#ifndef NAVIGATION_WIDGETS_MAINWIDGET_H
#define NAVIGATION_WIDGETS_MAINWIDGET_H
#include <QWidget>
#include <vector>
class QVBoxLayout;
class ClickedButton;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget* parent = nullptr);
    void addButton(ClickedButton* button);
    void deleteButton(const QString& line);

private:
    QVBoxLayout* layout_;
    std::vector<ClickedButton*> buttons_;
};

#endif
