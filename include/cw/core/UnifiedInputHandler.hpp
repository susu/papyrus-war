#ifndef CW_CORE_UNIFIED_INPUT_HANDLER_HPP_INC
#define CW_CORE_UNIFIED_INPUT_HANDLER_HPP_INC

namespace cw
{
  namespace core
  {
    class UnifiedInputHandler
    {
      public:
        enum class ZoomDir : int
        {
          IN,
          OUT
        };
        enum class ScrollDir : int
        {
          RIGHT,
          DOWN,
          LEFT,
          UP
        };
        virtual ~UnifiedInputHandler()
        {}

        virtual void clickedAt(int x, int y) = 0;
        virtual void zoom(ZoomDir direction) = 0;
        virtual void startScroll(ScrollDir direction) = 0;
        virtual void stopScroll() = 0;
    };
  }
}
#endif
