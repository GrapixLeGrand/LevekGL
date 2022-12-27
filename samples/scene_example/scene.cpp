
#include "LevekGL.hpp"

#include <iostream>
#include <vector>

int main(void) {
    
    std::cout << "example scene !" << std::endl;

    /*filesystem::path xmlPath = Levek::getFileResolver()->resolve("test.xml");

    if (!xmlPath.exists()) {
        throw Levek::LevekException("failed to find the xml with name %s", "test.xml");
    }*/

    filesystem::path p = Levek::getFileResolver()->resolve("samples/scene_example/test.xml");
    Levek::Application app(p.str());

    app.mainLoop();

    return 0;
}