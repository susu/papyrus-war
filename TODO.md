TODO
====

Version targets:
================

## v0.0.1 target:
  - limited size of water surface
  - one white paper boat
  - the ship can be controlled by mouse-right click
  - surface is scrollable

## v0.0.2 target:
  - ship is loaded from file (.obj or COLLADA format)


TODO list
=========

Always a good idea to ``ack --cpp TODO`` or ``grep -nrs TODO``

 * [DONE] ENFORCE idiom
 * [DONE] include __PRETTY_FUNCTION__ to logs
 * Wrapper class for GLFW (at least some RAII wrapper for init-terminate)
 * [DONE] UnitFactory(as ModelFactory)

## broken down sub-tasks for v0.0.1:

  * [DONE] show a blue surface (Surface class)
  * [DONE] show a white ship (PaperBoat class)
  * Scrollable surface
    - SurfaceView needs to know Camera
    - SurfaceView needs callbacks for mouse-edge events (enter/leave) )
  * Controlling with mouse right click
    - PaperBoat should register callback for move command
    - physical model timing: needs improvement (e.g. diff time as argument)

