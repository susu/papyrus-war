#ifndef FAKE_UNIFIED_INPUT_HANDLER_STUB_HPP_INC
#define FAKE_UNIFIED_INPUT_HANDLER_STUB_HPP_INC

#include <cw/core/UnifiedInputHandler.hpp>

namespace fake
{
  class UnifiedInputHandlerStub : public cw::core::UnifiedInputHandler
  {
    public:
      UnifiedInputHandlerStub()
        : m_zoomIn(0)
        , m_zoomOut(0)
      {}
      virtual void clickedAt(int x, int y)
      {
        m_clicks.push_back( Click{x,y} );
      }

      virtual void zoom(ZoomDir direction)
      {
        AssertThat( ZoomDir::IN == direction || ZoomDir::OUT == direction, Equals(true) );
        if ( direction == ZoomDir::IN ) ++m_zoomIn;
        else ++m_zoomOut;
      }

      virtual void startScroll(ScrollDir direction)
      {}

      virtual void stopScroll()
      {}

      bool hasClickAt(int x, int y) const
      {
        return m_clicks.end() != std::find_if(m_clicks.begin(), m_clicks.end(),
        [x,y](const Click & c)
        {
          return c.x == x && c.y == y;
        });
      }

      int getNumberOfZoomIn() const
      {
        return m_zoomIn;
      }

      int getNumberOfZoomOut() const
      {
        return m_zoomOut;
      }

      int getNumberOfClicks() const
      {
        return m_clicks.size();
      }
    private:
      struct Click
      {
        int x, y;
      };

      std::vector<Click> m_clicks;
      int m_zoomIn;
      int m_zoomOut;
  };
}

#endif
