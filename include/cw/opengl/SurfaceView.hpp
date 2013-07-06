#ifndef CW_OPENGL_SURFACE_VIEW_HPP_INC
#define CW_OPENGL_SURFACE_VIEW_HPP_INC

#include <vector>

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
        SurfaceView(Ref< core::Surface >::R, ProjectionView&);
      protected:
        virtual void registerCallbacks();
      private:
        void processScrollback(core::ScrollEvent);
        void tick();

        virtual void doShow() override;

        bool isScrolling() const;

        Camera m_camera;

        typedef std::vector<int> ActiveScrollDirs;
        ActiveScrollDirs m_activeScrollDirs;
    };
  }
}

#endif
