#pragma once

// Target :: Windows
#ifdef _WIN32
	#ifdef _WIN64
		#define GAIA_WINDOWS
	#else
		#error "x86 not supported"
	#endif
// Target :: Apple / Mac
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
// Target :: Android
#elif defined(__ANDROID__)
	#error "Android is not supported!"
// Target :: Linux
#elif defined(__linux__)
	#error "Linux is not supported!"
// Target :: Unknown
#else
	#error "Unknown platform!"
#endif
