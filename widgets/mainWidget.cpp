#include "mainWidget.h"
#include "../util/ClickedButton.h"
#include <QVBoxLayout>
#include <QLabel>

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent), layout_(new QVBoxLayout(this))
{
    layout_->setContentsMargins(12,12,12,12);
    layout_->setSpacing(12);
    auto* title = new QLabel("功能选择", this);
    title->setStyleSheet("font-size:20px;font-weight:600;padding:4px 0;");
    layout_->addWidget(title);
    buttons_.clear();
    auto* b1 = new ClickedButton("导航功能", ClickedButton::textOnDark, ClickedButton::primaryBlue, this);
    b1->setHeight(48);
    b1->setFontSize(16);
    addButton(b1);
    auto* b2 = new ClickedButton("构建地图", ClickedButton::textOnLight, ClickedButton::accentPurple, this);
    b2->setHeight(48);
    b2->setFontSize(16);
    addButton(b2);
    auto* b3 = new ClickedButton("加载地图", ClickedButton::textOnDark, ClickedButton::successGreen, this);
    b3->setHeight(48);
    b3->setFontSize(16);
    addButton(b3);
    auto* b4 = new ClickedButton("导出地图", ClickedButton::textOnLight, ClickedButton::warningAmber, this);
    b4->setHeight(48);
    b4->setFontSize(16);
    addButton(b4);
    auto* b5 = new ClickedButton("退出地图", ClickedButton::textOnLight, ClickedButton::dangerRed, this);
    b5->setHeight(48);
    b5->setFontSize(16);
    addButton(b5);
    layout_->addStretch(1);
}

void MainWidget::addButton(ClickedButton* button)
{
    buttons_.push_back(button);
    layout_->addWidget(button);
}

void MainWidget::deleteButton(const QString& line)
{
    for (auto it = buttons_.begin(); it != buttons_.end(); ) {
        if ((*it)->text() == line) {
            (*it)->hide();
            (*it)->deleteLater();
            it = buttons_.erase(it);
        } else {
            ++it;
        }
    }
}
