#ifndef GLSTUB_OPENGL_MEMORY_STUB_HPP_INC
#define GLSTUB_OPENGL_MEMORY_STUB_HPP_INC

#include <GL/glew.h>
#include <memory>
#include <unordered_map>

#include <cw/Enforce.hpp>

class OpenGlMemoryStub
{
  public:
    struct VBO
    {
      GLint index;
      GLenum type;
      size_t size;
      GLenum usage;
    };
    static OpenGlMemoryStub& instance();

    const VBO& getVBO(GLint index) const;
    VBO& getBoundVBO();
    void boundVBO(GLint index);
    GLuint generateVBO();
  private:
    OpenGlMemoryStub();
    GLint getNextIndex();

    static std::unique_ptr<OpenGlMemoryStub> s_instance;
    GLint m_boundVBO; ///< index of the currently bound VBO
    GLint m_lastIndex;

    std::unordered_map<GLint,VBO> m_VBOs;
};

#endif
