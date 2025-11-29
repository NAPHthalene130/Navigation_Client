#ifndef NAVIGATION_WIDGETS_SAVEMAPWIDGET_H
#define NAVIGATION_WIDGETS_SAVEMAPWIDGET_H

#include <QWidget>

class MainWindow;
class QVBoxLayout;
class ClickedButton;
class QLineEdit;

class SaveMapWidget : public QWidget
{
    Q_OBJECT
private:
    MainWindow* owner;
    QVBoxLayout* layout;
    ClickedButton* backButton;
    ClickedButton* dirSelectButton;
    QLineEdit* dirPathLine;
    ClickedButton* fileSaveButton;
    QLineEdit* nameTextLine;
    ClickedButton* netSaveButton;
    QLineEdit* tokenTextLine;

public:
    explicit SaveMapWidget(MainWindow* owner, QWidget* parent = nullptr);

private slots:
    void selectDirButtonClicked();
    void fileSaveButtonClicked();
    void netSaveButtonClicked();
};

#endif
