#ifndef CW_OPENGL_GL_EXCEPTION_HPP_INC
#define CW_OPENGL_GL_EXCEPTION_HPP_INC

#include <stdexcept>

namespace cw
{
  namespace opengl
  {
    struct GlException : public std::logic_error
    {
      GlException( const std::string & wh )
        : std::logic_error(wh)
      {}
    };
  }
}

#endif
