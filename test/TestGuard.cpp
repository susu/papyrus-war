#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/Guard.hpp>

using namespace igloo;
using cw::core::CreateGuard;

Describe(AGuard)
{
  It(works_with_vector)
  {
    std::vector<int> numbers;

    {
      numbers.push_back(42);
      auto exitCallback = [&numbers]( int number )
      {
        numbers.erase( std::remove(numbers.begin(), numbers.end(), number) );
      };
      auto guard = CreateGuard( exitCallback, 42 );
    }

    AssertThat(numbers.empty(), Equals(true));
  }

  It(calls_the_function_only_once)
  {
    int numberOfCalls = 0;

    { // TEST block
      auto guard = CreateGuard( [&numberOfCalls]()
      {
        ++numberOfCalls;
      });
    } // TEST block

    AssertThat(numberOfCalls, Equals(1));
  }
};
