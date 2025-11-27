#include "addPointWidget.h"
#include "../util/ClickedButton.h"
#include "../util/MapDataContainer.h"
#include "../mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include "../util/MapPointButton.h"

AddPointWidget::AddPointWidget(MainWindow* mainWindow, QWidget* parent,MapDataContainer *tempMapDataContainer)
    : QWidget(parent), mainWindow(mainWindow),tempMapDataContainer(tempMapDataContainer)
{
    nowX = mainWindow->getNowClickedX();
    nowY = mainWindow->getNowClickedY();
    setWindowTitle("添加点");
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setFixedSize(460, 340);
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    this->setStyleSheet("AddPointWidget{background:#eef2f7;}");

    auto* card = new QFrame(this);
    card->setObjectName("card");
    card->setStyleSheet("#card{background:#ffffff;border-radius:16px;}");
    auto* shadow = new QGraphicsDropShadowEffect(card);
    shadow->setBlurRadius(30);
    shadow->setOffset(0,8);
    shadow->setColor(QColor(0,0,0,72));
    card->setGraphicsEffect(shadow);
    layout->addWidget(card);

    auto* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(18,18,18,18);
    cardLayout->setSpacing(12);
    card->setLayout(cardLayout);

    card->setStyleSheet(card->styleSheet() + " QLabel{font-size:14px;color:#111827;font-weight:600;} QComboBox,QLineEdit,QTextEdit{background:#ffffff;border:1px solid #e5e7eb;border-radius:10px;padding:8px 10px; font-size:14px;} QComboBox:focus,QLineEdit:focus,QTextEdit:focus{border:1px solid #2563eb; box-shadow:0 0 0 3px rgba(37,99,235,0.15);} QTextEdit{min-height:110px;}");

    auto* typeRow = new QHBoxLayout();
    auto* typeLabel = new QLabel("类型", card);
    typeCombo = new QComboBox(card);
    typeCombo->addItem("路径点");
    typeCombo->addItem("景点");
    typeRow->addWidget(typeLabel);
    typeRow->addWidget(typeCombo);
    cardLayout->addLayout(typeRow);

    auto* sep1 = new QFrame(card);
    sep1->setFrameShape(QFrame::HLine);
    sep1->setFixedHeight(1);
    sep1->setStyleSheet("QFrame{background:#e5e7eb;}");
    cardLayout->addWidget(sep1);

    auto* nameRow = new QHBoxLayout();
    auto* nameLabel = new QLabel("节点名称", card);
    nameEdit = new QLineEdit(card);
    nameRow->addWidget(nameLabel);
    nameEdit->setPlaceholderText("请输入节点名称");
    nameRow->addWidget(nameEdit);
    cardLayout->addLayout(nameRow);

    auto* sep2 = new QFrame(card);
    sep2->setFrameShape(QFrame::HLine);
    sep2->setFixedHeight(1);
    sep2->setStyleSheet("QFrame{background:#e5e7eb;}");
    cardLayout->addWidget(sep2);

    auto* contentLabel = new QLabel("节点介绍", card);
    contentLabel->setStyleSheet("font-size:13px;color:#6b7280; margin-bottom:4px; font-weight:600;");
    contentEdit = new QTextEdit(card);
    contentEdit->setPlainText("无");
    cardLayout->addWidget(contentLabel);
    cardLayout->addWidget(contentEdit);

    auto* sep3 = new QFrame(card);
    sep3->setFrameShape(QFrame::HLine);
    sep3->setFixedHeight(1);
    sep3->setStyleSheet("QFrame{background:#e5e7eb;}");
    cardLayout->addWidget(sep3);

    auto* btnRow = new QHBoxLayout();
    cancelButton = new ClickedButton("取消", ClickedButton::textOnLight, ClickedButton::dangerRed, card);
    cancelButton->setHeight(36);
    cancelButton->setFontSize(14);
    okButton = new ClickedButton("确定", ClickedButton::textOnLight, ClickedButton::successGreen, card);
    okButton->setHeight(36);
    okButton->setFontSize(14);
    btnRow->addStretch(1);
    btnRow->addWidget(cancelButton);
    btnRow->addWidget(okButton);
    cardLayout->addLayout(btnRow);

    connect(cancelButton, &QPushButton::clicked, this, &AddPointWidget::cancelButtonClicked);
    connect(okButton, &QPushButton::clicked, this, &AddPointWidget::okButtonCliked);

    centerInParent();
}

void AddPointWidget::cancelButtonClicked()
{
    close();
    deleteLater();
}

void AddPointWidget::okButtonCliked()
{
    // TODO: 确定新增点逻辑，写入 container
    std::string typeStr = typeCombo->currentText().toStdString();
    std::string name = nameEdit->text().toStdString();
    std::string content = contentEdit->toPlainText().toStdString();
    int type = typeStr == "路径点" ? MapPointButton::ROUTE_MARK : MapPointButton::SCENIC_SPOT;
    MapPointButton* point = new MapPointButton(type);
    point->setName(name);
    point->setContent(content);
    bool nameSameFlag = false;
    auto* container = tempMapDataContainer;
    if (!container) {
        close();
        return;
    }
    for (auto& p : container->pointButtonContainer) {
        if (p->getName() == name) {
            nameSameFlag = true;
            break;
        }
    }
    if (nameSameFlag) {
        QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("提示");
    msgBox->setText("已有名字相同的节点");
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setStyleSheet(
        "QMessageBox {"
        "    background-color: #f7f7f7;"
        "    border: 1px solid #dcdcdc;"
        "    border-radius: 8px;"
        "}"
        "QMessageBox QLabel {"
        "    color: #333333;"
        "    padding: 10px;"
        "}"
        "QMessageBox QPushButton {"
        "    background-color: #ffffff;"
        "    border: 1px solid #cccccc;"
        "    border-radius: 4px;"
        "    padding: 5px 15px;"
        "    min-width: 80px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "    background-color: #e6e6e6;"
        "}"
    );

    msgBox->exec();
    delete msgBox;
    return;
    } else {
        tempMapDataContainer->pointButtonContainer.push_back(point);
    }
    mainWindow->displayPoints(tempMapDataContainer);
    close();
}

void AddPointWidget::centerInParent()
{
    QWidget* p = parentWidget();
    if (p) {
        QPoint center = p->mapToGlobal(QPoint(p->width()/2, p->height()/2));
        move(center.x() - width()/2, center.y() - height()/2);
    } else {
        QScreen* s = QGuiApplication::primaryScreen();
        if (s) {
            QRect r = s->geometry();
            move(r.center().x() - width()/2, r.center().y() - height()/2);
        }
    }
}
