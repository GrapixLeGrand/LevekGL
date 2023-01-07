#include "Application.hpp"

#include "LevekGL.hpp"
#include "pugixml.hpp"
#include "Common.hpp"

LEVEK_NAMESPACE_BEGIN

Application::Application(const std::string& xmlFile) {

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xmlFile.c_str());

    if (!result) {
        throw LevekException("failed to parse the xml file with name %s", xmlFile);
    }

    pugi::xml_node sceneNode = doc.child("scene");
    
    if (!sceneNode) {
        throw LevekException("xml does not contains scene node");
    }

    for (pugi::xml_node n : sceneNode) {
        
        std::cout << n.name() << std::endl;
        //if (n.)
    }

}

void Application::mainLoop() {

}

LEVEK_NAMESPACE_END