#ifndef CW_GRAPH_OPENGL_VIEW_MAPPING_HPP_INC
#define CW_GRAPH_OPENGL_VIEW_MAPPING_HPP_INC

#include <cw/core/PaperBoat.hpp>
#include <cw/graph/PaperBoatView.hpp>

#include <cw/graph/ViewFactory.hpp>

namespace cw
{
  namespace graph
  {
    template<class T>
    struct OpenGlViewMapping;

    struct OpenGlViewPolicy
    {
      template<class T>
        using Mapping = OpenGlViewMapping<T>;
    };
    VIEW_MAPPING(OpenGlViewMapping, cw::core::PaperBoat, cw::graph::PaperBoatView);
  }
}


#endif
