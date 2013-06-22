#include <cw/opengl/Mesh.hpp>

#include <cw/core/Logger.hpp>
#include <cw/opengl/GlException.hpp>

namespace cw
{
  namespace opengl
  {

Mesh::Mesh(const std::string & fname, const std::string & objectName)
  : m_importer()
  , m_scene(m_importer.ReadFile(fname,
                                aiProcess_Triangulate
                                | aiProcess_ConvertToLeftHanded))
{
  LOG_DEBUG("Load object=", objectName, " from file=", fname);
  if (m_scene == nullptr)
  {
    THROW(GlException,
          core::MakeString() << "Cannot import file! (" <<
          m_importer.GetErrorString() << ")");
  }
  LOG_DEBUG("HasMeshes=",(m_scene->HasMeshes()? "true" : "false"));

  aiNode * node = m_scene->mRootNode->FindNode(objectName.c_str());
  if (node == nullptr)
  {
    THROW(GlException,"There is no such object!");
  }

  LOG_INFO("name=", node->mName.C_Str());

  unsigned meshIndex = node->mMeshes[0];
  aiMesh * mesh = m_scene->mMeshes[meshIndex];
  LOG_FINE("Mesh: ", mesh);
  for(unsigned v = 0; v < mesh->mNumVertices; ++v)
  {
    auto vertex = mesh->mVertices[v];
    LOG_FINE("vertex-",v,": (", vertex.x, ", ", vertex.y, ", ", vertex.z, ")");
    m_vertices.push_back(vertex.x);
    m_vertices.push_back(vertex.y);
    m_vertices.push_back(vertex.z);
  }
}

const std::vector<GLfloat> & Mesh::getVertices() const
{
  return m_vertices;
}

  }
}
