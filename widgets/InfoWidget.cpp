#include "InfoWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include "../util/MapPointButton.h"

InfoWidget::InfoWidget(QWidget* parent) : QWidget(parent) {
    layout_ = new QVBoxLayout(this);
    layout_->setContentsMargins(12, 12, 12, 12);
    layout_->setSpacing(8);
    setStyleSheet("QWidget { border: 1px solid #cccccc; border-radius: 8px; background-color: #ffffff; }");

    nameLabel_ = new QLabel(this);
    typeLabel_ = new QLabel(this);
    contentEdit_ = new QTextEdit(this);
    contentEdit_->setReadOnly(true);
    contentEdit_->setMinimumHeight(200);

    nameLabel_->setStyleSheet("font-size:16px;font-weight:500;padding:4px 8px;");
    typeLabel_->setStyleSheet("font-size:16px;font-weight:500;padding:4px 8px;");
    contentEdit_->setStyleSheet("QTextEdit { border: 1px solid #cccccc; border-radius: 8px; padding:8px; font-size:14px; }");

    layout_->addWidget(nameLabel_);
    layout_->addWidget(typeLabel_);
    layout_->addWidget(contentEdit_);

    refresh();
}

std::string InfoWidget::getName() const { return name_; }
void InfoWidget::setName(const std::string& n) { name_ = n; refresh(); }
int InfoWidget::getType() const { return type_; }
void InfoWidget::setType(int t) { type_ = t; refresh(); }
std::string InfoWidget::getContent() const { return content_; }
void InfoWidget::setContent(const std::string& c) { content_ = c; refresh(); }

void InfoWidget::setPointButton(MapPointButton* point) {
    if (!point) return;
    name_ = point->getName();
    int pt = point->getType();
    if (pt == MapPointButton::ROUTE_MARK) type_ = 0; else if (pt == MapPointButton::SCENIC_SPOT) type_ = 1; else type_ = pt;
    content_ = point->getContent();
    refresh();
}

void InfoWidget::refresh() {
    QString typeText;
    if (type_ == 0) typeText = "路径点"; else if (type_ == 1) typeText = "景点"; else typeText = QString::number(type_);
    nameLabel_->setText(QString::fromStdString(std::string("名称:") + name_));
    typeLabel_->setText(QString::fromStdString("类型:") + typeText);
    contentEdit_->setPlainText(QString::fromStdString(content_));
}

