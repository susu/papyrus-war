#ifndef CW_OPENGL_SURFACE_VIEW_HPP_INC
#define CW_OPENGL_SURFACE_VIEW_HPP_INC

#include <cw/core/Types.hpp>
#include <cw/core/Surface.hpp>
#include <cw/core/InputDistributor.hpp>

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
      protected:
        virtual void registerCallbacks();
      private:
        void processScrollback(core::ScrollEvent);
        void tick();

        Camera m_camera;
        core::ScrollDir m_scrollDir;
        bool m_isScrolling;
    };
  }
}

#endif
