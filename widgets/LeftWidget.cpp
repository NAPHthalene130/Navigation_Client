#include "leftWidget.h"
#include "../mainwindow.h"
#include "AddPointWidget.h"
#include "mapConstructorWidget.h"
#include <QMouseEvent>
#include <qnamespace.h>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QCoreApplication>
#include "../util/Edge.h"

LeftWidget::LeftWidget(MainWindow *owner, QWidget *parent)
    : QWidget(parent), owner(owner) {
  setMouseTracking(true);
  canvasLabel = new QLabel(this);
  canvasLabel->setGeometry(0,0,1500,1000);
  canvasLabel->setScaledContents(true);
}

void LeftWidget::drawWidget(MapDataContainer mapDataContainer)
{
  setFixedSize(1500,1000);
  if (!canvasLabel) {
    canvasLabel = new QLabel(this);
    canvasLabel->setGeometry(0,0,1500,1000);
    canvasLabel->setScaledContents(true);
  }

  QString path = QCoreApplication::applicationDirPath() + "/img/mapPic.png";
  QPixmap basePixmap(path);
  if (basePixmap.isNull()) {
    basePixmap = QPixmap(1500,1000);
    basePixmap.fill(Qt::white);
  } else {
    basePixmap = basePixmap.scaled(1500,1000, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  }

  QPainter painter(&basePixmap);
  painter.setRenderHint(QPainter::Antialiasing, true);
  for (auto* e : mapDataContainer.edgeContainer) {
    if (!e) continue;
    auto* a = e->getFirstPoint();
    auto* b = e->getSecondPointButton();
    if (!a || !b) continue;
    QPen pen;
    if (e->getType() == 0) {
      pen = QPen(QColor(135,206,235), 3); // 天蓝色
    } else if (e->getType() == 1) {
      // TODO: type==1 边颜色设置
      pen = QPen(QColor(135,206,235), 3);
    } else if (e->getType() == 2) {
      // TODO: type==2 边颜色设置
      pen = QPen(QColor(135,206,235), 3);
    }
    painter.setPen(pen);
    painter.drawLine(QPoint(a->getX()+10, a->getY()+10), QPoint(b->getX()+10, b->getY()+10));
  }
  painter.end();

  canvasLabel->setPixmap(basePixmap);
  canvasLabel->show();
  canvasLabel->raise();

  for (auto* btn : mapDataContainer.pointButtonContainer) {
    if (!btn) continue;
    if (btn->parentWidget() != this) btn->setParent(this);
    btn->move(btn->getX(), btn->getY());
    btn->raise();
    btn->show();
  }
}

void LeftWidget::hideMapDataContainer(MapDataContainer* mapDataContainer)
{
  if (!mapDataContainer) return;
  for (auto* btn : mapDataContainer->pointButtonContainer) {
    if (!btn) continue;
    btn->hide();
  }
  QString path = QCoreApplication::applicationDirPath() + "/img/mapPic.png";
  QPixmap basePixmap(path);
  if (basePixmap.isNull()) {
    basePixmap = QPixmap(1500,1000);
    basePixmap.fill(Qt::white);
  } else {
    basePixmap = basePixmap.scaled(1500,1000, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  }
  canvasLabel->setPixmap(basePixmap);
  canvasLabel->show();
  canvasLabel->raise();
}

void LeftWidget::mousePressEvent(QMouseEvent *event) {
  nowClickedX = event->x();
  nowClickedY = event->y();
  int t = owner->getMouseClickedType();
  if (event->button() == Qt::LeftButton) {
    if (t == MainWindow::DEFAULT) {

    } else if (t == MainWindow::ADD_POINT) {
      AddPointWidget *w = new AddPointWidget(
          owner, this, owner->mapConstructorWidget->tempMapDataContainer);
      w->show();
      owner->displayPoints(owner->mapConstructorWidget->tempMapDataContainer);
    } else if (t == MainWindow::DELETE_POINT) {

    } else if (t == MainWindow::ADD_EDGE) {

    } else if (t == MainWindow::ADD_EDGE) {

    } else if (t == MainWindow::DELETE_EDGE) {

    }
  } else if (event->button() == Qt::RightButton) {
    owner->setClickedButtonNum(0);
  }

  QWidget::mousePressEvent(event);
}
