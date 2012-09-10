#include "colladaloader.h"

#include "3rd_party/pugixml.hpp"

#include <QFile>

ColladaLoader::ColladaLoader(char* path)
{
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(path);

    QFile f2("test.txt");
    f2.open(QIODevice::ReadWrite);
    f2.write(doc.child("COLLADA").child("library_geometries").find_child_by_attribute("geometry", "name", "box").attribute("id").value());
    f2.waitForBytesWritten(1000);
    f2.close();

    //std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
}
