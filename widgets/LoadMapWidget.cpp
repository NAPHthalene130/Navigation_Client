#include "LoadMapWidget.h"
#include "../mainwindow.h"
#include "../util/ClickedButton.h"
#include "../util/MapPointButton.h"
#include "LeftWidget.h"
#include "MainWidget.h"
#include "MapDataContainer.h"
#include "NoticeDialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFrame>
#include <QFileDialog>
#include <QStandardPaths>
#include "../util/DataIO.h"

LoadMapWidget::LoadMapWidget(MainWindow* owner, QWidget* parent)
    : QWidget(parent), owner(owner)
{
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(8,8,8,8);
    layout->setSpacing(16);

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

    QFrame* line1 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Plain);
    line1->setStyleSheet("color: #DDDDDD; background-color: #DDDDDD; border: none; min-height: 1px; max-height: 1px;");
    layout->addWidget(line1);

    fileSelectButton = new ClickedButton("选择文件", ClickedButton::textOnLight, ClickedButton::primaryBlue, this);
    fileSelectButton->setHeight(40);
    fileSelectButton->setFontSize(14);
    layout->addWidget(fileSelectButton);
    connect(fileSelectButton, &QPushButton::clicked, this, &LoadMapWidget::selectFileButtonClicked);

    filePathLine = new QLineEdit(this);
    filePathLine->setPlaceholderText("未选择文件");
    filePathLine->setAlignment(Qt::AlignCenter);
    filePathLine->setFixedHeight(40);
    filePathLine->setReadOnly(true);
    QFont dirFont = filePathLine->font();
    dirFont.setPixelSize(14);
    filePathLine->setFont(dirFont);
    filePathLine->setStyleSheet("QLineEdit { border: 1px solid #CCCCCC; border-radius: 4px; color: #555555; background-color: #F0F0F0; }");
    layout->addWidget(filePathLine);

    fileLoadButton = new ClickedButton("文件导入", ClickedButton::textOnLight, ClickedButton::successGreen, this);
    fileLoadButton->setHeight(40);
    fileLoadButton->setFontSize(14);
    layout->addWidget(fileLoadButton);
    connect(fileLoadButton, &QPushButton::clicked, this, &LoadMapWidget::fileLoadButtonClicked);

    QFrame* line2 = new QFrame();
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Plain);
    line2->setStyleSheet("color: #DDDDDD; background-color: #DDDDDD; border: none; min-height: 1px; max-height: 1px;");
    layout->addWidget(line2);

    tokenTextLine = new QLineEdit(this);
    tokenTextLine->setPlaceholderText("请输入TOKEN");
    tokenTextLine->setAlignment(Qt::AlignCenter);
    tokenTextLine->setFixedHeight(40);
    QFont tokenFont = tokenTextLine->font();
    tokenFont.setPixelSize(14);
    tokenTextLine->setFont(tokenFont);
    tokenTextLine->setStyleSheet("QLineEdit { border: 1px solid #CCCCCC; border-radius: 4px; color: #333333; background-color: white; } QLineEdit:focus { border: 1px solid #66AFE9; }");
    layout->addWidget(tokenTextLine);

    netLoadButton = new ClickedButton("云端导入", ClickedButton::textOnLight, ClickedButton::successGreen, this);
    netLoadButton->setHeight(40);
    netLoadButton->setFontSize(14);
    layout->addWidget(netLoadButton);
    connect(netLoadButton, &QPushButton::clicked, this, &LoadMapWidget::netLoadButtonClicked);

    QFrame* line3 = new QFrame();
    line3->setFrameShape(QFrame::HLine);
    line3->setFrameShadow(QFrame::Plain);
    line3->setStyleSheet("color: #DDDDDD; background-color: #DDDDDD; border: none; min-height: 1px; max-height: 1px;");
    layout->addWidget(line3);

    okButton = new ClickedButton("确认构建", ClickedButton::textOnLight, ClickedButton::primaryBlue, this);
    okButton->setHeight(40);
    okButton->setFontSize(14);
    layout->addWidget(okButton);
    connect(okButton, &QPushButton::clicked, this, &LoadMapWidget::okButtonClicked);

    layout->addStretch();

    tempMapDataContainer = new MapDataContainer();
}

void LoadMapWidget::resetTempMapDataContainer()
{
    tempMapDataContainer = new MapDataContainer();
}

void LoadMapWidget::selectFileButtonClicked()
{
    QString file = QFileDialog::getOpenFileName(this, "选择地图文件",
                                                QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                "Map Files (*.map *.json *.txt);;All Files (*)");
    if (!file.isEmpty()) {
        filePathLine->setText(file);
    }
}

void LoadMapWidget::fileLoadButtonClicked()
{
    tempMapDataContainer->reset();
    owner->displayPoints(tempMapDataContainer);

    std::filesystem::path path = filePathLine->text().toStdString();
    if (!std::filesystem::exists(path)) {
        new NoticeDialog("错误", "文件不存在");
        return;
    }
    MapDataContainer* container = DataIO::readFile(path.string());
    if (!container) {
        new NoticeDialog("错误", "文件读取失败");
        return;
    }
    for (auto pointButton : container->pointButtonContainer) {
        pointButton->setMainWindow(owner);
        tempMapDataContainer->addMapPointButton(pointButton);
    }
    for (auto edge : container->edgeContainer) {
        tempMapDataContainer->edgeContainer.push_back(edge);
    }
    delete container;
    owner->displayPoints(tempMapDataContainer);
}

void LoadMapWidget::netLoadButtonClicked()
{
    
}

void LoadMapWidget::okButtonClicked()
{
    if (owner->mapDataContainer) {
        owner->mapDataContainer->reset();
        delete owner->mapDataContainer;
    }
    owner->mapDataContainer = tempMapDataContainer;
    tempMapDataContainer = new MapDataContainer();
    owner->setMouseClickedType(0);
    owner->changeRightWidgetShow(owner->getMainWidget());
}
