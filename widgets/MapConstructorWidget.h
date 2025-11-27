#ifndef NAVIGATION_WIDGETS_MAPCONSTRUCTORWIDGET_H
#define NAVIGATION_WIDGETS_MAPCONSTRUCTORWIDGET_H
#include <QWidget>
#include "../util/MapDataContainer.h"
class MainWindow;
class QVBoxLayout;
class ClickedButton;

class MapConstructorWidget : public QWidget
{
    Q_OBJECT
private:
    MainWindow* owner;
    QVBoxLayout* layout;
    ClickedButton* backButton;
    ClickedButton* addPointButton;
    
public:
    explicit MapConstructorWidget(MainWindow* owner, QWidget* parent = nullptr);
    void refreshAddPointButtonStyle();
    void resetTempMapDataContainer();
    MapDataContainer* tempMapDataContainer;
};

#endif
