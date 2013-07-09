Papyrus War
=============

Be the best and build your economy for creating paperboats!
Recycle paper to save the trees! Build unique ships, customize them with office tools!

Download binaries
-----------------

Not available yet!
 * windows
 * linux:
     - AUR PKGBUILD
     - deb packages

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

Development on windows is a bit messy, includes a lot of manual work.
I've collected the dependencies (as precompiled binaries) into a zip file (see below).
(I'm not a windows developer, so if you have better idea, let me know!)

 * Install Visual Studio 2013 Express Preview (it contains the newest MSVC)
 * Clone the repo
 * download [winlibs.zip]() and extract into the repo
 * Open a Developer Command Prompt (Start -> All Programs -> Microsoft Visual Studio 2013 -> Visual Studio Tools -> Developer Command Prompt for VS2013 Preview)
 * navigate to the repo
 * execute bootstrap.sh
 * tup init (only for first time)
 * tup upd

### Installing dependencies on OSX
