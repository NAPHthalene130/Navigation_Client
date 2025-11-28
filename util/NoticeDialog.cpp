#include "NoticeDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QApplication>
#include <QString>
#include "ClickedButton.h"

NoticeDialog::NoticeDialog(const std::string& title,
                           const std::string& content)
    : QDialog()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowTitle(QString::fromStdString(title));
    setModal(true);
    setMinimumSize(420, 220);

    auto* rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(16,16,16,16);
    rootLayout->setSpacing(0);

    card_ = new QFrame(this);
    card_->setObjectName("card");
    card_->setStyleSheet(
        "#card{"
        "background: rgb(252, 253, 255);"
        "border-radius: 16px;"
        "border: 1px solid rgba(33,37,41,0.15);"
        "}"
    );
    auto* shadow = new QGraphicsDropShadowEffect(card_);
    shadow->setBlurRadius(24);
    shadow->setOffset(0, 8);
    shadow->setColor(QColor(0,0,0,60));
    card_->setGraphicsEffect(shadow);

    auto* cardLayout = new QVBoxLayout(card_);
    cardLayout->setContentsMargins(20,20,20,20);
    cardLayout->setSpacing(14);

    titleLabel_ = new QLabel(QString::fromStdString(title), card_);
    titleLabel_->setStyleSheet(
        "color: rgb(33,37,41);"
        "font-size: 18px;"
        "font-weight: 600;"
    );

    contentLabel_ = new QLabel(QString::fromStdString(content), card_);
    contentLabel_->setWordWrap(true);
    contentLabel_->setStyleSheet(
        "color: rgb(73,80,87);"
        "font-size: 14px;"
        "line-height: 1.6em;"
    );

    auto* actions = new QHBoxLayout();
    actions->setContentsMargins(0,0,0,0);
    actions->setSpacing(10);
    actions->addStretch(1);
    okButton_ = new ClickedButton("确定", ClickedButton::textOnLight, ClickedButton::primaryBlue, card_);
    okButton_->setHeight(36);
    okButton_->setFontSize(14);
    actions->addWidget(okButton_);

    cardLayout->addWidget(titleLabel_);
    cardLayout->addWidget(contentLabel_);
    cardLayout->addLayout(actions);
    rootLayout->addWidget(card_);

    connect(okButton_, &QPushButton::clicked, this, [this]() { this->accept(); });

    auto* anim = new QPropertyAnimation(this, "windowOpacity");
    anim->setDuration(180);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    open();
}

