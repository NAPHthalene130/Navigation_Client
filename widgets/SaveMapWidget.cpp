#include "SaveMapWidget.h"
#include "../mainwindow.h"
#include "../util/ClickedButton.h"
#include "MainWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFrame>
#include <QFileDialog>
#include <QStandardPaths>
#include "../util/DataIO.h"
#include "NoticeDialog.h"
#include <boost/asio.hpp>
#include "../util/MapPointButton.h"
#include "../util/Edge.h"
SaveMapWidget::SaveMapWidget(MainWindow* owner, QWidget* parent)
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

    dirSelectButton = new ClickedButton("选择保存目录", ClickedButton::textOnLight, ClickedButton::primaryBlue, this);
    dirSelectButton->setHeight(40);
    dirSelectButton->setFontSize(14);
    layout->addWidget(dirSelectButton);
    connect(dirSelectButton, &QPushButton::clicked, this, &SaveMapWidget::selectDirButtonClicked);

    dirPathLine = new QLineEdit(this);
    dirPathLine->setPlaceholderText("未选择目录");
    dirPathLine->setAlignment(Qt::AlignCenter);
    dirPathLine->setFixedHeight(40);
    dirPathLine->setReadOnly(true);
    QFont dirFont = dirPathLine->font();
    dirFont.setPixelSize(14);
    dirPathLine->setFont(dirFont);
    dirPathLine->setStyleSheet("QLineEdit { border: 1px solid #CCCCCC; border-radius: 4px; color: #555555; background-color: #F0F0F0; }");
    layout->addWidget(dirPathLine);

    nameTextLine = new QLineEdit(this);
    nameTextLine->setPlaceholderText("请输入保存文件名");
    nameTextLine->setAlignment(Qt::AlignCenter);
    nameTextLine->setFixedHeight(40);
    QFont nameFont = nameTextLine->font();
    nameFont.setPixelSize(14);
    nameTextLine->setFont(nameFont);
    nameTextLine->setStyleSheet("QLineEdit { border: 1px solid #CCCCCC; border-radius: 4px; color: #333333; background-color: white; } QLineEdit:focus { border: 1px solid #66AFE9; }");
    layout->addWidget(nameTextLine);

    fileSaveButton = new ClickedButton("保存到目录", ClickedButton::textOnLight, ClickedButton::successGreen, this);
    fileSaveButton->setHeight(40);
    fileSaveButton->setFontSize(14);
    layout->addWidget(fileSaveButton);
    connect(fileSaveButton, &QPushButton::clicked, this, &SaveMapWidget::fileSaveButtonClicked);

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

    netSaveButton = new ClickedButton("保存到云端", ClickedButton::textOnLight, ClickedButton::successGreen, this);
    netSaveButton->setHeight(40);
    netSaveButton->setFontSize(14);
    layout->addWidget(netSaveButton);
    connect(netSaveButton, &QPushButton::clicked, this, &SaveMapWidget::netSaveButtonClicked);
    
    layout->addStretch();
}

void SaveMapWidget::selectDirButtonClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "选择保存目录",
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        dirPathLine->setText(dir);
    }
}

void SaveMapWidget::fileSaveButtonClicked()
{
    // TODO
    if (nameTextLine->text().isEmpty()) {
        new NoticeDialog("错误","请输入保存文件名");
        return;
    }
    if (dirPathLine->text().isEmpty()) {
        new NoticeDialog("错误","请选择保存目录");
        return;
    }
    std::filesystem::path rootPath = dirPathLine->text().toStdString();
    std::filesystem::path filePath = rootPath / (nameTextLine->text().toStdString() + ".map");
    DataIO::writeFile(filePath.string(), this->owner->mapDataContainer);
    new NoticeDialog("提示","地图保存成功");
}

void SaveMapWidget::netSaveButtonClicked()
{
    if (tokenTextLine->text().isEmpty()) {
        new NoticeDialog("错误","请输入TOKEN");
        return;
    }
    DataIO::writeNet(this->owner->getIp(),this->owner->getPort(), this->owner->mapDataContainer, tokenTextLine->text().toStdString());
}

