#ifndef CW_OPENGL_GLM_PICKING_HPP_INC
#define CW_OPENGL_GLM_PICKING_HPP_INC

#include <cw/core/PickingInterface.hpp>

namespace cw
{
  namespace opengl
  {
    class GlmPicking : public core::PickingInterface
    {
      public:
        virtual core::Pos3d unProject( core::Pos ) override;
    };
  }
}

#endif
