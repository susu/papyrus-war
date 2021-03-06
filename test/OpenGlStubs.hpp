#ifndef OPENGLSTUB_STUBS_H_INC
#define OPENGLSTUB_STUBS_H_INC

#include "GL/glew.h"

#include <iostream>

#include <cw/core/Logger.hpp>

#if defined(_WIN32)
#define STUB_APIENTRY __attribute__((stdcall))
#else
#define STUB_APIENTRY
#endif

//#undef STUB_APIENTRY
//#define STUB_APIENTRY

#include "openglstub/ShaderRepo.hpp"
#include "openglstub/ProgramRepo.hpp"
#include "openglstub/OpenGlMemoryStub.hpp"

namespace glstub
{
  extern ProgramRepo programRepo;
  extern GLuint lastProgram;
}

extern "C"
{
  inline GLuint STUB_APIENTRY stub_CreateProgram()
  {
    auto programId = glstub::programRepo.createProgram();
    LOG_DEBUG("programId=", programId);
    return programId;
  }

  inline GLuint STUB_APIENTRY stub_CreateShader(GLenum type)
  {
    GLuint shaderId = ShaderRepo::instance().createShader(type);
    LOG_DEBUG("shaderId=", shaderId);
    return shaderId;
  }

  inline void STUB_APIENTRY stub_GetShaderiv(GLuint index,GLenum infoType,GLint* out)
  {
    LOG_DEBUG();
    *out = ShaderRepo::instance().getShaderiv(index, infoType);
  }

  inline void STUB_APIENTRY stub_DeleteShader(GLuint)
  {
    LOG_DEBUG();
  }

  inline void STUB_APIENTRY stub_ShaderSource(GLuint id,int,const char **,const int*)
  {
    LOG_DEBUG();
  }

  inline void STUB_APIENTRY stub_CompileShader(GLuint id)
  {
    LOG_DEBUG();
    ShaderRepo::instance().compileShader(id);
  }

  inline void STUB_APIENTRY stub_GetShaderInfoLog(GLuint id, GLsizei bufSize, GLsizei*, GLchar* infoLog)
  {}

  inline GLint STUB_APIENTRY stub_GetUniformLocation(GLuint programId, const GLchar* unifName)
  {
    LOG_DEBUG("program-id=",programId, " uniform-name='", unifName, "'");
    if (glstub::programRepo.getProgram(programId).hasUniform(unifName))
    {
      return glstub::programRepo.getProgram(programId).getUniformIndex(unifName);
    }
    return -1;
  }

  inline void STUB_APIENTRY stub_UseProgram( GLuint programId )
  {
    LOG_DEBUG("glUseProgram: ", programId);
    glstub::lastProgram = programId;
  }

  inline void STUB_APIENTRY stub_UniformMatrix4fv(int matrixId, int,unsigned char,const float* matrixPtr)
  {
    LOG_DEBUG("uniform-id=", matrixId, " program-id=", glstub::lastProgram);
    glstub::programRepo.getProgram( glstub::lastProgram ).uniformMatrix(matrixId, 4, matrixPtr);
  }

  inline void STUB_APIENTRY stub_AttachShader(GLuint programId, GLuint shaderId)
  {
    LOG_DEBUG();
  }

  inline GLint STUB_APIENTRY stub_GetAttribLocation(GLuint programId, const char * attrName)
  {
    return -1;
  }

  inline void STUB_APIENTRY stub_BufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage)
  {
    auto & vbo = OpenGlMemoryStub::instance().getBoundVBO();
    vbo.type = target;
    vbo.size = size;
    vbo.usage = usage;
  }

  inline void STUB_APIENTRY stub_GenBuffers(GLsizei n, GLuint * buffers)
  {
    for (int i = 0; i < n; ++i)
    {
      buffers[i] = OpenGlMemoryStub::instance().generateVBO();
    }
  }
  inline void STUB_APIENTRY stub_BindBuffer(GLenum target, GLuint buffer)
  {
    OpenGlMemoryStub::instance().boundVBO(buffer);
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
    __glewAttachShader = &stub_AttachShader;
    __glewUniformMatrix4fv = &stub_UniformMatrix4fv;
    __glewGetAttribLocation = &stub_GetAttribLocation;
    __glewBufferData = &stub_BufferData;
    __glewGenBuffers = &stub_GenBuffers;
    __glewBindBuffer = &stub_BindBuffer;
    return 0;
  }
}

#endif
