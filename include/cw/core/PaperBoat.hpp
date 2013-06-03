#ifndef CW_CORE_PAPER_BOAT_HPP_INC
#define CW_CORE_PAPER_BOAT_HPP_INC

#include <cw/core/Types.hpp>
#include <cw/core/Model.hpp>
#include <cw/core/Moving.hpp>

namespace cw
{
  namespace core
  {
    class PaperBoat : public Model
    {
      public:
        PaperBoat(double x, double y);
        virtual ~PaperBoat();

        virtual void tick(double diffTime) override;

        const Pos & getPos() const;
        void setMoveTarget(const Pos & p);
        double getCurrentOrientation() const
        { return m_moving.getCurrentOrientation(); }
      private:
        Moving m_moving;
    };
  }
}

#endif
