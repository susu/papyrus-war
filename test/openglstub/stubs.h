
#include "GL/glew.h"
#include "GL/glxew.h"

#include <iostream>

#include "ShaderRepo.hpp"
#include "ProgramRepo.hpp"

namespace glstub
{
  ShadersRepo shaderRepo;
  ProgramRepo programRepo;
  GLuint lastProgram;
}

extern "C"
{
  GLuint stub_CreateProgram()
  {
    LOG(DEBUG);
    return glstub::programRepo.createProgram();
  }

  GLuint stub_CreateShader(GLenum type)
  {
    LOG(DEBUG);
    return glstub::shaderRepo.createShader(type);
  }

  void stub_GetShaderiv(GLuint index,GLenum infoType,GLint* out)
  {
    LOG(DEBUG);
    *out = glstub::shaderRepo.getShaderiv(index, infoType);
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
    glstub::shaderRepo.compileShader(id);
  }

  void stub_GetShaderInfoLog(GLuint id, GLsizei bufSize, GLsizei*, GLchar* infoLog)
  {}

  GLint stub_GetUniformLocation(GLuint, const GLchar*)
  {
    return 1;
  }

  void stub_UseProgram( GLuint programId )
  {
    glstub::lastProgram = programId;
  }

  void stub_UniformMatrix4fv(int matrixId, int,unsigned char,const float* matrixPtr)
  {
    glstub::programRepo.getProgram( glstub::lastProgram ).uniformMatrix(matrixId, matrixPtr);
  }

  GLenum glewInit()
  {
    __glewCreateProgram = &stub_CreateProgram;
    __glewCreateShader = &stub_CreateShader;
    __glewGetShaderiv = &stub_GetShaderiv;
    __glewDeleteShader = &stub_DeleteShader;
    __glewShaderSource = &stub_ShaderSource;
    __glewCompileShader = &stub_CompileShader;
    __glewGetShaderInfoLog = &stub_GetShaderInfoLog;
    __glewGetUniformLocation = &stub_GetUniformLocation;
    __glewUseProgram = &stub_UseProgram;
    __glewUniformMatrix4fv = &stub_UniformMatrix4fv;
    return 0;
  }
}

