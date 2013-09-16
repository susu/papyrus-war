#ifndef CW_OPENGL_VERTEXBUFFER_HPP_INC
#define CW_OPENGL_VERTEXBUFFER_HPP_INC

#include <GL/glew.h>
#include <cw/MeasureUnits.hpp>

namespace cw
{
  namespace opengl
  {
    /**
     *  VertexBuffer represents a VBO
     */
    class VertexBuffer
    {
      public:
        VertexBuffer(ByteType size);
        ~VertexBuffer();

        // returns the index of the VBO
        GLint getIndex() const;

        // returns the alloc'd size of VBO
        ByteType getAllocatedSize() const;

      private:
        VertexBuffer(VertexBuffer&);
        VertexBuffer& operator=(VertexBuffer&);

        const ByteType m_allocatedVboSize;
        GLuint m_bufferIndex;
    };
  }
}

#endif
