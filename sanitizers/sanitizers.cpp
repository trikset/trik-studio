#include "sanitizers.h"
#include <cstdio>
#include <mutex>
#include <cstring>
#include <atomic>
#include <iostream>

#ifdef HAS_SANITIZER_INTERFACE

std::atomic<char*> globalSanitizerLogPath{nullptr};

void initSanitizerPath(const char* path) {
	if (auto* const newPath = strdup(path)) {
		if (auto* const oldPath = globalSanitizerLogPath.exchange(newPath)) {
			free(oldPath);
		}
	}
}

extern "C" {
	__attribute__((used, visibility("default")))
	// NOLINTNEXTLINE(bugprone-reserved-identifier)
	const char* __asan_default_options() { return "detect_leaks=1"; }

	__attribute__((used, visibility("default")))
	// NOLINTNEXTLINE(bugprone-reserved-identifier)
	const char* __ubsan_default_options() { return "print_stacktrace=1"; }

	__attribute__((used, visibility("default")))
	// NOLINTNEXTLINE(bugprone-reserved-identifier)
	void __sanitizer_on_print(const char* str) {
		static FILE* file = nullptr;
		static std::mutex mutex;

		std::lock_guard<std::mutex> lock(mutex);
		auto* const path = globalSanitizerLogPath.load();
		if (path && !file) {
			file = fopen(path, "a");
		}

		auto* const out = file ? file : stderr;
		fputs(str, out);
		fflush(out);
	}
}

#endif
