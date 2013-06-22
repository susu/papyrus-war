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

There are several configs/targets:

  * build-debug (no optimization, enables every loglevel, very verbose)
  * build-release (with optimization, less loglevel)
  * build-clang (same as debug, but compiled with clang)

If you don't have clang, you can delete the build-clang directory,
it will not harm the others.

``tup init`` (only first time)

``tup upd`` (builds every config)

You can compile only one config:

E.g.: If you want build release only:
``tup upd build-release``

Dependencies
------------

  * [tup](http://gittup.org/tup/)
  * [GLEW - OpenGL Extension Wrangler Library](glew.sourceforge.net)
  * [GLFW - OpenGL FrameWork (or Good Luck Finding Willy)](www.glfw.org)
  * [glm - OpenGL Mathematics](http://glm.g-truc.net/)
  * [assimp - Open Asset Import Library](http://assimp.sourceforge.net/)

### Installing dependencies on ArchLinux

You'll need the following packages:

  * aur/tup-git
  * extra/glew
  * community/glfw
  * community/glm
  * community/assimp

``pacman -S glew glfw glm assimp``

If you have packer:

``packer -S tup-git``

If you don't have packer, download from [AUR](aur.archlinux.org)

### Installing dependencies on Ubuntu/Debian

### Installing dependencies on Windows

At the moment windows build is not working (compiles, but crashes at various places).
If you need more info, drop me a mail!

### Installing dependencies on OSX
