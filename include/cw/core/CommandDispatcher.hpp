#ifndef CW_CORE_COMMAND_DISPATCHER_HPP_INC
#define CW_CORE_COMMAND_DISPATCHER_HPP_INC

#include <cw/core/Model.hpp>
#include <cw/core/InputDistributor.hpp>
#include <cw/core/EntityContainer.hpp>

namespace cw
{
  namespace core
  {
    class CommandDispatcher
    {
      public:
        typedef core::EntityContainer< core::Model > ModelContainer;
        CommandDispatcher(InputDistributor & distributor, const ModelContainer & models);

      private:
        void onClick(ClickEvent event);
    };
  }
}

#endif
