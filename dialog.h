#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include<QtGui>
#include<window.h>
class QLineEdit;
class CLoginDlg : public QDialog
{
    Q_OBJECT
public:
    CLoginDlg(QWidget* = 0);

public slots:
    virtual void accept();  //虚函数，点击确定按钮之后的接受函数

private:
    QLineEdit* usrLineEdit;  //输入用户名的框
    QLineEdit* pwdLineEdit;  //输入密码的框
    bool connectDB();
    Window *window;
signals:
    void showmainwindow(QString str);
};

#endif // LOGINDLG_H
