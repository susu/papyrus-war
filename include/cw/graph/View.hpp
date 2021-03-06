#ifndef CW_GRAPH_VIEW_HPP_INC
#define CW_GRAPH_VIEW_HPP_INC

#include <cw/core/EntityContainer.hpp>
#include <cw/core/HasCallbackRegistrar.hpp>

namespace cw
{
  namespace graph
  {
    class View : public core::HasCallbackRegistrar
    {
      public:
        virtual ~View()
        {}

        virtual void show() = 0;
      protected:
        View(View&);
        void operator=(View&);

        View()
        {}
    };
  }
}
#endif
