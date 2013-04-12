#include <cw/opengl/GlmPicking.hpp>

namespace cw
{
  namespace opengl
  {

core::Pos3d GlmPicking::unProject( core::Pos click )
{
  return core::Pos3d( click.x, click.y, 0.0);
}

  }
}
