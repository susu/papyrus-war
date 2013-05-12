#ifndef CW_OPENGL_SUN_HPP_INC
#define CW_OPENGL_SUN_HPP_INC

#include <cw/core/Pos3d.hpp>
#include <cw/opengl/ShaderResourceLocator.hpp>

namespace cw
{
  namespace opengl
  {
    class Program;
    /// Directional light
    class Sun
    {
      public:
        /**
         * @param program: GLSL program, needed for ShaderResourceLocator
         * @param pos: position of the Sun
         *     (it is a directional light, the direction points to the origo)
         * variables will be sent automatically to the GPU
         */
        Sun( Program & program, core::Pos3d pos );

        /**
         * sets the position of the Sun, but not updates it in the GPU
         *   you should call updateVariables() to send to the GPU
         */
        void setPos( core::Pos3d pos );

        /**
         * sends the variables to GPU
         */
        void updateVariables();

      private:
        ShaderResourceLocator m_resLocator;
        core::Pos3d m_pos;
    };
  }
}

#endif
