#include "MapConstructorWidget.h"
#include "../mainwindow.h"
#include "../util/ClickedButton.h"
#include "MainWidget.h"
#include <QVBoxLayout>

MapConstructorWidget::MapConstructorWidget(MainWindow* owner, QWidget* parent)
    : QWidget(parent), owner(owner)
{
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(8,8,8,8);
    layout->setSpacing(8);

    backButton = new ClickedButton("返回主界面", ClickedButton::textOnLight, ClickedButton::dangerRed, this);
    backButton->setHeight(40);
    backButton->setFontSize(14);
    layout->addWidget(backButton);

    addPointButton = new ClickedButton("添加路径点", ClickedButton::textOnLight, ClickedButton::secondaryGray, this);
    addPointButton->setHeight(40);
    addPointButton->setFontSize(14);
    layout->addWidget(addPointButton);
    connect(addPointButton, &QPushButton::clicked, this, [this]() {
        this->owner->setMouseClickedType(MainWindow::ADD_POINT);
        this->refreshAddPointButtonStyle();
    });
    refreshAddPointButtonStyle();

    connect(backButton, &QPushButton::clicked, this, [this]() {
        this->owner->setMouseClickedType(0);
        this->owner->changeRightWidgetShow(this->owner->getMainWidget());
    });
}

void MapConstructorWidget::refreshAddPointButtonStyle()
{
    int t = owner->getMouseClickedType();
    if (t == MainWindow::ADD_POINT) {
        addPointButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
    } else {
        addPointButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
    }
}

void MapConstructorWidget::resetTempMapDataContainer()
{
    tempMapDataContainer = new MapDataContainer();
}
