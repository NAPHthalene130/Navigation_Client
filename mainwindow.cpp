#include "mainwindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QSizePolicy>
#include "widgets/mainWidget.h"
#include "util/MapDataContainer.h"
#include "util/MapPointButton.h"
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

    QLabel* imgLabel = new QLabel(leftWidget);
    imgLabel->setGeometry(0,0,1500,1000);
    imgLabel->setScaledContents(true);
    QString base = QCoreApplication::applicationDirPath() + "/img";
    QDir dir(base);
    QStringList files = dir.entryList({"*.png","*.jpg","*.jpeg","*.bmp"}, QDir::Files);
    if (!files.isEmpty()) {
        QString path = dir.absoluteFilePath(files.first());
        QPixmap pix(path);
        imgLabel->setPixmap(pix.scaled(1500,1000,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

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
    displayPoints(mapDataContainer);
}

MainWindow::~MainWindow() {}

void MainWindow::displayPoints(MapDataContainer* mapDataContainer)
{
    if (!mapDataContainer) return;
    for (auto* btn : mapDataContainer->pointButtonContainer)
    {
        if (!btn) continue;
        if (btn->parentWidget() != leftWidget) btn->setParent(leftWidget);
        btn->move(btn->getX(), btn->getY());
        btn->raise();
        btn->show();
    }
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

int MainWindow::getClickedButtonNum() { return clickedButtonNum; }
void MainWindow::setClickedButtonNum(int num) { clickedButtonNum = num; }

int MainWindow::getMouseClickedType() const { return mouseClickedType; }
void MainWindow::setMouseClickedType(int t) { mouseClickedType = t; if (mapConstructorWidget) mapConstructorWidget->refreshAddPointButtonStyle(); }
MainWidget* MainWindow::getMainWidget() const { return mainWidget; }
MapConstructorWidget* MainWindow::getMapConstructorWidget() const { return mapConstructorWidget; }
MapDataContainer* MainWindow::getMapDataContainer() const { return mapDataContainer; }
