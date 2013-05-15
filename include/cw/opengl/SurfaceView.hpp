#ifndef CW_OPENGL_SURFACE_VIEW_HPP_INC
#define CW_OPENGL_SURFACE_VIEW_HPP_INC

#include <cw/core/Types.hpp>
#include <cw/core/Surface.hpp>

#include <cw/opengl/OpenGlViewBase.hpp>
#include <cw/opengl/Camera.hpp>

namespace cw
{
  namespace opengl
  {
    class ProjectionView;
    class SurfaceView : public opengl::OpenGlViewBase< core::Surface >
    {
      public:
        SurfaceView(Ref< core::Surface >, ProjectionView&);
        virtual void show() override;
      private:
        Camera m_camera;
    };
  }
}

#endif
