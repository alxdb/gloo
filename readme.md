# gloo

A small collection of classes to make writing opengl code a bit less verbose.

This is not meant to replace all opengl functionality. It is more for managing
openGL objects via RAII, and providing functions encapsulating commonly
performed tasks.

Ids can always be fetched for use with any OpenGL function. The idea is to mix
raw OpenGL calls, with these utility classes.

the GLEW header file is included by deafult. If you want to use another opengl
loader then define `GLOO_NOGLEW` before including `gloo.hpp`.

if included as a cmake subdirectory, an interface library will be exported which
links glew and opengl as well as these header files.
