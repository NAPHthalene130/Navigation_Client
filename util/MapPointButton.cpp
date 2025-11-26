#include "MapPointButton.h"

MapPointButton::MapPointButton(QWidget* parent)
    : QPushButton(parent)
{
    setFixedSize(20,20);
    setFlat(true);
    applyStyle();
}

MapPointButton::MapPointButton(int type)
    : QPushButton(nullptr)
{
    setFixedSize(20,20);
    setFlat(true);
    setType(type);
    applyStyle();
}

void MapPointButton::applyStyle()
{
    QString color = (type == ROUTE_MARK)
        ? QString("rgb(108,117,125)")
        : QString("rgb(40,167,69)");
    QString style = QString(
        "QPushButton{"
        "background: transparent;"
        "border-radius: 10px;"
        "border: 2px solid %1;"
        "}"
        "QPushButton:hover{"
        "background: rgba(0,0,0,0.06);"
        "}"
    ).arg(color);
    setStyleSheet(style);
}

int MapPointButton::getX() const { return x; }
void MapPointButton::setX(int v) { x = v; }
int MapPointButton::getY() const { return y; }
void MapPointButton::setY(int v) { y = v; }
int MapPointButton::getType() const { return type; }
void MapPointButton::setType(int v) { type = v; }
std::string MapPointButton::getName() const { return name; }
void MapPointButton::setName(const std::string& n) { name = n; }
std::string MapPointButton::getContent() const { return content; }
void MapPointButton::setContent(const std::string& c) { content = c; }
