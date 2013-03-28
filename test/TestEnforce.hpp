#ifndef TEST_CW_ENFORCE_HPP_INC
#define TEST_CW_ENFORCE_HPP_INC

#include <stdexcept>

#include <cw/Enforce.hpp>

Describe(the_enforce_idiom)
{
  It(should_throw_E_with_args)
  {
    AssertThrows(std::runtime_error,
      cw::enforce< std::runtime_error >( false, "" );
    );
  }

  It(should_not_throw_if_condition_is_false)
  {
    cw::enforce< std::runtime_error >( true, "" );
  }

  It(should_throw_with_message)
  {
    std::string msg = "It's false, dude!";
    AssertThrows(std::runtime_error,
      cw::enforce< std::runtime_error >( false, msg )
    );
    AssertThat( LastException<std::runtime_error>().what(), Equals( msg ) );
  }
};

#endif
