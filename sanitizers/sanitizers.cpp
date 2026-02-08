/* Copyright 2026 CyberTech Labs Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "sanitizers.h"
#include <cstdio>
#include <mutex>
#include <cstring>

#ifdef HAS_SANITIZER_INTERFACE

std::atomic<char*> globalSanitizerLogPath{nullptr};

extern "C" {
	void initSanitizerPath(const char* path) {
		if (auto* const newPath = strdup(path)) {
			if (auto* const oldPath = globalSanitizerLogPath.exchange(newPath)) {
				free(oldPath);
			}
		}
	}

	// NOLINTNEXTLINE(bugprone-reserved-identifier)
	const char* __asan_default_options() { return "detect_leaks=1"; }

	// NOLINTNEXTLINE(bugprone-reserved-identifier)
	const char* __ubsan_default_options() { return "print_stacktrace=1"; }

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
