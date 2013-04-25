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
#include <cw/opengl/Camera.hpp>
#include <cw/opengl/RayCastPicking.hpp>

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

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  glfwEnable( GLFW_STICKY_KEYS );

  GlfwCallbackRepo::initialize();
  graph::CallbackRepo & cbRepo = GlfwCallbackRepo::instance();

  core::Timer timer( glfwGetTime() );

  core::ModelContainer models;
  graph::ViewContainer views;

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

  ProjectionView projectionView(shaderProgram);
  Camera cam( projectionView );
  cam.setPos( 6, 7, -13 );
  cam.lookAt( 0, 0, 0 );
  cam.orientation( Camera::HEADS_UP );

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

  inputDistributor.registerClickedOn(
  [boat, &projectionView, &picking]( core::ClickEvent click )
  {
    LOG(DEBUG) << "click: x=" << click.pos.x << " y=" << click.pos.y;
    auto worldSpace = picking.unProject( click.pos );
    core::Pos p( worldSpace.x, worldSpace.y );
    boat->setPos( p );
  });

  glClearColor( 0.0f, 0.0f, 0.3f, 0.0f );

  double camX = 0;
  double camY = 0;
  double angle = 0;
  do
  {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // TESTCODE TODO: delete
    angle+= 0.01;
    camX = 10* cos(angle);
    camY = 10* sin(angle);
    cam.setPos( camX, camY, -13 );
    // TESTCODE

    models.doIt();
    views.doIt();
    glfwSwapBuffers();

    // glfwWaitEvents();
    timer.updateCurrentTime( glfwGetTime() );
  }
  while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS
      && glfwGetWindowParam( GLFW_OPENED ) );

  GlfwCallbackRepo::terminate();
}

void startGlFw()
{
  if ( !glfwInit() )
  {
    throw GlException( "Failed to initialize GLFW!" );
  }
  LOG(DEBUG) << "GLFW initialized.";

  glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4 ); // 4x anit-aliasing
  glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
  glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 1 );

  const int COLOR_DEPTH = 32;
  if ( !glfwOpenWindow( SCREEN_X, SCREEN_Y, 0,0,0,0, COLOR_DEPTH, 0, GLFW_WINDOW ) )
  {
    glfwTerminate();
    throw GlException( "Failed to open GLFW window!" );
  }
  glfwSetWindowTitle( "CelluloseWar" );
  int actualX;
  int actualY;
  glfwGetWindowSize( &actualX, &actualY );
  LOG(DEBUG) << "GLFW Window opened. " <<
    "requested_size=" << SCREEN_X << "x" << SCREEN_Y << " " <<
    "actual_size=" << actualX << "x" << actualY;

}

void initGlew()
{
  glewExperimental = true;

  if ( glewInit() != GLEW_OK)
  {
    throw GlException( "Failed to initialize GLEW!" );
  }
  LOG(DEBUG) << "GLEW initialized successfully.";
}

  }
}

