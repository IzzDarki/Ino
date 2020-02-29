---------------------------------------------------------------
#                         Ino Library                         #
#                            Core                             #
---------------------------------------------------------------

This library is the core of the Ino library series. It provides some useful functionality, that each isn't big enough to consist as an own library.

---------------------------------------------------------------

Preprocessor definitions (users can modify)

INO_PLATFORMIO      - default: undefined - should be defined when using PlatformIO environment

INO_DEBUG           - default: 0         - define as 0 for release and as anything else for debug

---------------------------------------------------------------

Preprocessor macros

INO_IF_DEBUG(x)     - expands to x when in debug

INO_IF_RELEASE(x)   - expands to x when in release
