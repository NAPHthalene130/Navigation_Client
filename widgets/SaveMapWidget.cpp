#include "SaveMapWidget.h"
#include "../mainwindow.h"
#include "../util/ClickedButton.h"
#include "MainWidget.h"
#include <QVBoxLayout>

SaveMapWidget::SaveMapWidget(MainWindow* owner, QWidget* parent)
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

    fileSaveButton = new ClickedButton("文件保存", ClickedButton::textOnLight, ClickedButton::successGreen, this);
    fileSaveButton->setHeight(40);
    fileSaveButton->setFontSize(14);
    layout->addWidget(fileSaveButton);
    connect(fileSaveButton, &QPushButton::clicked, this, &SaveMapWidget::fileSaveButtonClicked);

    netSaveButton = new ClickedButton("云端保存", ClickedButton::textOnLight, ClickedButton::successGreen, this);
    netSaveButton->setHeight(40);
    netSaveButton->setFontSize(14);
    layout->addWidget(netSaveButton);
    connect(netSaveButton, &QPushButton::clicked, this, &SaveMapWidget::netSaveButtonClicked);
}

void SaveMapWidget::fileSaveButtonClicked()
{
    // TODO
}

void SaveMapWidget::netSaveButtonClicked()
{
    // TODO
}
