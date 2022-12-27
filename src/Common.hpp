#pragma once

#include <stdexcept>
#include <tinyformat.h>

#include "filesystem/resolver.h"

#define LEVEK_NAMESPACE_BEGIN namespace Levek {
#define LEVEK_NAMESPACE_END }


LEVEK_NAMESPACE_BEGIN

/// Simple exception class, which stores a human-readable error description
class LevekException : public std::runtime_error {
public:
    /// Variadic template constructor to support printf-style arguments
    template <typename... Args> LevekException(const char *fmt, const Args &... args) 
     : std::runtime_error(tfm::format(fmt, args...)) { }
};

/// @brief returns a filesystem, this function was taken from the Nori Renderer.
/// @return 
extern filesystem::resolver *getFileResolver();

LEVEK_NAMESPACE_END