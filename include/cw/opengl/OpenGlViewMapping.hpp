#ifndef CW_OPENGL_OPENGL_VIEW_MAPPING_HPP_INC
#define CW_OPENGL_OPENGL_VIEW_MAPPING_HPP_INC

#include <cw/core/PaperBoat.hpp>
#include <cw/core/Surface.hpp>
#include <cw/graph/ViewFactory.hpp>

#include <cw/opengl/ProjectionView.hpp>
#include <cw/opengl/PaperBoatView.hpp>
#include <cw/opengl/SurfaceView.hpp>

namespace cw
{
  namespace opengl
  {
    template<class T>
    struct OpenGlViewMapping;

    struct OpenGlViewPolicy
    {
      template<class T>
      struct Mapping
      {
        typedef OpenGlViewMapping<T> type;
      };
    };
    VIEW_MAPPING(OpenGlViewMapping, cw::core::PaperBoat, cw::opengl::PaperBoatView);
    VIEW_MAPPING(OpenGlViewMapping, cw::core::Surface, cw::opengl::SurfaceView);

    class OpenGlViewFactory
    {
      public:
        OpenGlViewFactory( ProjectionView & projView )
          : m_projView(projView)
        {}
        template<typename T, typename Model>
        typename Ref<graph::View>::R createViewFor(Model model)
        {
          return m_viewFactory.template createViewFor<T>(model, m_projView);
        }
      private:
        ProjectionView & m_projView;
        graph::ViewFactory< OpenGlViewPolicy > m_viewFactory;
    };
  }
}


#endif
