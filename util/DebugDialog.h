#ifndef NAVIGATION_UTIL_DEBUGDIALOG_H
#define NAVIGATION_UTIL_DEBUGDIALOG_H
#include <QDialog>
#include <string>

class QLabel;

class DebugDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DebugDialog(const std::string& title,
                         const std::string& conten,
                         QWidget* parent = nullptr);

private:
    QLabel* contentLabel;
};

#endif
