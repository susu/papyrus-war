#ifndef TEST_GLFW_INPUT_TRANSLATOR_HPP_INC
#define TEST_GLFW_INPUT_TRANSLATOR_HPP_INC

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <GL/glfw.h>

#include <cw/graph/GlfwInputTranslator.hpp>

#include "fake/UnifiedInputHandlerStub.hpp"

Describe(the_glfwInputTranslator)
{
  fake::UnifiedInputHandlerStub unifiedInputHandler;
  cw::graph::GlfwInputTranslator translator;

  the_glfwInputTranslator()
    : translator(unifiedInputHandler)
  {}

  It(can_be_instantiated)
  {
    // TODO translator should accept also KeyConfig which contains the needed keymappings
    cw::graph::GlfwInputTranslator translator(unifiedInputHandler);
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
    translator.mouseWheelEvent(1);

    AssertThat( unifiedInputHandler.getNumberOfZoomIn(), Equals(1) );
  }

  It(should_handle_same_mousewheel_pos_multiple_time_UP)
  {
    AssertThat( unifiedInputHandler.getNumberOfZoomIn(), Equals(0) );

    translator.mouseWheelEvent(1);
    AssertThat( unifiedInputHandler.getNumberOfZoomIn(), Equals(1) );

    translator.mouseWheelEvent(1);
    AssertThat( unifiedInputHandler.getNumberOfZoomIn(), Equals(1) );
  }

  It(should_interpret_mousewheel_down_as_zoom_out)
  {
    translator.mouseWheelEvent( -1 );
    AssertThat( unifiedInputHandler.getNumberOfZoomOut(), Equals(1) );
  }

  It(should_handle_same_mousewheel_pos_multiple_time_DOWN)
  {
    AssertThat( unifiedInputHandler.getNumberOfZoomIn(), Equals(0) );

    translator.mouseWheelEvent(-1);
    AssertThat( unifiedInputHandler.getNumberOfZoomOut(), Equals(1) );

    translator.mouseWheelEvent(-1);
    AssertThat( unifiedInputHandler.getNumberOfZoomOut(), Equals(1) );
  }

  It(should_interpret_press_key_arrows_as_start_of_scrolling)
  {
    typedef cw::core::UnifiedInputHandler::ScrollDir ScrollDir;
    AssertThat( unifiedInputHandler.hasScrollDir(), Equals(false) );

    translator.keyEvent(GLFW_KEY_LEFT, GLFW_PRESS);
    AssertThat( unifiedInputHandler.hasScrollDir(), Equals(true) );
    AssertThat( unifiedInputHandler.getLastScrollDir(), Equals(ScrollDir::LEFT) );
  }

  It(should_interpret_release_key_as_stopScroll)
  {
    std::cout << "\n!!! PENDING: It_" << __FUNCTION__ << " !!!" << std::endl;
  }

};

#endif
