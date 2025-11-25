#include "mainwindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>
#include <QCoreApplication>

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
    rightWidget->setFixedSize(400,1000);
    layout->addWidget(leftWidget);
    layout->addWidget(rightWidget);
    setFixedSize(1900,1000);

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
