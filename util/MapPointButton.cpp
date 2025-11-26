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
    QString brightColor;
    QString darkColor;

    if (type == ROUTE_MARK) {
        brightColor = QString("rgb(180, 190, 200)");
        darkColor = QString("rgb(140, 150, 160)");
    } else {
        brightColor = QString("rgb(144, 238, 144)");
        darkColor = QString("rgb(100, 180, 100)");
    }

    QString style = QString(
        "QPushButton{"
        "background: %1;"
        "border-radius: 10px;"
        "border: 2px solid black;"
        "}"
        "QPushButton:hover{"
        "background: %2;"
        "}"
    ).arg(brightColor, darkColor);
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