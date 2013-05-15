#ifndef FAKE_UNIFIED_INPUT_HANDLER_STUB_HPP_INC
#define FAKE_UNIFIED_INPUT_HANDLER_STUB_HPP_INC

#include <igloo/igloo.h>

#include <cw/core/UnifiedInputHandler.hpp>

using namespace igloo;

namespace fake
{
  class UnifiedInputHandlerStub : public cw::core::UnifiedInputHandler
  {
    public:
      UnifiedInputHandlerStub()
        : m_zoomIn(0)
        , m_zoomOut(0)
        , m_hasScrollDir(false)
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

      virtual void startScroll(cw::core::ScrollDir direction)
      {
        m_hasScrollDir = true;
        m_scrollDir = direction;
      }

      virtual void stopScroll()
      {
        m_hasScrollDir = false;
      }

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

      bool hasScrollDir() const
      {
        return m_hasScrollDir;
      }

      cw::core::ScrollDir getLastScrollDir() const
      {
        return m_scrollDir;
      }
    private:
      struct Click
      {
        int x, y;
      };

      std::vector<Click> m_clicks;
      int m_zoomIn;
      int m_zoomOut;

      bool m_hasScrollDir;
      cw::core::ScrollDir m_scrollDir;
  };
}

#endif
