#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <thread>
#include <chrono>

#include <cw/core/Logger.hpp>
#include <cw/core/Timer.hpp>
#include <cw/core/Model.hpp>
#include <cw/core/InputDistributor.hpp>
#include <cw/core/PaperBoat.hpp>
#include <cw/core/Surface.hpp>

#include <cw/graph/ModelFactory.hpp>
#include <cw/graph/View.hpp>
#include <cw/graph/ScreenSize.hpp>

#include <cw/opengl/GlException.hpp>
#include <cw/opengl/GlfwWindow.hpp>
#include <cw/opengl/OpenGlLoop.hpp>
#include <cw/opengl/PaperBoatView.hpp>
#include <cw/opengl/GlfwInputTranslator.hpp>
#include <cw/opengl/OpenGlViewMapping.hpp>
#include <cw/opengl/Program.hpp>
#include <cw/opengl/ProjectionView.hpp>
#include <cw/opengl/RayCastPicking.hpp>
#include <cw/opengl/Sun.hpp>
#include <cw/opengl/Gpu.hpp>
#include <cw/opengl/OpenGlViewBase.hpp>

namespace
{
  const int SCREEN_X = 1280;
  const int SCREEN_Y = 700;
}

namespace cw
{
  namespace opengl
  {

struct TargetMarker : core::Model
{
  TargetMarker(double x, double y)
    : m_pos(x,y)
  {}

  void tick(double) override {}
  void onFocused() override {}
  void onDeFocused() override {}
  void onOuterClick(core::Pos click, Ref<core::Model>::R clickedModel) override {}

  core::Pos m_pos;
};

struct TargetMarkerView : OpenGlViewBase<TargetMarker>
{
  TargetMarkerView(Ref<TargetMarker>::R tmarker, ProjectionView & projView)
    : BaseType(tmarker,projView)
  {
    setModelVertices(
    {
       0.2f, -0.2f, 0.0f,
       0.0f,  0.0f, 0.0f, // tip
      -0.2f, -0.2f, 0.0f,
    });
    computeNormals();
  }

  void doShow() override
  {
    double x = m_model->m_pos.x;
    double y = m_model->m_pos.y;
    glm::mat4 modelMatrix = glm::translate( glm::mat4(1.0f), glm::vec3( x,y, -0.1f ) );
    sendMVP(modelMatrix);
    sendColor( 1.0, 0.0, 0.0 );

    glDrawArrays(GL_TRIANGLES, 0, getNumberOfVertices() );
  }
};

VIEW_MAPPING(OpenGlViewMapping, TargetMarker, TargetMarkerView);

void initGlew();

OpenGlLoop::OpenGlLoop()
  : m_screenSize( SCREEN_X, SCREEN_Y )
  , m_window(m_screenSize,"PapyrusWar")
{
  LOG_INFO("Window opened: size=", m_screenSize);
  initGlew();
  LOG_INFO("OpenGL context initialized");
  LOG_INFO("Video memory size: ", opengl::gpu::getDedicatedMemory()/1000.0, " MB");

  m_window.setInputMode(GLFW_STICKY_KEYS, GL_TRUE);
}

OpenGlLoop::~OpenGlLoop()
{
  glfwTerminate();
}

void OpenGlLoop::run()
{
  core::Timer timer( glfwGetTime() );

  core::EntityContainer<core::Model> models;
  core::EntityContainer<graph::View> views;

  Program shaderProgram;

  try
  {
    shaderProgram.attachShaderFromFile( "shaders/vertex.glsl", GL_VERTEX_SHADER );
    shaderProgram.attachShaderFromFile( "shaders/fragment.glsl", GL_FRAGMENT_SHADER );
    shaderProgram.link();
  }
  catch( GlException const & ex )
  {
    LOG_EXCEPTION( ex );
    return;
  }

  ProjectionView projectionView(shaderProgram, m_screenSize);

  RayCastPicking picking( projectionView, m_screenSize );
  core::InputDistributor inputDistributor( picking ); // forwards input to models

  GlfwInputTranslator inputTranslator( inputDistributor ); // process GLFW input
  inputTranslator.registerCallbacks(m_window);

  auto modelCallback = [&models]( Ref<core::Model>::R model )
  {
    models.add(model);
  };
  auto viewCallback = [&views]( Ref<graph::View>::R view )
  {
    views.add(view);
  };

  core::CallbackRegistrars cbRegistrars(inputDistributor, timer);
  graph::ModelFactory< opengl::OpenGlViewFactory > modelFactory(
    modelCallback, viewCallback, projectionView);
  modelFactory.setCallbackRegistrar(cbRegistrars);

  LOG_DEBUG("Creating initial objects");
  auto boat = modelFactory.create< core::PaperBoat >(0,0);
  modelFactory.create< core::Surface >( );
  auto targetMarker = modelFactory.create< TargetMarker >(0,0);
  opengl::Sun sun( shaderProgram, core::Pos3d(-10,7.5,-5) );

  LOG_DEBUG("Set up click-following logic");
  inputDistributor.registerClickedOn(
  [targetMarker, boat, &picking]( core::ClickEvent click )
  {
    LOG_DEBUG("click: x=", click.pos.x, " y=", click.pos.y);
    auto worldSpace = picking.unProject( click.pos );
    core::Pos p( worldSpace.x, worldSpace.y );
    boat->setMoveTarget( p );
    targetMarker->m_pos = p;
  });


  timer.setUpTimer( 10.0, []()
  {
    LOG_DEBUG("Current GPU memory usage: ",
              gpu::getDedicatedMemory()-gpu::getAvailabelDedicatedMemory(),
              " KB");
  });

  const float skyBlueR = 0.529f;
  const float skyBlueG = 0.807f;
  const float skyBlueB = 0.980f;
  glClearColor( skyBlueR, skyBlueG, skyBlueB, 0.0f );
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_CULL_FACE );
  glCullFace( GL_BACK );
  glFrontFace( GL_CW );

  // double angle = 0;
  core::Pos3d sunPos( 10.0, 10.0, -5.0 );

  // TODO register timer callback
  double lastTickShot = glfwGetTime();
  do
  {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    double timeDiff = glfwGetTime() - lastTickShot;
    models.each([timeDiff](Ref<core::Model>::R & model)
    {
      model->tick(timeDiff);
    });
    lastTickShot = glfwGetTime();

    views.each([](Ref<graph::View>::R & view)
    {
      view->show();
    });

    m_window.swapBuffers();
    glfwPollEvents();

    std::this_thread::sleep_for( std::chrono::milliseconds(10) );

    timer.updateCurrentTime( glfwGetTime() );
  }
  while( m_window.getKeyStatus(GLFW_KEY_ESCAPE) != GLFW_PRESS
         && !m_window.shouldBeClosed());

  LOG_INFO("Exiting gracefully.");
}

void initGlew()
{
  glewExperimental = true;

  if ( glewInit() != GLEW_OK)
  {
    THROW( GlException, "Failed to initialize GLEW!" );
  }
  LOG_INFO("GLEW initialized successfully.");
}

  }
}

