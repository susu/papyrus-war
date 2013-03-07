#ifndef CW_GRAPH_GL_EXCEPTION_HPP_INC
#define CW_GRAPH_GL_EXCEPTION_HPP_INC

#include <stdexcept>

namespace cw
{
  namespace graph
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
