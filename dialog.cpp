#include "dialog.h"
#include "window.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include<QMessageBox>
#include<qDebug>
#include <QApplication>
#include <QDialog>
#include<QLineEdit>
#include<QGridLayout>
#include<QPushButton>
#include<QString>
#include<QLabel>

#include <QSqlDatabase><span style="white-space:pre;">                    </span>
#include <QDebug>

#include<QSqlError>
CLoginDlg::CLoginDlg(QWidget * parent)
    : QDialog(parent)
{
    connectDB();
    QLabel *usrLabel = new QLabel(trUtf8("username:"));
    QLabel *pwdLabel = new QLabel(trUtf8("password:"));
    usrLineEdit = new QLineEdit;
    pwdLineEdit = new QLineEdit;
    pwdLineEdit->setEchoMode(QLineEdit::Password);

    //布局
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(usrLabel,0,0,1,1);
    gridLayout->addWidget(pwdLabel,1,0,1,1);
    gridLayout->addWidget(usrLineEdit,0,1,1,3);
    gridLayout->addWidget(pwdLineEdit,1,1,1,3);

    QPushButton* okBtn = new QPushButton(trUtf8("OK"));
    QPushButton* cancelBtn = new QPushButton(trUtf8("Cancel"));
    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(60);
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);

    QVBoxLayout* dlgLayout = new QVBoxLayout;
    dlgLayout->setMargin(40);
    dlgLayout->addLayout(gridLayout);
    dlgLayout->addStretch(40);
    dlgLayout->addLayout(btnLayout);
    setLayout(dlgLayout);

    connect(okBtn,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(reject()));

    setWindowTitle(trUtf8("Sign in"));
    resize(300,200);
    window = new Window();
     QObject::connect(this,&CLoginDlg::showmainwindow,window,&Window::receivelogin);


}
bool CLoginDlg::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
        qDebug()<<"ODBC driver?"<<db.isValid();
        QString dsn = QString::fromLocal8Bit("QTDSN");      //数据源名称
        db.setHostName("localhost");                        //选择本地主机，127.0.1.1
        db.setDatabaseName(dsn);                            //设置数据源名称
        db.setUserName("sa");                               //登录用户
        db.setPassword("2333");                           //密码
        if(!db.open())                                      //打开数据库
        {
            qDebug()<<db.lastError().text();
            QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
            return false;                                   //打开失败
        }
        else
        {
            qDebug()<<"database open success!";


        }
        return true;


}

void CLoginDlg::accept()
{
   QString yonghu = usrLineEdit->text(), mima = pwdLineEdit->text();
   QString zhao = QString("select * from 用户列表 where username='%1' and password='%2'").arg(yonghu).arg(mima);
   QSqlQuery query;
   query.exec(zhao);
   query.last();
   int record=query.at();

    if(record!=-1)
    {

        emit showmainwindow(yonghu);
        QDialog::accept();
    }
    else
    {
        QMessageBox::warning(this,trUtf8("警告"),trUtf8("用户名或密码错误"),
                             QMessageBox::Yes);
        usrLineEdit->setFocus();
    }
   query.clear();
}
