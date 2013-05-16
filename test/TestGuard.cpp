#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/Guard.hpp>

using namespace igloo;
using cw::core::CreateGuard;

Describe(AGuard)
{
  It(can_be_instantiated)
  {
    std::vector<int> numbers;

    {
      numbers.push_back(42);
      auto exitCallback = []( std::vector<int> & nums, int number )
      {
        nums.erase( std::remove(nums.begin(), nums.end(), number) );
      };
      auto guard = CreateGuard( exitCallback, std::ref(numbers) );
    }

    // (in progress) TODO
    // AssertThat(numbers.empty(), Equals(true));
  }
};
