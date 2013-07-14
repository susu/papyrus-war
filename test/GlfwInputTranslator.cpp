#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <GLFW/glfw3.h>

#include <cw/opengl/GlfwInputTranslator.hpp>

#include "fake/UnifiedInputHandlerStub.hpp"

using namespace igloo;

Describe(the_glfwInputTranslator)
{
  typedef cw::core::ScrollDir ScrollDir;

  fake::UnifiedInputHandlerStub unifiedInputHandler;
  cw::opengl::GlfwInputTranslator translator;

  the_glfwInputTranslator()
    : translator(unifiedInputHandler)
  {}

  It(can_be_instantiated)
  {
    // TODO translator should accept also KeyConfig which contains the needed keymappings
    cw::opengl::GlfwInputTranslator translator(unifiedInputHandler);
  }

  It(should_forward_mouse_press_and_release_as_click)
  {
    int x = 940;
    int y = 303;
    translator.mouseMoveEvent(x,y);
    AssertThat( unifiedInputHandler.hasClickAt(x,y), Equals(false) );

    translator.mouseButtonEvent( GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS );
    AssertThat( unifiedInputHandler.hasClickAt(x,y), Equals(false) );

    translator.mouseButtonEvent( GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE );
    AssertThat( unifiedInputHandler.hasClickAt(x,y), Equals(true) );
    AssertThat( unifiedInputHandler.getNumberOfClicks(), Equals(1) );
  }

  It(should_handle_multiple_clicks)
  {
    int x = 268;
    int y = 511;
    translator.mouseMoveEvent(x,y);
    translator.mouseButtonEvent( GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS );
    translator.mouseButtonEvent( GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE );

    AssertThat( unifiedInputHandler.hasClickAt(x,y), Equals(true) );
    AssertThat( unifiedInputHandler.getNumberOfClicks(), Equals(1) );

    x = 1233;
    y = 122;
    translator.mouseMoveEvent(x,y);
    translator.mouseButtonEvent( GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS );
    translator.mouseButtonEvent( GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE );

    AssertThat( unifiedInputHandler.hasClickAt(x,y), Equals(true) );
    AssertThat( unifiedInputHandler.getNumberOfClicks(), Equals(2) );
  }

  It(should_interpret_mousewheel_up_as_zoom_in)
  {
    translator.mouseWheelEvent(1,0);

    AssertThat( unifiedInputHandler.getNumberOfZoomIn(), Equals(1) );
  }

  It(should_handle_same_mousewheel_pos_multiple_time_UP)
  {
    AssertThat( unifiedInputHandler.getNumberOfZoomIn(), Equals(0) );

    translator.mouseWheelEvent(1,0);
    AssertThat( unifiedInputHandler.getNumberOfZoomIn(), Equals(1) );

    translator.mouseWheelEvent(1,0);
    AssertThat( unifiedInputHandler.getNumberOfZoomIn(), Equals(1) );
  }

  It(should_interpret_mousewheel_down_as_zoom_out)
  {
    translator.mouseWheelEvent( -1,0 );
    AssertThat( unifiedInputHandler.getNumberOfZoomOut(), Equals(1) );
  }

  It(should_handle_same_mousewheel_pos_multiple_time_DOWN)
  {
    AssertThat( unifiedInputHandler.getNumberOfZoomIn(), Equals(0) );

    translator.mouseWheelEvent(-1,0);
    AssertThat( unifiedInputHandler.getNumberOfZoomOut(), Equals(1) );

    translator.mouseWheelEvent(-1,0);
    AssertThat( unifiedInputHandler.getNumberOfZoomOut(), Equals(1) );
  }

  It(should_interpret_key_arrows_as_scrolling)
  {
    AssertThat( unifiedInputHandler.hasScrollDir(), Equals(false) );

    translator.keyEvent(GLFW_KEY_LEFT, GLFW_PRESS);
    AssertThat( unifiedInputHandler.hasScrollDir(), Equals(true) );
    AssertThat( unifiedInputHandler.getActiveScrollDirs(), Contains(ScrollDir::LEFT) );
    AssertThat( unifiedInputHandler.getActiveScrollDirs(), HasLength(1) );

    translator.keyEvent(GLFW_KEY_LEFT, GLFW_RELEASE);
    AssertThat( unifiedInputHandler.hasScrollDir(), Equals(false) );
  }

  It(should_interpret_multiple_press_simultaneously)
  {
    translator.keyEvent(GLFW_KEY_LEFT, GLFW_PRESS);
    translator.keyEvent(GLFW_KEY_DOWN, GLFW_PRESS);

    AssertThat( unifiedInputHandler.getActiveScrollDirs(), HasLength(2) );
    AssertThat( unifiedInputHandler.getActiveScrollDirs(), Contains(ScrollDir::LEFT) );
    AssertThat( unifiedInputHandler.getActiveScrollDirs(), Contains(ScrollDir::DOWN) );

    translator.keyEvent(GLFW_KEY_LEFT, GLFW_RELEASE);
    AssertThat( unifiedInputHandler.getActiveScrollDirs(), HasLength(1) );
    AssertThat( unifiedInputHandler.getActiveScrollDirs(), Contains(ScrollDir::DOWN) );
  }

  It(should_handle_other_key_inputs_also)
  {
    translator.keyEvent('t', GLFW_PRESS);
    AssertThat( unifiedInputHandler.hasScrollDir(), Equals(false) );
  }

};
