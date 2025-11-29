#ifndef NAVIGATION_WIDGETS_SAVEMAPWIDGET_H
#define NAVIGATION_WIDGETS_SAVEMAPWIDGET_H

#include <QWidget>

class MainWindow;
class QVBoxLayout;
class ClickedButton;

class SaveMapWidget : public QWidget
{
    Q_OBJECT
private:
    MainWindow* owner;
    QVBoxLayout* layout;
    ClickedButton* backButton;
    ClickedButton* fileSaveButton;
    ClickedButton* netSaveButton;

public:
    explicit SaveMapWidget(MainWindow* owner, QWidget* parent = nullptr);

private slots:
    void fileSaveButtonClicked();
    void netSaveButtonClicked();
};

#endif
