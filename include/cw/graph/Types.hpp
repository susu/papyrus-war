#ifndef CW_GRAPH_TYPES_HPP_INC
#define CW_GRAPH_TYPES_HPP_INC

#include <memory>

#include <cw/core/Types.hpp>

namespace cw
{
  namespace graph
  {
    class View;
    typedef Ref<View> ViewRef;
  }
  namespace opengl
  {
    class PaperBoatView;
    typedef Ref<PaperBoatView> PaperBoatViewRef;
  }
}

#endif
