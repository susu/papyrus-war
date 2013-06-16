#ifndef CW_OPENGL_GL_EXCEPTION_HPP_INC
#define CW_OPENGL_GL_EXCEPTION_HPP_INC

#include <cw/core/BaseException.hpp>

namespace cw
{
  namespace opengl
  {
    struct GlException : public core::BaseException
    {
      GlException(const char* file, int line, const std::string & wh )
        : core::BaseException(file,line,wh)
      {}
    };
  }
}

#endif
