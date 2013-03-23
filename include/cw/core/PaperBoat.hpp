#ifndef CW_CORE_PAPER_BOAT_HPP_INC
#define CW_CORE_PAPER_BOAT_HPP_INC

#include <cw/core/Types.hpp>
#include <cw/core/RectangleUnit.hpp>

namespace cw
{
  namespace core
  {
    class PaperBoat : public RectangleUnit
    {
      public:
        PaperBoat(double x, double y);
        virtual ~PaperBoat();

        virtual void moveTo(double x, double y) override;
        virtual void tick() override;
    };
  }
}

#endif
