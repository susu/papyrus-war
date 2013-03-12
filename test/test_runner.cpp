#include "igloo/igloo.h"

#include "TestDummyGraphics.hpp"
#include "TestTimer.hpp"
#include "TestSuffixOperatorsForTime.hpp"
#include "TestGlfwInputTranslator.hpp"

int main()
{
  return igloo::TestRunner::RunAllTests();
}
