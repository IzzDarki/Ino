#pragma once
#ifndef INO_CORE_INCLUDED
#define INO_CORE_INCLUDED

#ifndef INO_DEBUG
    #define INO_DEBUG 0
#endif

#if INO_DEBUG
    #define INO_IF_DEBUG(...) __VA_ARGS__
    #define INO_IF_RELEASE(...)
#else
    #define INO_IF_DEBUG(...)
    #define INO_IF_RELEASE(...) __VA_ARGS__
#endif

#if defined(INO_PLATFORMIO) && !defined(INO_STANDARDIN)
	#define INO_PLATFORMIOIN
#else
	#define INO_STANDARDIN
#endif

#endif
