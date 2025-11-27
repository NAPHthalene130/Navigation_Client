#include "leftWidget.h"
#include "../mainwindow.h"
#include "AddPointWidget.h"
#include "AddPointWidget.h"
#include "mapConstructorWidget.h"
#include <QMouseEvent>

LeftWidget::LeftWidget(MainWindow* owner, QWidget* parent)
    : QWidget(parent), owner(owner)
{
    setMouseTracking(true);
}

void LeftWidget::mousePressEvent(QMouseEvent* event)
{
    nowClickedX = event->x();
    nowClickedY = event->y();
    int t = owner->getMouseClickedType();
    if (t == MainWindow::DEFAULT) {
        
    } else if (t == MainWindow::ADD_POINT) {
        AddPointWidget* w = new AddPointWidget(owner, this,owner->mapConstructorWidget->tempMapDataContainer);
        w->show();
        owner->displayPoints(owner->mapConstructorWidget->tempMapDataContainer);
    } else if (t == MainWindow::DELETE_POINT) {
        
    } else {
        
    }
    QWidget::mousePressEvent(event);
}
