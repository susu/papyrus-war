#ifndef CW_OPENGL_PAPER_BOAT_VIEW_HPP_INC
#define CW_OPENGL_PAPER_BOAT_VIEW_HPP_INC

#include <vector>

#include <GL/glew.h>

#include <cw/core/Types.hpp>

#include <cw/graph/View.hpp>
#include <cw/graph/Types.hpp>

namespace cw
{
  namespace opengl
  {
    class PaperBoatView : public graph::View
    {
      public:
        static PaperBoatViewRef create( core::PaperBoatRef model );

        PaperBoatView( core::PaperBoatRef model );

        virtual void show() override;
      private:
        GLuint m_vertexBuffer;
        GLuint m_shaderProgramId;
        std::vector< GLfloat > m_model;
    };
  }
}

#endif
