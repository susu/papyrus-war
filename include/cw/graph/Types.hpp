#ifndef CW_GRAPH_TYPES_HPP_INC
#define CW_GRAPH_TYPES_HPP_INC

#include <memory>

namespace cw
{
  namespace graph
  {
    class View;
    typedef std::shared_ptr<View> ViewRef;

    class PaperBoatView;
    typedef std::shared_ptr<PaperBoatView> PaperBoatViewRef;
  }
}

#endif
