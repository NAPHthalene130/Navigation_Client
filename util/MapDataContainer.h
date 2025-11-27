#ifndef NAVIGATION_UTIL_MAPDATACONTAINER_H
#define NAVIGATION_UTIL_MAPDATACONTAINER_H
#include <vector>
#include <string>
class MapPointButton;

class MapDataContainer
{
public:
    MapDataContainer() = default;
    ~MapDataContainer() = default;

    void addMapPointButton(MapPointButton* button);
    void deleteButtonByName(const std::string& name);
    void cleanPointButtonContainerNullptr();

    std::vector<MapPointButton*> pointButtonContainer;
};

#endif //NAVIGATION_UTIL_MAPDATACONTAINER_H
