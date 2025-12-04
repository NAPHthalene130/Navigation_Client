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
#include <set>

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

  QString path = "F:/CODE/QT/Navigation/img/mapPic.png";
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
    auto* a = e->getFirstPointButton();
    auto* b = e->getSecondPointButton();
    if (!a || !b) continue;
    QPen pen;
    if (e->getType() == 0) {
      //默认情况
      pen = QPen(QColor(00,102,255), 5); // 蓝色
    } else if (e->getType() == 1) {
      //管道边
      pen = QPen(QColor(0,51,153), 5); //深蓝色
    } else if (e->getType() == 2) {
      //导航边
      pen = QPen(QColor(204,41,0), 5);
    } else if (e->getType() == -1) {
      //隐藏边
      pen = QPen(QColor(135,206,235), 5);
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

void LeftWidget::drawPathWithGradient(MapDataContainer* mapDataContainer, const std::vector<Edge*>& path)
{
    if (!mapDataContainer) return;
    setFixedSize(1500, 1000);
    if (!canvasLabel) {
        canvasLabel = new QLabel(this);
        canvasLabel->setGeometry(0, 0, 1500, 1000);
        canvasLabel->setScaledContents(true);
    }

    QString pathStr = "F:/CODE/QT/Navigation/img/mapPic.png";
    QPixmap basePixmap(pathStr);
    if (basePixmap.isNull()) {
        basePixmap = QPixmap(1500, 1000);
        basePixmap.fill(Qt::white);
    } else {
        basePixmap = basePixmap.scaled(1500, 1000, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }

    QPainter painter(&basePixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    std::set<Edge*> pathSet(path.begin(), path.end());

    std::map<Edge*, int> edgeToIndex;
    for(size_t i = 0; i < path.size(); ++i) {
        edgeToIndex[path[i]] = i;
    }

    for (auto* e : mapDataContainer->edgeContainer) {
        if (!e) continue;
        auto* a = e->getFirstPointButton();
        auto* b = e->getSecondPointButton();
        if (!a || !b) continue;
        
        QPen pen;
        if (pathSet.count(e)) {
            // Gradient: Green -> Red
            int index = edgeToIndex[e];
            int pathSize = path.size();
            double t = 0.0;
            if (pathSize > 1) {
                t = (double)index / (pathSize - 1);
            }
            int r = (int)(t * 255);
            int g = (int)((1 - t) * 255);
            int b = 0;
            pen = QPen(QColor(r, g, b), 5);
        } else {
            pen = QPen(QColor(135,206,235), 5);
        }
        
        painter.setPen(pen);
        painter.drawLine(QPoint(a->getX()+10, a->getY()+10), QPoint(b->getX()+10, b->getY()+10));
    }
    painter.end();

    canvasLabel->setPixmap(basePixmap);
    canvasLabel->show();
    canvasLabel->raise();

    for (auto* btn : mapDataContainer->pointButtonContainer) {
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
  QString path = "F:/CODE/QT/Navigation/img/mapPic.png";
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
  nowClickedX = event->position().x();
  nowClickedY = event->position().y();
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

    } else if (t == MainWindow::DELETE_EDGE) {

    }
  } else if (event->button() == Qt::RightButton) {
    clickedButtonNum = 0;
    if (owner && owner->mapConstructorWidget) owner->mapConstructorWidget->buttonColorUpdate();
  }

  QWidget::mousePressEvent(event);
}
