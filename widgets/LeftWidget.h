#ifndef NAVIGATION_WIDGETS_LEFTWIDGET_H
#define NAVIGATION_WIDGETS_LEFTWIDGET_H
#include <QWidget>
class MainWindow;

class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(MainWindow* owner, QWidget* parent = nullptr);
    int nowClickedX;
    int nowClickedY;
protected:
    void mousePressEvent(class QMouseEvent* event) override;

private:
    MainWindow* owner;
};

#endif
