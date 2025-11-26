#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class MapDataContainer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeLeftWidgetShow(QWidget* nowShow);
    void dispalyPoints(MapDataContainer* mapDataContainer);

private:
    QWidget* leftWidget;
    QWidget* rightWidget;
    class QVBoxLayout* leftLayout;
    QWidget* currentLeft;
};
#endif // MAINWINDOW_H
