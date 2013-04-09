#ifndef TEST_CW_OPENGL_SHADER_HPP_INC
#define TEST_CW_OPENGL_SHADER_HPP_INC

#include <cw/opengl/Shader.hpp>

Describe(the_Shader)
{
  void SetUp()
  {
    shaderRepo.clear();
  }

  It(can_be_instantiated)
  {
    cw::opengl::Shader shader( "", GL_VERTEX_SHADER );
    AssertThat( shaderRepo.shaders(), HasLength(1) );
  }

  It(can_compile_the_shader_source)
  {
    cw::opengl::Shader shader( "", GL_VERTEX_SHADER );
    shader.compile();
    AssertThat( shaderRepo.shaders().back().compiled, Equals(true) );
  }

  It(can_check_the_shader_state)
  {
    cw::opengl::Shader shader( "", GL_VERTEX_SHADER );
    shader.compile();
    shader.check();

    AssertThat( shaderRepo.shaders().back().checked, Equals(true) );
  }
};

#endif
