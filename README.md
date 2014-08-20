##Disclaimer##
THIS PROJECT IS NOT READY FOR PRIME TIME. IT IS NOT EVEN USABLE YET.

I ONLY MAKE IT PUBLIC IN ORDER TO USE ITS CODE FOR THE NEXT LUDUM DARE.
USE IT AT YOUR OWN RISK !

##Yet Another Game Engine##
YAGE is a C++ game engine built on top of SDL2. 

It doesn't aim to be a full-featured high performance engine, instead it focus on being developper friendly and encouraging the use of modern C++ idioms.

##Dependencies##
* [SDL2](https://www.libsdl.org/download-2.0.php)
* [Boost](http://www.boost.org/users/download/)

##How to build##
*Pro-tip*: don't ! (copy the files you need in yout project instead)

The project is curently a VisualStudio 2013 SDL Project, not even a DLL.
It has some hard-coded dependencies paths.

If you really want to try, here's a list of stuff to do:
* Fix sdl2 and boost includes directories
* Fix sdl2 and boost libraries paths
* Hope it's enough