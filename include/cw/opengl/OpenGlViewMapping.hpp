#ifndef CW_OPENGL_OPENGL_VIEW_MAPPING_HPP_INC
#define CW_OPENGL_OPENGL_VIEW_MAPPING_HPP_INC

#include <cw/core/PaperBoat.hpp>
#include <cw/graph/ViewFactory.hpp>

#include <cw/opengl/PaperBoatView.hpp>
namespace cw
{
  namespace opengl
  {
    template<class T>
    struct OpenGlViewMapping;

    struct OpenGlViewPolicy
    {
      template<class T>
        using Mapping = OpenGlViewMapping<T>;
    };
    VIEW_MAPPING(OpenGlViewMapping, cw::core::PaperBoat, cw::opengl::PaperBoatView);
    typedef graph::ViewFactory< OpenGlViewPolicy > OpenGlViewFactory;
  }
}


#endif
