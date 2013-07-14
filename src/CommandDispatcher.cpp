#include <cw/core/CommandDispatcher.hpp>


namespace cw
{
  namespace core
  {

CommandDispatcher::CommandDispatcher(
    InputDistributor & distributor,
    const ModelContainer & models)
{
  using namespace std::placeholders;

  distributor.registerClickedOn(std::bind(&CommandDispatcher::onClick, this, _1));
}

void CommandDispatcher::onClick(ClickEvent event)
{
}

  }
}
