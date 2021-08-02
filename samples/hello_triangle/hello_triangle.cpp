
#include "LevekGL.hpp"

#include <iostream>

int main(void) {
    std::cout << "hello triangle !" << std::endl;
    Levek::RenderingEngine engine = Levek::RenderingEngine(1024, 1024); 
    //Levek::FrameBuffer f = Levek::FrameBuffer(1024, 1024);
    return 0;
}