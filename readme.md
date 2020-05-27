# gl\_utils

A small collection of classes to make writing opengl code a bit less verbose.

This is not meant to replace all opengl functionality. It is more for managing
openGL objects via RAII, and providing functions encapsulating commonly
performed tasks.

Ids can always be fetched for use with any OpenGL function. The idea is to mix
raw OpenGL calls, with these utility classes.

