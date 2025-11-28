#include "ClickedButton.h"
#include <QSizePolicy>

QColor ClickedButton::primaryBlue = QColor(50, 115, 220);
QColor ClickedButton::secondaryGray = QColor(108, 117, 125);
QColor ClickedButton::accentPurple = QColor(142, 68, 173);
QColor ClickedButton::successGreen = QColor(40, 167, 69);
QColor ClickedButton::warningAmber = QColor(255, 193, 7);
QColor ClickedButton::dangerRed = QColor(220, 53, 69);
QColor ClickedButton::backgroundDark = QColor(33, 37, 41);
QColor ClickedButton::backgroundLight = QColor(245, 247, 250);
QColor ClickedButton::textOnDark = QColor(248, 249, 250);
QColor ClickedButton::textOnLight = QColor(33, 37, 41);

ClickedButton::ClickedButton(const QString& line,
                             const QColor& buttonColor,
                             const QColor& backgroundColor,
                             QWidget* parent)
    : QPushButton(line, parent), textColor_(buttonColor), backgroundColor_(backgroundColor), fontSize_(16)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    applyStyle();
}

void ClickedButton::setWidth(int w)
{
    setFixedWidth(w);
}

void ClickedButton::setHeight(int h)
{
    setFixedHeight(h);
}

void ClickedButton::setColors(const QColor& buttonColor, const QColor& backgroundColor)
{
    textColor_ = buttonColor;
    backgroundColor_ = backgroundColor;
    applyStyle();
}

void ClickedButton::setFontSize(int px)
{
    fontSize_ = px;
    applyStyle();
}

void ClickedButton::applyStyle()
{
    QString bg = QString("rgb(%1,%2,%3)").arg(backgroundColor_.red()).arg(backgroundColor_.green()).arg(backgroundColor_.blue());
    QString fg = QString("rgb(%1,%2,%3)").arg(textColor_.red()).arg(textColor_.green()).arg(textColor_.blue());
    QString hoverBg = QString("rgba(%1,%2,%3,0.9)").arg(backgroundColor_.red()).arg(backgroundColor_.green()).arg(backgroundColor_.blue());
    QString pressedBg = QString("rgba(%1,%2,%3,0.85)").arg(backgroundColor_.red()).arg(backgroundColor_.green()).arg(backgroundColor_.blue());
    QString border = QString("rgba(%1,%2,%3,0.35)").arg(textColor_.red()).arg(textColor_.green()).arg(textColor_.blue());
    QString style = QString(
        "QPushButton{"
        "background:%1;"
        "color:%2;"
        "border:1px solid %5;"
        "border-radius:10px;"
        "padding:12px 18px;"
        "font-size:%6px;"
        "font-weight:500;"
        "}"
        "QPushButton:hover{"
        "background:%3;"
        "}"
        "QPushButton:pressed{"
        "background:%4;"
        "}"
        ).arg(bg).arg(fg).arg(hoverBg).arg(pressedBg).arg(border).arg(fontSize_);
    setStyleSheet(style);
}
