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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout* layout = new QHBoxLayout(central);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    leftWidget = new QWidget(central);
    rightWidget = new QWidget(central);
    leftWidget->setFixedSize(1500,1000);
    leftWidget->setStyleSheet("border: 1px solid #444444;");
    rightWidget->setFixedSize(400,1000);
    layout->addWidget(leftWidget);
    layout->addWidget(rightWidget);
    setFixedSize(1900,1000);
    leftLayout = nullptr;
    currentLeft = nullptr;

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

    MainWidget* mw = new MainWidget(rightWidget);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setContentsMargins(8,8,8,8);
    rightLayout->setSpacing(8);
    rightLayout->addWidget(mw);

    // TEST: add some demo points and display them on the left widget
    // remove or modify these after integration
    MapDataContainer demoContainer;
    auto* t1 = new MapPointButton(MapPointButton::ROUTE_MARK);
    t1->setX(120); t1->setY(160); t1->setName("TEST_POINT_1");
    demoContainer.addMapPointButton(t1);
    auto* t2 = new MapPointButton(MapPointButton::SCENIC_SPOT);
    t2->setX(480); t2->setY(300); t2->setName("TEST_POINT_2");
    demoContainer.addMapPointButton(t2);
    auto* t3 = new MapPointButton(MapPointButton::SCENIC_SPOT);
    t3->setX(0); t3->setY(0); t3->setName("TEST_POINT_3");
    demoContainer.addMapPointButton(t3);
    dispalyPoints(&demoContainer);
}

MainWindow::~MainWindow() {}

void MainWindow::changeLeftWidgetShow(QWidget* nowShow)
{
    if (!leftLayout) {
        leftLayout = new QVBoxLayout(leftWidget);
        leftLayout->setContentsMargins(0,0,0,0);
        leftLayout->setSpacing(0);
    }
    while (leftLayout->count() > 0) {
        QLayoutItem* it = leftLayout->takeAt(0);
        if (it) {
            if (it->widget()) it->widget()->setParent(nullptr);
            delete it;
        }
    }
    const auto children = leftWidget->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly);
    for (QWidget* w : children) {
        if (w != nowShow) w->hide();
    }
    if (nowShow->parent() != leftWidget) nowShow->setParent(leftWidget);
    nowShow->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    leftLayout->addWidget(nowShow);
    nowShow->show();
    currentLeft = nowShow;
}

void MainWindow::dispalyPoints(MapDataContainer* mapDataContainer)
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
