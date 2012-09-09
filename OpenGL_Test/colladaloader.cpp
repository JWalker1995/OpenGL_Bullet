#include "colladaloader.h"

#include "3rd_party/pugixml.hpp"

http://www.everita.com/lightwave-collada-and-opengles-on-the-iphone
http://www.gamedev.net/topic/547314-collada-and-opengl/

ColladaLoader::ColladaLoader(char* path)
{
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(path);

    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
}
