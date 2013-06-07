#include <cw/opengl/SurfaceView.hpp>

#include <functional>
#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>

#include <cw/core/Logger.hpp>

namespace cw
{
  namespace opengl
  {

SurfaceView::SurfaceView( Ref< core::Surface> surface, ProjectionView& projView )
  : BaseType( surface, projView )
  , m_camera( projView )
  , m_activeScrollDirs(4,false)
{
  m_camera.setPos( 0, 0, -13 );
  m_camera.lookAt( 0, 0, 0 );
  m_camera.orientation( Camera::HEADS_UP );

  setModelVertices(
  {
    -1.0,  1.0, 0.0,
    -1.0, -1.0, 0.0,
     1.0, -1.0, 0.0,

    -1.0,  1.0, 0.0,
     1.0, -1.0, 0.0,
     1.0,  1.0, 0.0
  });
  computeNormals();
}

void SurfaceView::registerCallbacks()
{
  getRegistrars().getInputDistributor().registerScroll(
      std::bind(&SurfaceView::processScrollback, this, std::placeholders::_1) );
  getRegistrars().getTimer().setUpTimer(
      10_millisec,
      std::bind(&SurfaceView::tick,this) );
}

void SurfaceView::doShow()
{
  glm::mat4 modelMatrix = glm::scale( glm::mat4(1.0f), glm::vec3( 5.0f, 5.0f, 1.0f ) );

  sendMVP( modelMatrix );
  sendColor( 0.145f, 0.427f, 0.782f );

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SurfaceView::processScrollback(core::ScrollEvent ev)
{
  bool isStartScroll = (ev.action == core::ScrollEvent::START);
  m_activeScrollDirs[ to_underlying(ev.scrollDir) ] = isStartScroll;
}

bool SurfaceView::isScrolling() const
{
  return std::find(m_activeScrollDirs.begin(),
                   m_activeScrollDirs.end(),
                   true) != m_activeScrollDirs.end();
}

void SurfaceView::tick()
{
  using core::ScrollDir;

  if (!isScrolling())
    return;

  auto nextPos = m_camera.getPos();
  auto nextLook = m_camera.getLookAt();

  float step = 0.1;

  if ( m_activeScrollDirs[ to_underlying(ScrollDir::RIGHT) ] )
  {
    nextPos.x -= step;
    nextLook.x -= step;
  }

  if ( m_activeScrollDirs[ to_underlying(ScrollDir::LEFT) ] )
  {
    nextPos.x += step;
    nextLook.x += step;
  }

  if ( m_activeScrollDirs[ to_underlying(ScrollDir::DOWN) ] )
  {
    nextPos.y -= step;
    nextLook.y -= step;
  }

  if ( m_activeScrollDirs[ to_underlying(ScrollDir::UP) ] )
  {
    nextPos.y += step;
    nextLook.y += step;
  }

  m_camera.setPos( nextPos.x, nextPos.y, nextPos.z );
  m_camera.lookAt( nextLook.x, nextLook.y, nextLook.z );
}

  }
}
