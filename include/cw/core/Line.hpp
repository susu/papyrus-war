#ifndef CW_CORE_LINE_HPP_INC
#define CW_CORE_LINE_HPP_INC

#include <cw/core/Pos3d.hpp>

namespace cw
{
  namespace core
  {
    class Line
    {
      public:
        static Line createFromPoints( Pos3d one, Pos3d two );

        Line( Pos3d directionVec, Pos3d fixPoint );
        ~Line();

        Pos3d getPointAtZ( double z ) const;
      private:
        Pos3d m_dirVec;
        Pos3d m_fixPoint;
    };
  }
}

#endif
