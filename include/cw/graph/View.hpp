#ifndef CW_GRAPH_VIEW_HPP_INC
#define CW_GRAPH_VIEW_HPP_INC

#include <cw/core/EntityContainer.hpp>

namespace cw
{
  namespace graph
  {
    class View
    {
      public:
        View(View&) = delete;
        void operator=(View&) = delete;

        virtual ~View()
        {}

        virtual void show() = 0;
      protected:
        View()
        {}
    };
    typedef core::EntityContainer<View, &View::show> ViewContainer;
  }
}
#endif
