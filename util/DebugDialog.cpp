#include "DebugDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QString>

DebugDialog::DebugDialog(const std::string& title,
                         const std::string& conten,
                         QWidget* parent)
    : QDialog(parent), contentLabel(new QLabel(QString::fromStdString(conten), this))
{
    setWindowTitle(QString::fromStdString(title));
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(contentLabel);
    setAttribute(Qt::WA_DeleteOnClose, true);
    open();
}

