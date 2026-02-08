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
#include <string>

#ifdef HAS_SANITIZER_INTERFACE

static std::string globalSanitizerLogPath; // clazy:exclude=non-pod-global-static
static std::mutex sanitizerMutex;
static FILE* sanitizerFile = nullptr;

extern "C" {
	void initSanitizerPath(const char* path) {
		if (!path) return;
		std::lock_guard<std::mutex> lock(sanitizerMutex);
		globalSanitizerLogPath = path;
		if (sanitizerFile) {
			fclose(sanitizerFile);
			sanitizerFile = nullptr;
		}
	}

	// NOLINTNEXTLINE(bugprone-reserved-identifier)
	void __sanitizer_on_print(const char* str) {
		std::lock_guard<std::mutex> lock(sanitizerMutex);

		if (!sanitizerFile && !globalSanitizerLogPath.empty()) {
			sanitizerFile = fopen(globalSanitizerLogPath.c_str(), "a");
		}

		FILE* out = sanitizerFile ? sanitizerFile : stderr;
		fputs(str, out);
		fflush(out);
	}
}

#endif
