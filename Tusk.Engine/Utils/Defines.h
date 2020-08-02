#pragma once

#ifndef U32_MAX
#define U32_MAX 0xffffffffui32
#endif

#ifndef U64_MAX
#define U64_MAX 0xffffffffffffffffui64
#endif

#define FORCEINLINE __forceinline

// Assertions
#define ASSERTIONS_ENABLED
#ifdef ASSERTIONS_ENABLED
#include <iostream>

#include <intrin.h>
#define debugBreak() __debugbreak();

#define ASSERT(expr) { \
    if( !expr ) { \
        reportAssertionFailure(#expr, "", __FILE__, __LINE__); \
        debugBreak(); \
    } \
}

#define ASSERT_MSG(expr, message) { \
    if( !expr ) { \
        reportAssertionFailure(#expr, message, __FILE__, __LINE__); \
        debugBreak(); \
    } \
}

#ifdef _DEBUG
#define ASSERT_DEBUG(expr) { \
    if( expr ) { \
    } else { \
        reportAssertionFailure(#expr, "", __FILE__, __LINE__); \
        debugBreak(); \
    } \
}
#else
#define ASSERT_DEBUG(expr) // Does nothing at all
#endif

FORCEINLINE void reportAssertionFailure(const char* expression, const char* message, const char* file, int line) {
    std::cerr << "Assertion failure: " << expression << ", message: '" << message << "', in file: " << file << ", line: " << line << "\n";
}

#else
#define ASSERT(expr) // Does nothing at all
#define ASSERT_MSG(expr, message) // Does nothing at all
#define ASSERT_DEBUG(expr) // Does nothing at all
#endif