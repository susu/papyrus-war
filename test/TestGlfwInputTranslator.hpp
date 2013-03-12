#ifndef TEST_GLFW_INPUT_TRANSLATOR_HPP_INC
#define TEST_GLFW_INPUT_TRANSLATOR_HPP_INC

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/graph/GlfwInputTranslator.hpp>

#include "fake/UnifiedInputHandlerStub.hpp"

Describe(the_glfwInputTranslator)
{
  It(can_be_instantiated)
  {
    fake::UnifiedInputHandlerStub unifiedInputHandler;
    cw::graph::GlfwInputTranslator translator(unifiedInputHandler);
  }

  It(should_forward_mouse_click_event)
  {
    std::cout << "\n!!! PENDING: It_" << __FUNCTION__ << " !!!" << std::endl;
  }

  It(should_interpret_mousewheel_up_as_zoom_in)
  {
    std::cout << "\n!!! PENDING: It_" << __FUNCTION__ << " !!!" << std::endl;
  }

  It(should_interpret_mousewheel_down_as_zoom_out)
  {
    std::cout << "\n!!! PENDING: It_" << __FUNCTION__ << " !!!" << std::endl;
  }

  It(should_interpret_press_key_arrows_as_start_of_scrolling)
  {
    std::cout << "\n!!! PENDING: It_" << __FUNCTION__ << " !!!" << std::endl;
  }

  It(should_interpret_release_key_as_stopScroll)
  {
    std::cout << "\n!!! PENDING: It_" << __FUNCTION__ << " !!!" << std::endl;
  }

};

#endif
