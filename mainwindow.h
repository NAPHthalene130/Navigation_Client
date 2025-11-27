#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widgets/leftWidget.h"
#include <QMainWindow>
class MapDataContainer;
class MainWidget;
class MapConstructorWidget;
class QVBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static const int DEFAULT = 0;
    static const int ADD_POINT = 1;
    static const int DELETE_POINT = 2;
    static const int ADD_EDGE = 3;
    static const int DELETE_EDGE = 4;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeRightWidgetShow(QWidget* nowShow);
    void displayPoints(MapDataContainer* mapDataContainer);
    int getMouseClickedType() const;
    void setMouseClickedType(int t);
    void setClickedButtonNum(int num);
    int getClickedButtonNum();
    MainWidget* getMainWidget() const;
    MapConstructorWidget* getMapConstructorWidget() const;
    MapDataContainer* getMapDataContainer() const;
    int getNowClickedX();
    int getNowClickedY();
    MainWidget* mainWidget;
    MapConstructorWidget* mapConstructorWidget;
    MapDataContainer* mapDataContainer;
private:
    LeftWidget* leftWidget;
    QWidget* rightWidget;
    QVBoxLayout* leftLayout;
    QVBoxLayout* rightLayout;
    QWidget* currentLeft;
    int mouseClickedType = 0;
    int clickedButtonNum = 0;
};
#endif // MAINWINDOW_H
