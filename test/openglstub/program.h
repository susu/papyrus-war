
#include "GL/glew.h"
#include "GL/glxew.h"

#include <iostream>

#include "ShaderRepo.hpp"

namespace
{
  ShadersRepo shaderRepo;
}

extern "C"
{
  GLuint stub_CreateProgram()
  {
    LOG(DEBUG);
    return 0;
  }

  GLuint stub_CreateShader(GLenum type)
  {
    LOG(DEBUG);
    return shaderRepo.createShader(type);
  }

  void stub_GetShaderiv(GLuint index,GLenum infoType,GLint* out)
  {
    LOG(DEBUG);
    *out = shaderRepo.getShaderiv(index, infoType);
  }

  void stub_DeleteShader(GLuint)
  {
    LOG(DEBUG);
  }

  void stub_ShaderSource(GLuint id,int,const char **,const int*)
  {
    LOG(DEBUG);
  }

  void stub_CompileShader(GLuint id)
  {
    LOG(DEBUG);
    shaderRepo.compileShader(id);
  }

  void stub_GetShaderInfoLog(GLuint id, GLsizei bufSize, GLsizei*, GLchar* infoLog)
  {}

  GLenum glewInit()
  {
    __glewCreateProgram = &stub_CreateProgram;
    __glewCreateShader = &stub_CreateShader;
    __glewGetShaderiv = &stub_GetShaderiv;
    __glewDeleteShader = &stub_DeleteShader;
    __glewShaderSource = &stub_ShaderSource;
    __glewCompileShader = &stub_CompileShader;
    __glewGetShaderInfoLog = &stub_GetShaderInfoLog;
    return 0;
  }
}

