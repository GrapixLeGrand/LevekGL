

#include "Object.hpp"

LEVEK_NAMESPACE_BEGIN

std::map<std::string, LevekObjectFactory::Constructor> *LevekObjectFactory::m_constructors = nullptr;

void LevekObjectFactory::registerClass(const std::string &name, const Constructor &constr) {
    if (!m_constructors)
        m_constructors = new std::map<std::string, LevekObjectFactory::Constructor>();
    (*m_constructors)[name] = constr;
}

LEVEK_NAMESPACE_END