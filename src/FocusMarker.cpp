#include <cw/opengl/FocusMarker.hpp>

namespace cw
{
  namespace opengl
  {

FocusMarker::FocusMarker(core::Model::Polygon && poly)
  : m_boundingBox(std::move(poly))
{
  ENFORCE( !m_boundingBox.empty(), "FocusMarker created with empty bounding box!" );
  glGenVertexArrays(1, &m_vaoId);
  glBindVertexArray(m_vaoId);
}

void FocusMarker::show()
{
}

  }
}
