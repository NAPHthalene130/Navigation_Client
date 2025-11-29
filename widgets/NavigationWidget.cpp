#include "NavigationWidget.h"
#include "../mainwindow.h"
#include "../util/ClickedButton.h"
#include "MainWidget.h"
#include "MapPointButton.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <vector>
#include <map>
#include <cmath>
#include "Edge.h"

NavigationWidget::NavigationWidget(MainWindow* owner, QWidget* parent)
    : QWidget(parent), owner(owner)
{
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(8);

    backButton = new ClickedButton("返回主界面", ClickedButton::textOnLight, ClickedButton::dangerRed, this);
    backButton->setHeight(40);
    backButton->setFontSize(14);
    layout->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, this, &NavigationWidget::backButtonClicked);

    vipeButton = new ClickedButton("最优水管铺设", ClickedButton::textOnLight, ClickedButton::secondaryGray, this);
    vipeButton->setHeight(40);
    vipeButton->setFontSize(14);
    layout->addWidget(vipeButton);
    connect(vipeButton, &QPushButton::clicked, this, &NavigationWidget::vipeButtonClicked);

    navigationButton = new ClickedButton("路径导航", ClickedButton::textOnLight, ClickedButton::secondaryGray, this);
    navigationButton->setHeight(40);
    navigationButton->setFontSize(14);
    layout->addWidget(navigationButton);
    connect(navigationButton, &QPushButton::clicked, this, &NavigationWidget::navigationButtonClicked);

    infoButton = new ClickedButton("景点信息", ClickedButton::textOnLight, ClickedButton::secondaryGray, this);
    infoButton->setHeight(40);
    infoButton->setFontSize(14);
    layout->addWidget(infoButton);
    connect(infoButton, &QPushButton::clicked, this, &NavigationWidget::infoButtonClicked);

    infoShowWidget = new QWidget(this);
    infoShowWidget->setMinimumHeight(600);
    infoShowWidget->setStyleSheet("QWidget { border: 1px solid gray; border-radius: 8px; background-color: white; }");
    infoLayout = new QVBoxLayout(infoShowWidget);
    infoLayout->setContentsMargins(4, 4, 4, 4);
    infoLayout->setSpacing(0);
    layout->addWidget(infoShowWidget);

    QLabel* defaultLabel = new QLabel("请选择需要查看的路径点", infoShowWidget);
    defaultLabel->setAlignment(Qt::AlignCenter);
    defaultLabel->setStyleSheet("QLabel { border: none; color: lightgray; font-size: 14px; }");
    switchInfoShowWidget(defaultLabel);

    layout->addStretch(1);

    buttonColorUpdate();
}

void NavigationWidget::backButtonClicked()
{
    setFirstClickedButtonName("");
    setSecondClickedButtonName("");
    setClickedNum(0);
    if (owner) {
        owner->setMouseClickedType(0);
        owner->changeRightWidgetShow(owner->getMainWidget());
    }
}

void NavigationWidget::vipeButtonClicked()
{
    if (owner) {
        owner->setMouseClickedType(MainWindow::PIPE);
        buttonColorUpdate();
    }
    std::vector<MapPointButton*> indexToPoint(owner->getMapDataContainer()->pointButtonContainer.size()+1,nullptr);
    std::map<MapPointButton*,int>  pointToIndex;
    std::map<std::string,MapPointButton*> nameToPoint;
    int index = 1;
    for (auto point : owner->getMapDataContainer()->pointButtonContainer) {
        indexToPoint[index] = point;
        pointToIndex[point] = index;
        nameToPoint[point->getName()] = point;
        index++;
    }
    
    std::vector<std::vector<double>> mat(indexToPoint.size(),std::vector<double>(indexToPoint.size(),INT_MAX));
    for (auto edge: owner->getMapDataContainer()->edgeContainer) {
        std::string name1 = edge->getFirstPointButton()->getName();
        std::string name2 = edge->getSecondPointButton()->getName();
        int index1 = pointToIndex[nameToPoint[name1]];
        int index2 = pointToIndex[nameToPoint[name2]];
        int x1 = edge->getFirstPointButton()->getX();
        int y1 = edge->getFirstPointButton()->getY();
        int x2 = edge->getSecondPointButton()->getX();
        int y2 = edge->getSecondPointButton()->getY();
        double dis = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        mat[index1][index2] = dis;
        mat[index2][index1] = dis;
    }

    

}

void NavigationWidget::navigationButtonClicked()
{
    setClickedNum(0);
    setFirstClickedButtonName("");
    setSecondClickedButtonName("");
    if (owner) {
        owner->setMouseClickedType(MainWindow::NAVIGATION);
        buttonColorUpdate();
    }
}

void NavigationWidget::infoButtonClicked()
{
    // TODO 稍后完成
    if (owner) {
        owner->setMouseClickedType(MainWindow::INFO);
        buttonColorUpdate();
    }
}

void NavigationWidget::switchInfoShowWidget(QWidget* infoWidget)
{
    if (!infoLayout) return;

    // Clear existing items
    QLayoutItem* item;
    while ((item = infoLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }

    if (infoWidget) {
        infoLayout->addWidget(infoWidget);
    }
}

void NavigationWidget::buttonColorUpdate()
{
    if (!owner) return;
    int t = owner->getMouseClickedType();
    
    // Vipe Button
    if (t == MainWindow::PIPE) {
        vipeButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
    } else {
        vipeButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
    }

    // Navigation Button
    if (t == MainWindow::NAVIGATION) {
        if (clickedButtonNum == 0) {
            navigationButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
        } else if (clickedButtonNum == 1) {
            navigationButton->setColors(ClickedButton::textOnLight, ClickedButton::warningAmber);
        } else {
             // Fallback if needed, but requirements only specify 0 and 1
             navigationButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
        }
    } else {
        navigationButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
    }

    // Info Button
    if (t == MainWindow::INFO) {
        infoButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
    } else {
        infoButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
    }
}
