#ifndef CW_OPENGL_OPENGL_VIEW_MAPPING_HPP_INC
#define CW_OPENGL_OPENGL_VIEW_MAPPING_HPP_INC

#include <cw/core/PaperBoat.hpp>
#include <cw/graph/ViewFactory.hpp>

#include <cw/opengl/ProjectionView.hpp>
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

    class OpenGlViewFactory
    {
      public:
        OpenGlViewFactory( ProjectionView & projView )
          : m_projView(projView)
        {}
        template<typename T, typename Unit>
        Ref<graph::View> createViewFor(Unit unit)
        {
          return m_viewFactory.template createViewFor<T>(unit, m_projView);
        }
      private:
        ProjectionView & m_projView;
        graph::ViewFactory< OpenGlViewPolicy > m_viewFactory;
    };
  }
}


#endif
