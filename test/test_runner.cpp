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
#include "TestViewFactory.hpp"

class LoggerTestListener : public NullTestListener
{
  public:
    LoggerTestListener()
      : m_out(std::cout)
    {}
    virtual void SpecRunStarting( const ContextBase&, const std::string& name )
    {
      m_out << "  * It " << name << std::endl;
    }
    virtual void ContextRunStarting(const ContextBase& context)
    {
      m_out << "\n# Describe " << context.Name() << std::endl;
    }
    // TODO portable solution
    // virtual void SpecSucceeded(const ContextBase& context, const std::string& specName)
    // {
    //   m_out << "    \033[1;32m" << "[SUCCESS!]" << "\033[0m" << std::endl;
    // }
  private:
    std::ostream & m_out;
};

template<class T>
bool hasArg( const T& argv, const std::string & needle )
{
  for( auto arg : argv )
  {
    if ( arg == needle ) return true;
  }
  return false;
}

int main(int argc, const char* argv[])
{
  DefaultTestResultsOutput output;
  TestRunner runner(output);

  LoggerTestListener listener;
  if ( hasArg( std::vector<std::string>(argv, argv+argc), "--verbose") )
  {
    runner.AddListener(&listener);
  }

  return runner.Run();
}
