#include <GL/glew.h>
#include <GL/glfw.h>

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
#include <cw/opengl/GlfwCallbackRepo.hpp>
#include <cw/opengl/OpenGlLoop.hpp>
#include <cw/opengl/PaperBoatView.hpp>
#include <cw/opengl/GlfwInputTranslator.hpp>
#include <cw/opengl/OpenGlViewMapping.hpp>
#include <cw/opengl/Program.hpp>
#include <cw/opengl/ProjectionView.hpp>
#include <cw/opengl/RayCastPicking.hpp>
#include <cw/opengl/Sun.hpp>
#include <cw/opengl/Gpu.hpp>

namespace
{
  cw::core::Logger logger("opengl");
  const int SCREEN_X = 1024;
  const int SCREEN_Y = 600;
}

namespace cw
{
  namespace opengl
  {

void startGlFw();

void initGlew();

OpenGlLoop::OpenGlLoop()
{}

OpenGlLoop::~OpenGlLoop()
{}

void OpenGlLoop::run()
{
  try
  {
    startGlFw();
    initGlew();
  }
  catch( GlException const & ex )
  {
    LOG_EXCEPTION( ex );
    return;
  }

  LOG_INFO("Video memory size: ", opengl::gpu::getDedicatedMemory()/1000.0, " MB");
  glfwEnable( GLFW_STICKY_KEYS );

  GlfwCallbackRepo::initialize();
  graph::CallbackRepo & cbRepo = GlfwCallbackRepo::instance();

  core::Timer timer( glfwGetTime() );

  core::EntityContainer<core::Model> models;
  core::EntityContainer<graph::View> views;

  Program shaderProgram;
  graph::ScreenSize screen( SCREEN_X, SCREEN_Y );

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

  ProjectionView projectionView(shaderProgram,screen);

  RayCastPicking picking( projectionView, screen );
  core::InputDistributor inputDistributor( picking ); // forwards input to models
  GlfwInputTranslator inputTranslator( inputDistributor ); // process GLFW input
  inputTranslator.registerCallbacks( cbRepo );


  auto modelCallback = [&models]( Ref<core::Model> model )
  {
    models.add(model);
  };
  auto viewCallback = [&views]( graph::ViewRef view )
  {
    views.add(view);
  };

  graph::ModelFactory< opengl::OpenGlViewFactory > modelFactory(
    modelCallback, viewCallback, projectionView);

  auto boat = modelFactory.create< core::PaperBoat >(0,0);
  auto surface = modelFactory.create< core::Surface >( );
  opengl::Sun sun( shaderProgram, core::Pos3d(10,10,-5) );

  inputDistributor.registerClickedOn(
  [boat, &projectionView, &picking]( core::ClickEvent click )
  {
    LOG_DEBUG("click: x=", click.pos.x, " y=", click.pos.y);
    auto worldSpace = picking.unProject( click.pos );
    core::Pos p( worldSpace.x, worldSpace.y );
    boat->setPos( p );
  });

  timer.setUpTimer( 1_sec, []()
  {
    LOG_DEBUG("Current GPU memory usage: ",
              opengl::gpu::getDedicatedMemory()-opengl::gpu::getAvailabelDedicatedMemory(),
              " KB");
  });

  const float skyBlueR = 0.529f;
  const float skyBlueG = 0.807f;
  const float skyBlueB = 0.980f;
  glClearColor( skyBlueR, skyBlueG, skyBlueB, 0.0f );
  glEnable( GL_DEPTH_TEST );

  // double angle = 0;
  core::Pos3d sunPos( 10.0, 10.0, -5.0 );
  do
  {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // TESTCODE TODO: delete
    // angle+= 0.01;
    //camX = 10* cos(angle);
    //camY = 10* sin(angle);
    // sunPos.z = 30 * ( cos(angle) );
    // sunPos.x = 10 * ( -2.5 + sin(angle) );
    // sun.setPos( sunPos );
    // sun.updateVariables();
    //LOG_DEBUG("Sun's position: ", sunPos);
    // TESTCODE

    models.each([](Ref<core::Model> & model)
    {
      model->tick();
    });

    views.each([](Ref<graph::View> & view)
    {
      view->show();
    });

    glfwSwapBuffers();

    glfwWaitEvents();
    timer.updateCurrentTime( glfwGetTime() );
  }
  while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS
      && glfwGetWindowParam( GLFW_OPENED ) );

  LOG_INFO("Exiting gracefully.");
  GlfwCallbackRepo::terminate();
  glfwTerminate();
}

void startGlFw()
{
  if ( !glfwInit() )
  {
    throw GlException( "Failed to initialize GLFW!" );
  }
  LOG_INFO("GLFW initialized.");

  glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4 ); // 4x anit-aliasing
  glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
  glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 2 );

  const int COLOR_DEPTH = 32;
  if ( !glfwOpenWindow( SCREEN_X, SCREEN_Y, 0,0,0,0, COLOR_DEPTH, 0, GLFW_WINDOW ) )
  {
    glfwTerminate();
    throw GlException( "Failed to open GLFW window!" );
  }
  glfwSetWindowTitle( "PapyrusWar" );
  int actualX;
  int actualY;
  glfwGetWindowSize( &actualX, &actualY );
  LOG_INFO("GLFW Window opened. ",
    "requested_size=", SCREEN_X, "x", SCREEN_Y, " ",
    "actual_size=", actualX, "x", actualY);

}

void initGlew()
{
  glewExperimental = true;

  if ( glewInit() != GLEW_OK)
  {
    throw GlException( "Failed to initialize GLEW!" );
  }
  LOG_INFO("GLEW initialized successfully.");
}

  }
}

