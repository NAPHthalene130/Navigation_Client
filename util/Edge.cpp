#include "Edge.h"

Edge::Edge(MapPointButton* a, MapPointButton* b) {
    firstPoint = a;
    secondPointButton = b;
    if (a && b) {
        if (b->getName() < a->getName()) {
            firstPoint = b;
            secondPointButton = a;
        }
    }
}
