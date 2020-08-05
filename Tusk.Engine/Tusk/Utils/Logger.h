#pragma once

#include "Defines.h"

namespace Tusk {

    class Logger {
    public:
        static void Trace(const char* message, ...);
        static void Log(const char* message, ...);
        static void Warn(const char* message, ...);
        static void Error(const char* message, ...);
        static void Fatal(const char* message, ...);
    };
}