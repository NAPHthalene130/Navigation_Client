#ifndef NAVIGATION_UTIL_MAPPOINTBUTTON_H
#define NAVIGATION_UTIL_MAPPOINTBUTTON_H
#include <QPushButton>
#include <string>
#include "../mainwindow.h"
class MapPointButton : public QPushButton
{
    Q_OBJECT
public:
    static const int ROUTE_MARK = 1;
    static const int SCENIC_SPOT = 2;

    explicit MapPointButton(MapPointButton* otherButton);
    explicit MapPointButton(QWidget* parent = nullptr);
    explicit MapPointButton(int type, MainWindow* mainWindow);

    int getX() const;
    void setX(int v);
    int getY() const;
    void setY(int v);
    int getType() const;
    void setType(int v);
    std::string getName() const;
    void setName(const std::string& n);
    std::string getContent() const;
    void setContent(const std::string& c);
private:
    int x = 0;
    int y = 0;
    int type = 0;
    std::string name;
    std::string content;
    void applyStyle();
    MainWindow* mainWindow;
private slots:
    void clicked();
};

#endif // NAVIGATION_UTIL_MAPPOINTBUTTON_H
