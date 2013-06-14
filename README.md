Papyrus War
=============

Be the best and build your economy for creating paperboats!
Recycle paper to save the trees! Build unique ships, customize them with office tools!

Download binaries
-----------------

Not available yet!
 * [windows]()
 * [linux]()

Development
===========

Get the source
--------------

Source code is under GPLv3

``git clone --recursive <repo>``

Build
-----

``tup init`` (only first time)

``tup upd`` (builds every config)

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

If you don't have packer, download from [AUR](aur.archlinux.org)

### Installing dependencies on Ubuntu/Debian

### Installing dependencies on Windows

At the moment windows build is not working (compiles, but crashes at various places).
If you need more info, drop me a mail!

### Installing dependencies on OSX
