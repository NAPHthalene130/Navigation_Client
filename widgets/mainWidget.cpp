#include "mainWidget.h"
#include "../util/ClickedButton.h"
#include "../mainwindow.h"
#include "MapConstructorWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QCoreApplication>
#include "../util/MapDataContainer.h"
#include "../util/MapPointButton.h"
#include <iostream>
#include "../util/DebugDialog.h"
MainWidget::MainWidget(MainWindow* owner, QWidget* parent)
    : QWidget(parent), owner_(owner), layout_(new QVBoxLayout(this))
{
    layout_->setContentsMargins(12,12,12,12);
    layout_->setSpacing(12);
    auto* title = new QLabel("功能选择", this);
    title->setStyleSheet("font-size:20px;font-weight:600;padding:4px 0;");
    layout_->addWidget(title);
    buttons_.clear();
    mapFunctionButton = new ClickedButton("导航功能", ClickedButton::textOnDark, ClickedButton::primaryBlue, this);
    mapFunctionButton->setHeight(48);
    mapFunctionButton->setFontSize(16);
    addButton(mapFunctionButton);
    mapConstructorButton = new ClickedButton("构建地图", ClickedButton::textOnLight, ClickedButton::accentPurple, this);
    mapConstructorButton->setHeight(48);
    mapConstructorButton->setFontSize(16);
    addButton(mapConstructorButton);
    loadMapButton = new ClickedButton("加载地图", ClickedButton::textOnDark, ClickedButton::successGreen, this);
    loadMapButton->setHeight(48);
    loadMapButton->setFontSize(16);
    addButton(loadMapButton);
    saveMaButton = new ClickedButton("导出地图", ClickedButton::textOnLight, ClickedButton::warningAmber, this);
    saveMaButton->setHeight(48);
    saveMaButton->setFontSize(16);
    addButton(saveMaButton);
    exitButton = new ClickedButton("退出地图", ClickedButton::textOnLight, ClickedButton::dangerRed, this);
    exitButton->setHeight(48);
    exitButton->setFontSize(16);
    addButton(exitButton);
    connect(mapFunctionButton, &QPushButton::clicked, this, &MainWidget::mapFunctionButtonClicked);
    connect(mapConstructorButton, &QPushButton::clicked, this, &MainWidget::mapConstructorButtonClicked);
    connect(loadMapButton, &QPushButton::clicked, this, &MainWidget::loadMapButtonClicked);
    connect(saveMaButton, &QPushButton::clicked, this, &MainWidget::saveMaButtonClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainWidget::exitButtonClicked);
    layout_->addStretch(1);
}

void MainWidget::addButton(ClickedButton* button)
{
    buttons_.push_back(button);
    layout_->addWidget(button);
}

void MainWidget::deleteButton(const QString& line)
{
    for (auto it = buttons_.begin(); it != buttons_.end(); ) {
        if ((*it)->text() == line) {
            (*it)->hide();
            (*it)->deleteLater();
            it = buttons_.erase(it);
        } else {
            ++it;
        }
    }
}

void MainWidget::mapFunctionButtonClicked()
{
}

void MainWidget::mapConstructorButtonClicked()
{
    // new DebugDialog("TEST1","TES1");
    owner_->changeRightWidgetShow(owner_->getMapConstructorWidget());
    owner_->getMapConstructorWidget()->resetTempMapDataContainer();
    for (auto point : owner_->getMapDataContainer()->pointButtonContainer) {
        point->hide();
        auto* newPoint = new MapPointButton(point);
        owner_->getMapConstructorWidget()->tempMapDataContainer->addMapPointButton(newPoint);
    }
    owner_->displayPoints(owner_->getMapConstructorWidget()->tempMapDataContainer);
}

void MainWidget::loadMapButtonClicked()
{
}

void MainWidget::saveMaButtonClicked()
{
}

void MainWidget::exitButtonClicked()
{
    QCoreApplication::quit();
}
