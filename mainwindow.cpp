#include "mainwindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QSizePolicy>

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
    leftLayout->addWidget(nowShow, 0, Qt::AlignCenter);
    nowShow->show();
    currentLeft = nowShow;
}
