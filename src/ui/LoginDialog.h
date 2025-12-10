#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QString>
#include <QRadioButton>

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    QString getUserType() const;
    int getUserId() const;

private:
    QRadioButton *radioButtonNormalUser;
    QRadioButton *radioButtonAdmin;
};

#endif // LOGINDIALOG_H