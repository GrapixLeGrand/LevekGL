#pragma once

#include "Object.hpp"


LEVEK_NAMESPACE_BEGIN

class Application {

public:

Application(const std::string& xmlFile);

void mainLoop();

};

LEVEK_NAMESPACE_END
