#ifndef NAVIGATION_WIDGETS_NAVIGATIONWIDGET_H
#define NAVIGATION_WIDGETS_NAVIGATIONWIDGET_H

#include <QWidget>
#include "InfoWidget.h"
class MainWindow;
class QVBoxLayout;
class ClickedButton;
class QLabel;

class NavigationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NavigationWidget(MainWindow* owner, QWidget* parent = nullptr);
    void switchInfoShowWidget(QWidget* infoWidget);
    void buttonColorUpdate();
    int clickedButtonNum = 0;

    void setFirstClickedButtonName(std::string name);
    void setSecondClickedButtonName(std::string name);
    void setClickedNum(int num);

    std::string getFirstClickedButtonName() const;
    std::string getSecondClickedButtonName() const;
    int getClickedNum() const;
    void dij(std::string start, std::string end);
    void dfs(std::string start);
    void dfsSimple(std::string start);
    QLabel* getDefaultLabel() const;
    void setDefaultLabel(QLabel* label);
    InfoWidget* infoWidget;


private:
    int nowShowIndex = 0;
    MainWindow* owner;
    QVBoxLayout* layout;
    ClickedButton* backButton;
    ClickedButton* pipeButton;
    ClickedButton* navigationButton;
    ClickedButton* infoButton;
    ClickedButton* dfsButton;
    QWidget* infoShowWidget;
    QVBoxLayout* infoLayout;
    QLabel* defaultLabel;
    std::string firstClickedButtonName = "";
    std::string secondClickedButtonName = "";
    int clickedNum = 0;
    void dfsHelper(std::vector<std::vector<int>> &link,
                                     std::vector<bool> &visited,
                                     std::vector<std::vector<int>> &paths,
                                     int current,
                                     std::vector<int> &currentPath);
private slots:
    void backButtonClicked();
    void pipeButtonClicked();
    void navigationButtonClicked();
    void infoButtonClicked();
    void dfsButtonClicked();

};

#endif // NAVIGATION_WIDGETS_NAVIGATIONWIDGET_H
