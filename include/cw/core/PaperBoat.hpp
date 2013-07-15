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

        void tick(double diffTime) override;

        bool isOver(Pos pos) const override;

        void onFocused() override
        {}

        void onDeFocused() override
        {}

        void onOuterClick(Pos click, Ref<Model>::R clickedModel) override
        {}

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
