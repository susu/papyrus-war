
#include "GL/glew.h"
#include "GL/glxew.h"

#include <iostream>

extern "C"
{
  GLuint stub_CreateProgram()
  {
    std::cout << "SEAM WORK!" << std::endl;
    return 0;
  }

  GLenum glewInit()
  {
    __glewCreateProgram = &stub_CreateProgram;
    return 0;
  }
}

