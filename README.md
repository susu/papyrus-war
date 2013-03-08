Cellulose War
=============

Get the source
--------------

``git clone --recursive <repo>``

Build
-----

``tup init`` (only first time)

``tup upd`` (builds both release and debug)

**NOTE:** debug compilation needs suid on ``/usr/bin/tup`` (``sudo chmod u+s /usr/bin/tup``)
**NOTE:** debug compilation needs ``user_allow_other`` in ``/etc/fuse.conf``

If you want build release only:
``tup upd build-release``

Dependencies
------------

  * [tup](http://gittup.org/tup/)
  * [GLEW - OpenGL Extension Wrangler Library](glew.sourceforge.net)
  * [GLFW - OpenGL FrameWork (or Good Luck Finding Willy)](www.glfw.org)

### Installing dependencies on ArchLinux

You'll need the following packages:

  * aur/tup-git
  * extra/glew
  * community/glfw

``pacman -S glew glfw``

If you have packer:

``packer -S tup-git``

### Installing dependencies on Ubuntu/Debian

### Installing dependencies on Windows

### Installing dependencies on OSX
