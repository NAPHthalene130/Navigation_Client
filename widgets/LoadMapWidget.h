#ifndef NAVIGATION_WIDGETS_LOADMAPWIDGET_H
#define NAVIGATION_WIDGETS_LOADMAPWIDGET_H

#include <QWidget>
#include "../util/MapDataContainer.h"

class MainWindow;
class QVBoxLayout;
class ClickedButton;
class QLineEdit;

class LoadMapWidget : public QWidget
{
    Q_OBJECT
private:
    MainWindow* owner;
    QVBoxLayout* layout;
    ClickedButton* backButton;
    ClickedButton* fileSelectButton;
    QLineEdit* filePathLine;
    ClickedButton* fileLoadButton;
    QLineEdit* tokenTextLine;
    ClickedButton* netLoadButton;
    ClickedButton* okButton;

public:
    explicit LoadMapWidget(MainWindow* owner, QWidget* parent = nullptr);
    MapDataContainer* tempMapDataContainer;
    void resetTempMapDataContainer();

private slots:
    void selectFileButtonClicked();
    void fileLoadButtonClicked();
    void netLoadButtonClicked();
    void okButtonClicked();
};

#endif
