#include "LoadMapWidget.h"
#include "../mainwindow.h"
#include "../util/ClickedButton.h"
#include "MainWidget.h"
#include <QVBoxLayout>

LoadMapWidget::LoadMapWidget(MainWindow* owner, QWidget* parent)
    : QWidget(parent), owner(owner)
{
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(8,8,8,8);
    layout->setSpacing(8);

    backButton = new ClickedButton("返回主界面", ClickedButton::textOnLight, ClickedButton::dangerRed, this);
    backButton->setHeight(40);
    backButton->setFontSize(14);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, [this]() {
        this->owner->setMouseClickedType(0);
        this->owner->changeRightWidgetShow(this->owner->getMainWidget());
        if (this->owner->mapDataContainer) {
             this->owner->displayPoints(this->owner->mapDataContainer);
        }
    });

    fileLoadButton = new ClickedButton("文件导入", ClickedButton::textOnLight, ClickedButton::successGreen, this);
    fileLoadButton->setHeight(40);
    fileLoadButton->setFontSize(14);
    layout->addWidget(fileLoadButton);
    connect(fileLoadButton, &QPushButton::clicked, this, &LoadMapWidget::fileLoadButtonClicked);

    netLoadButton = new ClickedButton("云端导入", ClickedButton::textOnLight, ClickedButton::successGreen, this);
    netLoadButton->setHeight(40);
    netLoadButton->setFontSize(14);
    layout->addWidget(netLoadButton);
    connect(netLoadButton, &QPushButton::clicked, this, &LoadMapWidget::netLoadButtonClicked);

    okButton = new ClickedButton("确认构建", ClickedButton::textOnLight, ClickedButton::primaryBlue, this);
    okButton->setHeight(40);
    okButton->setFontSize(14);
    layout->addWidget(okButton);
    connect(okButton, &QPushButton::clicked, this, &LoadMapWidget::okButtonClicked);
}

void LoadMapWidget::resetTempMapDataContainer()
{
    tempMapDataContainer = new MapDataContainer();
}

void LoadMapWidget::fileLoadButtonClicked()
{
    // TODO
}

void LoadMapWidget::netLoadButtonClicked()
{
    // TODO
}

void LoadMapWidget::okButtonClicked()
{
    // TODO
}
