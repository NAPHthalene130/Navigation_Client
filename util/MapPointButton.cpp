#include "MapPointButton.h"
#include "DebugDialog.h"
#include "NoticeDialog.h"
#include "../widgets/MapConstructorWidget.h"
#include "Edge.h"
#include "NoticeDialog.h"

MapPointButton::MapPointButton(MapPointButton* otherButton)
    : QPushButton(nullptr)
{
    if (!otherButton) return;
    x = otherButton->getX();
    y = otherButton->getY();
    type = otherButton->getType();
    name = otherButton->getName();
    content = otherButton->getContent();
    this->mainWindow = otherButton->mainWindow;
    setFixedSize(20,20);
    setFlat(true);
    applyStyle();
    connect(this, &QPushButton::clicked, this, &MapPointButton::clicked);
}

MapPointButton::MapPointButton(QWidget* parent)
    : QPushButton(parent)
{
    setFixedSize(20,20);
    setFlat(true);
    applyStyle();
    connect(this, &QPushButton::clicked, this, &MapPointButton::clicked);
}

MapPointButton::MapPointButton(int type, MainWindow* mainWindow)
    : QPushButton(nullptr)
{
    setFixedSize(20,20);
    setFlat(true);
    setType(type);
    applyStyle();
    this->mainWindow = mainWindow;
    connect(this, &QPushButton::clicked, this, &MapPointButton::clicked);
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

void MapPointButton::clicked()
{
    if (!mainWindow) return;
    if (mainWindow->getMouseClickedType() == MainWindow::DELETE_POINT) {
        auto* container = mainWindow->mapConstructorWidget ? mainWindow->mapConstructorWidget->tempMapDataContainer : nullptr;
        if (!container) return;
        container->deleteButtonByName(this->name);
        container->cleanPointButtonContainerNullptr();
        mainWindow->displayPoints(container);
    } else if (mainWindow->getMouseClickedType() == MainWindow::ADD_EDGE) {
        if (mainWindow->leftWidget->clickedButtonNum == 0) {
            mainWindow->leftWidget->firstClickedPointButton = this;
            mainWindow->leftWidget->clickedButtonNum++;
            if (mainWindow->mapConstructorWidget) mainWindow->mapConstructorWidget->buttonColorUpdate();
        } else if (mainWindow->leftWidget->clickedButtonNum == 1) {
            if (mainWindow->leftWidget->firstClickedPointButton == this) return;
            mainWindow->leftWidget->secondClickedPointButton = this;
            Edge* edge = new Edge(
                mainWindow->leftWidget->firstClickedPointButton,
                mainWindow->leftWidget->secondClickedPointButton
            );
            for (auto tempEdge : mainWindow->mapConstructorWidget->tempMapDataContainer->edgeContainer) {
                if ((edge->getFirstPointButton()->getName() == tempEdge->getFirstPointButton()->getName()) &&
                    edge->getSecondPointButton()->getName() == tempEdge->getSecondPointButton()->getName()) {
                        new NoticeDialog("注意","该路径已存在");
                        return;
                    }
            }
            mainWindow->mapConstructorWidget->tempMapDataContainer->edgeContainer.push_back(edge);
            mainWindow->leftWidget->drawWidget(*mainWindow->mapConstructorWidget->tempMapDataContainer);
            mainWindow->leftWidget->firstClickedPointButton = nullptr;
            mainWindow->leftWidget->secondClickedPointButton = nullptr;
            mainWindow->leftWidget->clickedButtonNum = 0;
            if (mainWindow->mapConstructorWidget) mainWindow->mapConstructorWidget->buttonColorUpdate();
        }
    } else if (mainWindow->getMouseClickedType() == MainWindow::DELETE_EDGE) {
        //删除边的逻辑
        auto* container = mainWindow->mapConstructorWidget ? mainWindow->mapConstructorWidget->tempMapDataContainer : nullptr;
        if (!container) return;
        if (mainWindow->leftWidget->clickedButtonNum == 0) {
            mainWindow->leftWidget->firstClickedPointButton = this;
            mainWindow->leftWidget->clickedButtonNum++;
            if (mainWindow->mapConstructorWidget) mainWindow->mapConstructorWidget->buttonColorUpdate();
        } else if (mainWindow->leftWidget->clickedButtonNum == 1) {
            if (mainWindow->leftWidget->firstClickedPointButton == this) return;
            mainWindow->leftWidget->secondClickedPointButton = this;
            std::string name1 = mainWindow->leftWidget->firstClickedPointButton->getName();
            std::string name2 = mainWindow->leftWidget->secondClickedPointButton->getName();
            for (auto it = container->edgeContainer.begin(); it != container->edgeContainer.end(); ++it) {
                if ((((*it)->getFirstPointButton()->getName() == name1) &&
                    ((*it)->getSecondPointButton()->getName() == name2)) ||
                    ((*it)->getFirstPointButton()->getName() == name2) &&
                    ((*it)->getSecondPointButton()->getName() == name1)) {
                        container->edgeContainer.erase(it);
                        break;
                    }
            }
            mainWindow->leftWidget->drawWidget(*mainWindow->mapConstructorWidget->tempMapDataContainer);
            mainWindow->leftWidget->firstClickedPointButton = nullptr;
            mainWindow->leftWidget->secondClickedPointButton = nullptr;
            mainWindow->leftWidget->clickedButtonNum = 0;
            if (mainWindow->mapConstructorWidget) mainWindow->mapConstructorWidget->buttonColorUpdate();
        }
    }
}
