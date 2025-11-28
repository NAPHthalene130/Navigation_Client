#ifndef NAVIGATION_WIDGETS_ADDPOINTWIDGET_H
#define NAVIGATION_WIDGETS_ADDPOINTWIDGET_H
#include <QWidget>
#include "../util/MapDataContainer.h"
class QVBoxLayout;
class QComboBox;
class QLineEdit;
class QTextEdit;
class ClickedButton;
class MainWindow;

class AddPointWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddPointWidget(MainWindow* mainWindow, QWidget* parent = nullptr,MapDataContainer *tempMapDataContainer = nullptr);

private:
    MainWindow* mainWindow;
    QVBoxLayout* layout;
    QComboBox* typeCombo;
    QLineEdit* nameEdit;
    QTextEdit* contentEdit;
    ClickedButton* cancelButton;
    ClickedButton* okButton;
    void centerInParent();
    int nowX;
    int nowY;
    MapDataContainer *tempMapDataContainer;
private slots:
    void cancelButtonClicked();
    void okButtonCliked();
};

#endif
