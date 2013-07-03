#ifndef CW_OPENGL_RAY_CAST_PICKING_HPP_INC
#define CW_OPENGL_RAY_CAST_PICKING_HPP_INC

#include <glm/glm.hpp>

#include <cw/core/PickingInterface.hpp>

#include <cw/graph/ScreenSize.hpp>

namespace cw
{
  namespace graph
  {
    struct ScreenSize;
  }
  namespace opengl
  {
    class ProjectionView;
    class RayCastPicking : public core::PickingInterface
    {
      public:
        RayCastPicking( ProjectionView &, const graph::ScreenSize & );
        virtual ~RayCastPicking();

        virtual core::Pos3d unProject( core::Pos ) override;
      private:
        RayCastPicking(RayCastPicking&);
        void operator=(RayCastPicking);

        core::Pos transformClickToBottomLeftCorner( core::Pos ) const;
        core::Pos3d unProjectScreenPos( const glm::vec3 & ) const;

        ProjectionView & m_projView;
        graph::ScreenSize m_screenSize;
        glm::vec4 m_viewPort;
    };
  }
}

#endif
