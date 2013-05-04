#ifndef OPENGLSTUB_STUBS_H_INC
#define OPENGLSTUB_STUBS_H_INC

#include "GL/glew.h"
#include "GL/glxew.h"

#include <iostream>

#include <cw/core/Logger.hpp>

namespace
{
  cw::core::Logger logger( "openglstub" );
}

#include "openglstub/ShaderRepo.hpp"
#include "openglstub/ProgramRepo.hpp"

namespace glstub
{
  extern ShadersRepo shaderRepo;
  extern ProgramRepo programRepo;
  extern GLuint lastProgram;
}

extern "C"
{
  inline GLuint stub_CreateProgram()
  {
    auto programId = glstub::programRepo.createProgram();
    LOG(DEBUG) << "programId=" << programId;
    return programId;
  }

  inline GLuint stub_CreateShader(GLenum type)
  {
    GLuint shaderId = glstub::shaderRepo.createShader(type);
    LOG(DEBUG) << "shaderId=" << shaderId;
    return shaderId;
  }

  inline void stub_GetShaderiv(GLuint index,GLenum infoType,GLint* out)
  {
    LOG(DEBUG);
    *out = glstub::shaderRepo.getShaderiv(index, infoType);
  }

  inline void stub_DeleteShader(GLuint)
  {
    LOG(DEBUG);
  }

  inline void stub_ShaderSource(GLuint id,int,const char **,const int*)
  {
    LOG(DEBUG);
  }

  inline void stub_CompileShader(GLuint id)
  {
    LOG(DEBUG);
    glstub::shaderRepo.compileShader(id);
  }

  inline void stub_GetShaderInfoLog(GLuint id, GLsizei bufSize, GLsizei*, GLchar* infoLog)
  {}

  inline GLint stub_GetUniformLocation(GLuint, const GLchar*)
  {
    return 1;
  }

  inline void stub_UseProgram( GLuint programId )
  {
    glstub::lastProgram = programId;
  }

  inline void stub_UniformMatrix4fv(int matrixId, int,unsigned char,const float* matrixPtr)
  {
    glstub::programRepo.getProgram( glstub::lastProgram ).uniformMatrix(matrixId, matrixPtr);
  }

  inline GLenum glewInit()
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

#endif
