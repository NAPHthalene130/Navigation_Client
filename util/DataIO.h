#ifndef NAVIGATION_UTIL_DATAIO_H
#define NAVIGATION_UTIL_DATAIO_H

#include <string>
#include "MapDataContainer.h"

class DataIO
{
public:
    static void writeFile(const std::string& path, MapDataContainer* container);
    static void writeNet(const std::string& ip, const std::string& port, MapDataContainer* container, const std::string& token);
    static MapDataContainer* readFile(const std::string& path);
    static MapDataContainer* readNet(const std::string& ip, const std::string& port, const std::string& token);
};

#endif // NAVIGATION_UTIL_DATAIO_H
