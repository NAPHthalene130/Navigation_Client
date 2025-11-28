#ifndef NAVIGATION_UTIL_CLICKEDBUTTON_H
#define NAVIGATION_UTIL_CLICKEDBUTTON_H
#include <QPushButton>
#include <QColor>
#include <QString>

class ClickedButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ClickedButton(const QString& line,
                           const QColor& buttonColor,
                           const QColor& backgroundColor,
                           QWidget* parent = nullptr);
    void setWidth(int w);
    void setHeight(int h);
    void setColors(const QColor& buttonColor, const QColor& backgroundColor);
    void setFontSize(int px);

    static QColor primaryBlue;
    static QColor secondaryGray;
    static QColor accentPurple;
    static QColor successGreen;
    static QColor warningAmber;
    static QColor dangerRed;
    static QColor backgroundDark;
    static QColor backgroundLight;
    static QColor textOnDark;
    static QColor textOnLight;

private:
    QColor textColor_;
    QColor backgroundColor_;
    int fontSize_;
    void applyStyle();
};

#endif
