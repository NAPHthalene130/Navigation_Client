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

MapPointButton* Edge::getFirstPointButton() const {
    return firstPoint;
}

void Edge::setFirstPointButton(MapPointButton* p) {
    firstPoint = p;
}

MapPointButton* Edge::getSecondPointButton() const {
    return secondPointButton;
}

void Edge::setSecondPointButton(MapPointButton* p) {
    secondPointButton = p;
}

int Edge::getType() const { return type; }
void Edge::setType(int t) { type = t; }

bool Edge::operator==(const Edge& other) const {
    const std::string a1 = firstPoint ? firstPoint->getName() : "";
    const std::string a2 = secondPointButton ? secondPointButton->getName() : "";
    const std::string b1 = other.firstPoint ? other.firstPoint->getName() : "";
    const std::string b2 = other.secondPointButton ? other.secondPointButton->getName() : "";
    if (a1.empty() || a2.empty() || b1.empty() || b2.empty()) return false;
    const bool directEq = (a1 == b1 && a2 == b2);
    const bool reverseEq = (a1 == b2 && a2 == b1);
    return directEq || reverseEq;
}

bool EdgeLess::operator()(const Edge& a, const Edge& b) const {
    std::string a1 = a.getFirstPointButton() ? a.getFirstPointButton()->getName() : "";
    std::string a2 = a.getSecondPointButton() ? a.getSecondPointButton()->getName() : "";
    std::string b1 = b.getFirstPointButton() ? b.getFirstPointButton()->getName() : "";
    std::string b2 = b.getSecondPointButton() ? b.getSecondPointButton()->getName() : "";
    if (a1 == b1) return a2 < b2;
    return a1 < b1;
}

 
