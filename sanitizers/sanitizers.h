#pragma once
#include <atomic>

#if defined(__SANITIZE_ADDRESS__)
#	define HAS_ASAN 1
#elif defined(__has_feature)
#	if __has_feature(address_sanitizer)
#		define HAS_ASAN 1
#	endif
#endif

#if defined(__has_feature)
#	if __has_feature(undefined_behavior_sanitizer)
#		define HAS_UBSAN 1
#	endif
#endif

#if defined(HAS_ASAN) || defined(HAS_UBSAN)
#   define HAS_SANITIZER_INTERFACE
#endif

#ifdef HAS_SANITIZER_INTERFACE
#include <sanitizer/common_interface_defs.h>

extern std::atomic<char*> globalSanitizerLogPath;

extern void initSanitizerPath(const char* path);
#endif
