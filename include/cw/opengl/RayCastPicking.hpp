#ifndef CW_OPENGL_RAY_CAST_PICKING_HPP_INC
#define CW_OPENGL_RAY_CAST_PICKING_HPP_INC

#include <glm/glm.hpp>

#include <cw/core/PickingInterface.hpp>

#include <cw/graph/ScreenSize.hpp>

namespace cw
{
  namespace graph
  {
    class ScreenSize;
  }
  namespace opengl
  {
    class ProjectionView;
    class RayCastPicking : public core::PickingInterface
    {
      public:
        RayCastPicking( ProjectionView &, const graph::ScreenSize & );
        virtual ~RayCastPicking();

        RayCastPicking(RayCastPicking&) = delete;
        void operator=(RayCastPicking) = delete;

        virtual core::Pos3d unProject( core::Pos ) override;
      private:
        ProjectionView & m_projView;
        graph::ScreenSize m_screenSize;
        glm::vec4 m_viewPort;
    };
  }
}

#endif
