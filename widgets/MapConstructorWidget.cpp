#include "MapConstructorWidget.h"
#include "../mainwindow.h"
#include "../util/ClickedButton.h"
#include "MainWidget.h"
#include <QVBoxLayout>
#include "../util/Edge.h"
#include "../util/MapPointButton.h"

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
        this->buttonColorUpdate();
    });

    deletePointButton = new ClickedButton("删除路径点", ClickedButton::textOnLight, ClickedButton::secondaryGray, this);
    deletePointButton->setHeight(40);
    deletePointButton->setFontSize(14);
    layout->addWidget(deletePointButton);
    connect(deletePointButton, &QPushButton::clicked, this, [this]() {
        this->owner->setMouseClickedType(MainWindow::DELETE_POINT);
        this->buttonColorUpdate();
    });

    addEdgeButton = new ClickedButton("添加边", ClickedButton::textOnLight, ClickedButton::secondaryGray, this);
    addEdgeButton->setHeight(40);
    addEdgeButton->setFontSize(14);
    layout->addWidget(addEdgeButton);
    connect(addEdgeButton, &QPushButton::clicked, this, [this]() {
        this->owner->setMouseClickedType(MainWindow::ADD_EDGE);
        this->buttonColorUpdate();
    });

    deleteEdgeButton = new ClickedButton("删除边", ClickedButton::textOnLight, ClickedButton::secondaryGray, this);
    deleteEdgeButton->setHeight(40);
    deleteEdgeButton->setFontSize(14);
    layout->addWidget(deleteEdgeButton);
    connect(deleteEdgeButton, &QPushButton::clicked, this, [this]() {
        this->owner->setMouseClickedType(MainWindow::DELETE_EDGE);
        this->buttonColorUpdate();
    });

    saveButton = new ClickedButton("保存地图", ClickedButton::textOnLight, ClickedButton::primaryBlue, this);
    saveButton->setHeight(40);
    saveButton->setFontSize(14);
    layout->addWidget(saveButton);
    connect(saveButton, &QPushButton::clicked, this, &MapConstructorWidget::savePointButtonClicked);
    buttonColorUpdate();

    connect(backButton, &QPushButton::clicked, this, [this]() {
        this->owner->setMouseClickedType(0);
        this->owner->changeRightWidgetShow(this->owner->getMainWidget());
        this->owner->displayPoints(this->owner->mapDataContainer);
    });
}

void MapConstructorWidget::refreshAddPointButtonStyle()
{
    buttonColorUpdate();
}

void MapConstructorWidget::buttonColorUpdate()
{
    int t = owner->getMouseClickedType();
    int c = owner && owner->leftWidget ? owner->leftWidget->clickedButtonNum : 0;

    if (t == MainWindow::ADD_POINT) {
        addPointButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
    } else {
        addPointButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
    }

    if (t == MainWindow::DELETE_POINT) {
        deletePointButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
    } else {
        deletePointButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
    }

    if (addEdgeButton) {
        if (t == MainWindow::ADD_EDGE) {
            if (c == 0) {
                addEdgeButton->setColors(ClickedButton::textOnLight, ClickedButton::warningAmber);
            } else {
                addEdgeButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
            }
        } else {
            addEdgeButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
        }
    }

    if (deleteEdgeButton) {
        if (t == MainWindow::DELETE_EDGE) {
            if (c == 0) {
                deleteEdgeButton->setColors(ClickedButton::textOnLight, ClickedButton::warningAmber);
            } else {
                deleteEdgeButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
            }
        } else {
            deleteEdgeButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
        }
    }
}

void MapConstructorWidget::resetTempMapDataContainer()
{
    tempMapDataContainer = new MapDataContainer();
}

void MapConstructorWidget::savePointButtonClicked()
{
    if (!owner) return;

    owner->changeRightWidgetShow(owner->getMainWidget());
    owner->setMouseClickedType(0);

    MapDataContainer* mainMap = owner->getMapDataContainer();
    if (mainMap) {
        for (auto* edge : mainMap->edgeContainer) {
            delete edge;
        }
        mainMap->edgeContainer.clear();

        for (auto* point : mainMap->pointButtonContainer) {
            point->deleteLater();
        }
        mainMap->pointButtonContainer.clear();

        if (tempMapDataContainer) {
            mainMap->pointButtonContainer = tempMapDataContainer->pointButtonContainer;
            mainMap->edgeContainer = tempMapDataContainer->edgeContainer;

            tempMapDataContainer->pointButtonContainer.clear();
            tempMapDataContainer->edgeContainer.clear();
        }
        
        owner->displayPoints(mainMap);
    }
}
