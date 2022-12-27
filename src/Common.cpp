#include "Common.hpp"

LEVEK_NAMESPACE_BEGIN


filesystem::resolver *getFileResolver() {
    static filesystem::resolver *resolver = new filesystem::resolver();
    return resolver;
}

LEVEK_NAMESPACE_END