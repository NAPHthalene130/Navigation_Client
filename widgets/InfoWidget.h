#ifndef NAVIGATION_WIDGETS_INFOWIDGET_H
#define NAVIGATION_WIDGETS_INFOWIDGET_H

#include <QWidget>
#include <string>

class QLabel;
class QTextEdit;
class QVBoxLayout;
class MapPointButton;

class InfoWidget : public QWidget {
    Q_OBJECT
public:
    explicit InfoWidget(QWidget* parent = nullptr);

    std::string getName() const;
    void setName(const std::string& n);
    int getType() const;
    void setType(int t);
    std::string getContent() const;
    void setContent(const std::string& c);
    void setPointButton(MapPointButton* point);

private:
    void refresh();
    std::string name_;
    int type_ = 0;
    std::string content_;
    QVBoxLayout* layout_;
    QLabel* nameLabel_;
    QLabel* typeLabel_;
    QTextEdit* contentEdit_;
};

#endif
