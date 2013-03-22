#ifndef CW_GRAPH_TYPES_HPP_INC
#define CW_GRAPH_TYPES_HPP_INC

#include <memory>

template<class T>
using Ref = std::shared_ptr<T>;

namespace cw
{
  namespace graph
  {
    class View;
    typedef Ref<View> ViewRef;

    class PaperBoatView;
    typedef Ref<PaperBoatView> PaperBoatViewRef;
  }
}

#endif
