#include "MapDataContainer.h"
#include "MapPointButton.h"

void MapDataContainer::addMapPointButton(MapPointButton* button)
{
    pointButtonContainer.push_back(button);
}

void MapDataContainer::deleteButtonByName(const std::string& name)
{
    for (auto it = pointButtonContainer.begin(); it != pointButtonContainer.end(); )
    {
        MapPointButton* b = *it;
        if (b && b->getName() == name)
        {
            b->hide();
            b->deleteLater();
            it = pointButtonContainer.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
