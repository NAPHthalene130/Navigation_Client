#ifndef NAVIGATION_WIDGETS_LOADMAPWIDGET_H
#define NAVIGATION_WIDGETS_LOADMAPWIDGET_H

#include <QWidget>
#include "../util/MapDataContainer.h"

class MainWindow;
class QVBoxLayout;
class ClickedButton;

class LoadMapWidget : public QWidget
{
    Q_OBJECT
private:
    MainWindow* owner;
    QVBoxLayout* layout;
    ClickedButton* backButton;
    ClickedButton* fileLoadButton;
    ClickedButton* netLoadButton;
    ClickedButton* okButton;

public:
    explicit LoadMapWidget(MainWindow* owner, QWidget* parent = nullptr);
    MapDataContainer* tempMapDataContainer;
    void resetTempMapDataContainer();

private slots:
    void fileLoadButtonClicked();
    void netLoadButtonClicked();
    void okButtonClicked();
};

#endif
