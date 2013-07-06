#ifndef CW_OPENGL_MESH_HPP_INC
#define CW_OPENGL_MESH_HPP_INC

#include <GL/glew.h>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// wrapper class for Assimp
namespace cw
{
  namespace opengl
  {
    class Mesh
    {
      public:
        /**
         *  The ctor loads 'objectName' from 'fname'
         *  @fname      COLLADA file (.dae)
         *  @objectName
         *
         *  @throws GlException if cannot load file or objectName not found
         */
        Mesh(const std::string & fname, const std::string & objectName);

        const std::vector<GLfloat> & getVertices() const;
      private:
        Assimp::Importer m_importer;
        const aiScene * m_scene;
        std::vector<GLfloat> m_vertices;
    };
  }
}

#endif
