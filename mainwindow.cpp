#include "mainwindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QDir>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QSizePolicy>
#include "widgets/mainWidget.h"
#include "util/MapDataContainer.h"
#include "util/MapPointButton.h"
#include "util/Edge.h"
#include "widgets/leftWidget.h"
#include "widgets/mapConstructorWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout* layout = new QHBoxLayout(central);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    leftWidget = new LeftWidget(this, central);
    rightWidget = new QWidget(central);
    leftWidget->setFixedSize(1500,1000);
    leftWidget->setStyleSheet("border: 1px solid #444444;");
    rightWidget->setFixedSize(400,1000);
    layout->addWidget(leftWidget);
    layout->addWidget(rightWidget);
    setFixedSize(1900,1000);
    leftLayout = nullptr;
    rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setContentsMargins(8,8,8,8);
    rightLayout->setSpacing(8);
    currentLeft = nullptr;
    mapDataContainer = new MapDataContainer();

    mainWidget = new MainWidget(this, rightWidget);
    mapConstructorWidget = new MapConstructorWidget(this, rightWidget);
    changeRightWidgetShow(mainWidget);

    auto* t1 = new MapPointButton(MapPointButton::ROUTE_MARK, this);
    t1->setX(120); t1->setY(160); t1->setName("TEST_POINT_1");
    mapDataContainer->addMapPointButton(t1);
    auto* t2 = new MapPointButton(MapPointButton::SCENIC_SPOT, this);
    t2->setX(480); t2->setY(300); t2->setName("TEST_POINT_2");
    mapDataContainer->addMapPointButton(t2);
    auto* t3 = new MapPointButton(MapPointButton::SCENIC_SPOT, this);
    t3->setX(990); t3->setY(990); t3->setName("TEST_POINT_3");
    mapDataContainer->addMapPointButton(t3);

    //下面拿来测试
    Edge* e1 = new Edge(t1, t2);
    e1->setType(0);
    Edge* e2 = new Edge(t2, t3);
    e2->setType(1);
    Edge* e3 = new Edge(t1, t3);
    e3->setType(2);
    mapDataContainer->edgeContainer.push_back(e1);
    mapDataContainer->edgeContainer.push_back(e2);
    mapDataContainer->edgeContainer.push_back(e3);
    //上面拿来测试
    displayPoints(mapDataContainer);
}

MainWindow::~MainWindow() {}

void MainWindow::displayPoints(MapDataContainer* mapDataContainer)
{
    if (!mapDataContainer) return;
    leftWidget->drawWidget(*mapDataContainer);
}

void MainWindow::changeRightWidgetShow(QWidget* nowShow)
{
    if (!rightLayout) {
        rightLayout = new QVBoxLayout(rightWidget);
        rightLayout->setContentsMargins(0,0,0,0);
        rightLayout->setSpacing(0);
    }
    while (rightLayout->count() > 0) {
        QLayoutItem* it = rightLayout->takeAt(0);
        if (it) {
            if (it->widget()) it->widget()->setParent(nullptr);
            delete it;
        }
    }
    const auto children = rightWidget->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly);
    for (QWidget* w : children) {
        if (w != nowShow) w->hide();
    }
    if (nowShow->parent() != rightWidget) nowShow->setParent(rightWidget);
    rightLayout->addWidget(nowShow);
    nowShow->show();
}

int MainWindow::getNowClickedX() { return leftWidget->nowClickedX; }
int MainWindow::getNowClickedY() { return leftWidget->nowClickedY; }


int MainWindow::getMouseClickedType() const { return mouseClickedType; }
void MainWindow::setMouseClickedType(int t) { mouseClickedType = t; if (mapConstructorWidget) mapConstructorWidget->buttonColorUpdate(); }
MainWidget* MainWindow::getMainWidget() const { return mainWidget; }
MapConstructorWidget* MainWindow::getMapConstructorWidget() const { return mapConstructorWidget; }
MapDataContainer* MainWindow::getMapDataContainer() const { return mapDataContainer; }
