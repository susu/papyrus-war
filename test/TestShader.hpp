#ifndef TEST_CW_OPENGL_SHADER_HPP_INC
#define TEST_CW_OPENGL_SHADER_HPP_INC

#include <cw/opengl/Shader.hpp>

Describe(the_Shader)
{
  It(can_be_instantiated)
  {
    cw::opengl::Shader shader( "", GL_VERTEX_SHADER );
  }

  It(can_compile_the_shader_source)
  {
    cw::opengl::Shader shader( "", GL_VERTEX_SHADER );
    shader.compile();
  }
};

#endif
