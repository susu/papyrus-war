#include <GL/glew.h>
#include <GL/glfw.h>

#include <cw/core/Logger.hpp>
#include <cw/core/Timer.hpp>
#include <cw/core/Unit.hpp>
#include <cw/core/InputDistributor.hpp>

#include <cw/graph/GlException.hpp>
#include <cw/graph/GlfwCallbackRepo.hpp>
#include <cw/graph/OpenGlLoop.hpp>
#include <cw/graph/View.hpp>
#include <cw/graph/GlfwInputTranslator.hpp>

namespace
{
  cw::core::Logger logger("opengl");
  const int SCREEN_X = 640;
  const int SCREEN_Y = 480;
}

namespace cw
{
  namespace graph
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

  glfwEnable( GLFW_STICKY_KEYS );

  GlfwCallbackRepo::initialize();
  CallbackRepo & cbRepo = GlfwCallbackRepo::instance();

  core::Timer timer( glfwGetTime() );

  core::UnitContainer units;
  graph::ViewContainer views;

  core::InputDistributor inputDistributor; // forwards input to units
  graph::GlfwInputTranslator inputTranslator( inputDistributor ); // process GLFW input
  inputTranslator.registerCallbacks( cbRepo );

  // auto boat = core::PaperBoat::create(10,10);
  // units.add( boat );

  // views.add( boat );

  do
  {
    units.doIt();
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
  glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 2 );
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

