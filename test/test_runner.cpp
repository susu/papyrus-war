#include "igloo/igloo.h"

#include <cw/core/Logger.hpp>
namespace
{
  cw::core::Logger logger("unittest");
}

#include "TestDummyGraphics.hpp"
#include "TestTimer.hpp"
#include "TestSuffixOperatorsForTime.hpp"
#include "TestGlfwInputTranslator.hpp"
#include "TestInputDistributor.hpp"
#include "TestEntityContainer.hpp"
#include "TestPaperBoat.hpp"
#include "TestRectangleUnit.hpp"
#include "TestUnitFactory.hpp"

int main()
{
  return igloo::TestRunner::RunAllTests();
}
