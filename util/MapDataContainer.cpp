#include "MapDataContainer.h"
#include "MapPointButton.h"
#include "Edge.h"

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

void MapDataContainer::cleanPointButtonContainerNullptr()
{
    for (auto it = pointButtonContainer.begin(); it != pointButtonContainer.end(); )
    {
        MapPointButton* b = *it;
        if (!b || b->parent() == nullptr)
        {
            it = pointButtonContainer.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void MapDataContainer::reset()
{
    for (auto button : pointButtonContainer) {
        button->hide();
        button->deleteLater();
    }
    pointButtonContainer.clear();
    for (auto edge : edgeContainer) {
        delete edge;
    }
    edgeContainer.clear();
}