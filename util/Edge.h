#ifndef NAVIGATION_UTIL_EDGE_H
#define NAVIGATION_UTIL_EDGE_H
#include "MapPointButton.h"
class Edge {
public:
    explicit Edge(MapPointButton* a, MapPointButton* b);

    MapPointButton* getFirstPoint() const;
    void setFirstPoint(MapPointButton* p);

    MapPointButton* getSecondPointButton() const;
    void setSecondPointButton(MapPointButton* p);

    int getType() const;
    void setType(int t);

    bool operator==(const Edge& other) const;

private:
    MapPointButton* firstPoint = nullptr;
    MapPointButton* secondPointButton = nullptr;
    int type = 0;
};

struct EdgeLess {
    bool operator()(const Edge& a, const Edge& b) const;
};
#endif // NAVIGATION_UTIL_EDGE_H
