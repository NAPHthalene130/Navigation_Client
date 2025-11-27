#ifndef NAVIGATION_UTIL_EDGE_H
#define NAVIGATION_UTIL_EDGE_H
#include "MapPointButton.h"
class Edge {
public:
    MapPointButton* firstPoint;
    MapPointButton* secondPointButton;
    explicit Edge(MapPointButton* a, MapPointButton* b);
};
#endif // NAVIGATION_UTIL_EDGE_H
