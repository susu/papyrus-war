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
      {
        m_activeScrollDirs[ cw::core::ScrollDir::LEFT ] = false;
        m_activeScrollDirs[ cw::core::ScrollDir::RIGHT ] = false;
        m_activeScrollDirs[ cw::core::ScrollDir::UP ] = false;
        m_activeScrollDirs[ cw::core::ScrollDir::DOWN ] = false;
      }
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
        m_activeScrollDirs[direction] = true;
      }

      virtual void stopScroll(cw::core::ScrollDir direction)
      {
        m_activeScrollDirs[ direction ] = false;
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
        return getNumberOfActiveScrolls() != 0;
      }

      size_t getNumberOfActiveScrolls() const
      {
        return std::count_if( m_activeScrollDirs.begin(), m_activeScrollDirs.end(),
        [](std::map<cw::core::ScrollDir,bool>::value_type x)
        {
          return x.second == true;
        });
      }

      std::vector<cw::core::ScrollDir> getActiveScrollDirs() const
      {
        std::vector<cw::core::ScrollDir> ret;
        for ( auto x : m_activeScrollDirs )
        {
          if (x.second)
            ret.push_back(x.first);
        }
        return ret;
      }
    private:
      struct Click
      {
        int x, y;
      };

      std::vector<Click> m_clicks;
      int m_zoomIn;
      int m_zoomOut;

      std::map<cw::core::ScrollDir,bool> m_activeScrollDirs;
  };
}

#endif
