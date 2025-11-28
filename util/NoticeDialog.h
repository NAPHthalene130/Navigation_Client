#ifndef NAVIGATION_UTIL_NOTICEDIALOG_H
#define NAVIGATION_UTIL_NOTICEDIALOG_H
#include <QDialog>
#include <string>

class QLabel;
class QVBoxLayout;
class QFrame;
class ClickedButton;

class NoticeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NoticeDialog(const std::string& title,
                          const std::string& content);

private:
    QFrame* card_;
    QLabel* titleLabel_;
    QLabel* contentLabel_;
    ClickedButton* okButton_;
};

#endif
