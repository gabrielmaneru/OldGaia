#pragma once

// Target definitions
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

// Include GLM
#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>

// Gaia definitions
#include <memory>
namespace Gaia {
	template<typename T>
	using unique = std::unique_ptr<T>;
	template<typename T>
	using shared = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr unique<T> new_unique(Args&&... args)
	{return std::make_unique<T>(std::forward<Args>(args)...);}
	template<typename T, typename ... Args>
	constexpr shared<T> new_shared(Args&&... args)
	{return std::make_shared<T>(std::forward<Args>(args)...);}


	// Type definitions
	using u8 = unsigned char;
	using u32 = unsigned int;
	struct urect{
		u32 x, y;
		bool operator==(const urect& r)const {
			return x == r.x&&y == r.y;
		}
	};
	using vec2 = glm::vec2;
	using vec3 = glm::vec3;
	using vec4 = glm::vec4;
	using mat3 = glm::mat3;
	using mat4 = glm::mat4;
}

// Asserts
#define GAIA_ASSERT(x, ...){ if(!(x)){\
	GAIA_LOG_CRITICAL("Assertion Failed: {0}", __VA_ARGS__);\
	__debugbreak();\
}}
#define GAIA_EASSERT(x, ...){ if(!(x)){\
	GAIA_ELOG_CRITICAL("Assertion Failed: {0}", __VA_ARGS__);\
	 __debugbreak();\
}}
