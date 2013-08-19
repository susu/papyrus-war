#ifndef CW_CORE_OPENGL_FOCUS_MARKER_HPP_INC
#define CW_CORE_OPENGL_FOCUS_MARKER_HPP_INC

#include <GL/glew.h>
#include <cw/core/Model.hpp>

namespace cw
{
  namespace opengl
  {
    class FocusMarker
    {
      public:
        /**
         * @param boundingBox mustn't be empty
         */
        FocusMarker(core::Model::Polygon && boundingBox);

        void show();
      private:
        core::Model::Polygon m_boundingBox;
        GLuint m_vaoId; // Vertex Array Object ID
    };

  }
}

#endif
