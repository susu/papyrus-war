#ifndef CW_OPENGL_PAPER_BOAT_VIEW_HPP_INC
#define CW_OPENGL_PAPER_BOAT_VIEW_HPP_INC

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <cw/core/Types.hpp>

#include <cw/graph/View.hpp>
#include <cw/graph/Types.hpp>

#include <cw/opengl/OpenGlViewBase.hpp>

namespace cw
{
  namespace opengl
  {
    class ProjectionView;
    class PaperBoatView : public OpenGlViewBase<core::PaperBoat>
    {
      public:
        PaperBoatView( core::PaperBoatRef model, ProjectionView & projView );

      private:
        virtual void doShow() override;
    };
  }
}

#endif
