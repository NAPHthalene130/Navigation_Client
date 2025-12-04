#ifndef NAVIGATION_WIDGETS_LEFTWIDGET_H
#define NAVIGATION_WIDGETS_LEFTWIDGET_H
#include <QWidget>
#include "../util/MapDataContainer.h"
class QLabel;
class MainWindow;

class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(MainWindow* owner, QWidget* parent = nullptr);
    int nowClickedX;
    int nowClickedY;
    void drawWidget(MapDataContainer mapDataContainer);
    void drawPathWithGradient(MapDataContainer* mapDataContainer, const std::vector<Edge*>& path);
    void hideMapDataContainer(MapDataContainer* mapDataContainer);
    MapPointButton* firstClickedPointButton;
    MapPointButton* secondClickedPointButton;
    int clickedButtonNum = 0;
protected:
    void mousePressEvent(class QMouseEvent* event) override;

private:
    MainWindow* owner;
    QLabel* canvasLabel;
};

#endif
