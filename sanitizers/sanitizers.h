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

#pragma once
#include <string>

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
extern "C" void initSanitizerPath(const char* path);
#endif
