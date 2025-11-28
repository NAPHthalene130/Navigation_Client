#ifndef NAVIGATION_WIDGETS_MAINWIDGET_H
#define NAVIGATION_WIDGETS_MAINWIDGET_H
#include <QWidget>
#include <vector>
class QVBoxLayout;
class ClickedButton;
class MainWindow;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(MainWindow* owner, QWidget* parent = nullptr);
    void addButton(ClickedButton* button);
    void deleteButton(const QString& line);

private:
    MainWindow* owner_;
    QVBoxLayout* layout_;
    std::vector<ClickedButton*> buttons_;
    ClickedButton* mapFunctionButton;
    ClickedButton* mapConstructorButton;
    ClickedButton* loadMapButton;
    ClickedButton* saveMaButton;
    ClickedButton* exitButton;

private slots:
    void mapFunctionButtonClicked();
    void mapConstructorButtonClicked();
    void loadMapButtonClicked();
    void saveMaButtonClicked();
    void exitButtonClicked();
};

#endif
