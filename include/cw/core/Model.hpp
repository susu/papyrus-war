#ifndef CW_CORE_MODEL_HPP_INC
#define CW_CORE_MODEL_HPP_INC

#include <cw/core/HasCallbackRegistrar.hpp>

namespace cw
{
  namespace core
  {
    class Model : public HasCallbackRegistrar
    {
      public:
        virtual void tick(double diffTime) = 0;

        // is-mouse-over method
        virtual bool isOver(Pos p) const = 0;

        void setFocus(bool focused)
        {
          m_focused = focused;
          if (focused) onFocused();
          else onDeFocused();
        }

        bool hasFocus() const
        { return m_focused; }

        // @{ Command-receiver concept
        virtual void onOuterClick(Pos click, Ref<Model>::R clickedModel) = 0;

      private:
        virtual void onFocused() = 0;
        virtual void onDeFocused() = 0;
        // @}

        bool m_focused;
    };
  }
}

#endif
