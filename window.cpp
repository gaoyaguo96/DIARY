#include "window.h"
#include <QtGui>
#include <QApplication>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QCalendarWidget>
#include <QGroupBox>
#include <QLabel>
#include <QDataWidgetMapper>
#include <QSqldatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include<QMessageBox>
#include<qDebug>
#include <QDialog>
#include<QSqlError>
#include<QToolButton>


#include <QMouseEvent>
#include <QPoint>



Window::Window()
{
    createPreviewGroupBox();
    createDiaryGroupBox();
    createScheduleGroupBox();


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(previewGroupBox, 0,0);
    layout->addWidget(scheduleGroupBox, 0,1,2,2);
    layout->addWidget(diaryGroupBox, 1,0);

    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

    previewLayout->setRowMinimumHeight(0, calendar->sizeHint().height()+20);
    previewLayout->setColumnMinimumWidth(0, calendar->sizeHint().width()+20);

    setWindowTitle(tr("Daily Life"));

    connectDB();

   setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint );

setAttribute(Qt::WA_TranslucentBackground, true);

setStyleSheet ("border:2px solid pink;border-radius:10px;padding:2px 4px;");

widgetDesign();

}

bool Window::connectDB()
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

void  Window::widgetDesign()
{

    Edit1->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    Edit2->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    Edit3->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    Edit4->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    label1->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    label2->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    label3->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    label4->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    nextButton->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    previousButton->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    saveButton->setStyleSheet("background-color: rgb(255, 255, 255, 120);");
    scheduleGroupBox->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    previewGroupBox->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    diaryGroupBox->setStyleSheet("background-color: rgb(255, 255, 255, 100);");
    diary->setStyleSheet("background-color: rgb(255, 255, 255, 100);");



    QFont fontEdit ( "Microsoft YaHei", 10, 63),fontLabel("Microsoft YaHei", 10, 50),fontCalendar("Microsoft YaHei", 10, 40);
    Edit1->setFont(fontEdit);
    Edit2->setFont(fontEdit);
    Edit3->setFont(fontEdit);
    Edit4->setFont(fontEdit);


    nextButton->setFont(fontLabel);
    previousButton->setFont(fontLabel);
    saveButton->setFont(fontLabel);
    scheduleGroupBox->setFont(fontLabel);
    previewGroupBox->setFont(fontLabel);
    diaryGroupBox->setFont(fontLabel);
    diary->setFont(fontLabel);
    calendar->setFont(fontCalendar);


    QPixmap tempPix = QPixmap(":/STAR.png");
    label1->setAlignment(Qt::AlignCenter);
    label1->setPixmap(tempPix);
    tempPix = QPixmap(":/riji.png");
    label2->setAlignment(Qt::AlignCenter);
    label2->setPixmap(tempPix);
    tempPix = QPixmap(":/zhebian.png");
    label3->setAlignment(Qt::AlignCenter);
    label3->setPixmap(tempPix);
    tempPix = QPixmap(":/SHUQIAN.png");
    label4->setAlignment(Qt::AlignCenter);
    label4->setPixmap(tempPix);
    tempPix = QPixmap(":/RIJIBEN.png");
    labelD->setAlignment(Qt::AlignCenter);
    labelD->setPixmap(tempPix);
    tempPix = QPixmap(":/xiaozuo.png");
    labelL->setAlignment(Qt::AlignCenter);
    labelL->setPixmap(tempPix);
    tempPix = QPixmap(":/xiaoyou.png");
    labelR->setAlignment(Qt::AlignCenter);
    labelR->setPixmap(tempPix);
    tempPix = QPixmap(":/BAOCUN.png");
    labelS->setAlignment(Qt::AlignCenter);
    labelS->setPixmap(tempPix);


    calendar->setStyleSheet("background-color: rgb(250, 235, 215);");

    QToolButton *prevBtn = calendar->findChild<QToolButton*>(QLatin1String("qt_calendar_prevmonth"));

      QToolButton *bextBtn = calendar->findChild<QToolButton*>(QLatin1String("qt_calendar_nextmonth"));

      QIcon icon;
       icon.addFile(tr(":/ZUOJIANTOU.png"));
      prevBtn->setIcon(icon);
    icon.addFile(tr(":/YOUJIANTOU.png"));
      bextBtn->setIcon(icon);


}

void Window::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }

}
void Window::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
        this->move(m_windowPoint + relativePos );
    }
}
void Window::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
    else if(event->button() == Qt::RightButton)
    {
        close();
    }
}


void Window::createPreviewGroupBox()
{
    previewGroupBox = new QGroupBox();

    calendar = new QCalendarWidget;
    calendar->setMinimumDate(QDate(2018, 1, 1));
    calendar->setMaximumDate(QDate(2019, 1, 1));
    calendar->setGridVisible(true);
    calendar->setLocale(QLocale::English);
    calendar->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);

    QDate date=QDate::currentDate();
    QTextCharFormat t;
    t.setBackground(Qt::gray);
    calendar->setDateTextFormat(date,t);

    previewLayout = new QGridLayout;
    previewLayout->addWidget(calendar, 0, 0, Qt::AlignCenter);
    previewGroupBox->setLayout(previewLayout);
}

void Window::createDiaryGroupBox()
{
    diaryGroupBox = new QGroupBox();
    diary = new QTextEdit();
    labelD = new QLabel();
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(labelD,0,0);
    layout->addWidget(diary,0,0);
    diaryGroupBox->setLayout(layout);
}

void Window::setupModel()
{
    QDate date;
    QString chazhao;
    QSqlQuery query;

    for(int i=0;i<=365;i++)
    {
        date=transr(i);
        chazhao = QString("select text1,text2,text3,text4,d from 日志 where username = '%1' and day = %2 and month =%3 and year = %4")
                .arg(username).arg(QString::number(date.day())).arg(QString::number(date.month())).arg(QString::number(date.year()));

        query.exec(chazhao);
        query.last();
        sche1<<query.value(0).toString();
        sche2<<query.value(1).toString();
        sche3<<query.value(2).toString();
        sche4<<query.value(3).toString();
        d<<query.value(4).toString();
    }
    query.clear();

    model = new QStandardItemModel(366,5,this);

    for (int row = 0; row <= 365; ++row) {
      QStandardItem *item = new QStandardItem(sche1[row]);
      model->setItem(row, 0, item);
      item = new QStandardItem(sche2[row]);
      model->setItem(row, 1, item);
      item = new QStandardItem(sche3[row]);
      model->setItem(row, 2, item);
      item = new QStandardItem(sche4[row]);
      model->setItem(row, 3, item);
      item = new QStandardItem(d[row]);
      model->setItem(row, 4, item);
    }
}



int Window::transd(QDate d)
{
    int cnt[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int tmp=d.day();
    for(int i=0;i<d.month()-1;i++)
        tmp+=cnt[i];
    return tmp;
}

QDate Window::transr(int row)
{
    int y=2018,m=1,d=0;
    int cnt[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int tmp=0;
    while(tmp+cnt[m-1]<row)
    {
        tmp+=cnt[m-1];
        m++;
    }
    d=row-tmp;
    return QDate(y,m,d);
}

void Window::selectedDateChanged()
{
    QDate d=calendar->selectedDate();
    mapper->setCurrentIndex(transd(d));
}

void Window::setSelectedDate(int r)
{
    calendar->setSelectedDate(transr(r));
}

void Window::createScheduleGroupBox()
{
    scheduleGroupBox = new QGroupBox();

    //setupModel();

    label1 = new QLabel();
    label2 = new QLabel();
    label3 = new QLabel();
    label4 = new QLabel();
    Edit1 =  new QTextEdit();
    Edit2 =  new QTextEdit();
    Edit3 =  new QTextEdit();
    Edit4 =  new QTextEdit();
    label1->setBuddy(Edit1);
    label2->setBuddy(Edit2);
    label3->setBuddy(Edit3);
    label4->setBuddy(Edit4);

    nextButton = new QPushButton();
    previousButton = new QPushButton();
    saveButton = new QPushButton();
    labelL = new QLabel();
    labelR = new QLabel();
    labelS = new QLabel();

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(label1,0,0,2,1);
    layout->addWidget(label2,0,1,2,1);
    layout->addWidget(Edit1, 0, 0, 2, 1);
    layout->addWidget(Edit2, 0, 1, 2, 1);
    layout->addWidget(label3,4,0,2,1);
    layout->addWidget(label4,4,1,2,1);
    layout->addWidget(Edit3, 4, 0, 2, 1);
    layout->addWidget(Edit4, 4, 1, 2, 1);
    layout->addWidget(labelL, 7, 0, 1, 1);
    layout->addWidget(previousButton, 7, 0, 1, 1);
    layout->addWidget(labelR, 7, 1, 1, 1);
    layout->addWidget(nextButton, 7, 1, 1, 1);
    layout->addWidget(labelS, 8, 0, 1, 2);
    layout->addWidget(saveButton, 8, 0, 1, 2);
    scheduleGroupBox->setLayout(layout);


}

void Window::updateButtons(int row)
{
    previousButton->setEnabled(row > 1);
    nextButton->setEnabled(row < model->rowCount() - 1);
}

void Window::ScheduleSave()
{
    QDate date = calendar->selectedDate();
   QString chazhao = QString("select day from 日志 where username = '%1' and day = %2 and month =%3 and year = %4")
            .arg(username)
            .arg(QString::number(date.day()))
            .arg(QString::number(date.month()))
            .arg(QString::number(date.year()));
    QSqlQuery query;
    query.exec(chazhao);
    query.last();

    QString text1 = Edit1->toPlainText(),
            text2 = Edit2->toPlainText(),
            text3 = Edit3->toPlainText(),
            text4 = Edit4->toPlainText(),
            text5 = diary->toPlainText();
    if(query.at()==-1)
    {
        QString xieru = QString("insert into 日志(username,day,month,year,text1,text2,text3,text4,d) values('%1',%2,%3,%4,'%5','%6','%7','%8','%9') ")
                .arg(username)
                .arg(QString::number(date.day()))
                .arg(QString::number(date.month()))
                .arg(QString::number(date.year()))
                .arg(text1)
                .arg(text2)
                .arg(text3)
                .arg(text4)
                .arg(text5);
        query.clear();
        query.exec(xieru);
        query.clear();


    }

    else
   {
        QString xieru = QString("update 日志 set text1='%5',text2='%6',text3='%7',text4='%8',d='%9' where username='%1' and day=%2 and month =%3 and year = %4")
            .arg(username)
            .arg(QString::number(date.day()))
            .arg(QString::number(date.month()))
            .arg(QString::number(date.year()))
            .arg(text1)
            .arg(text2)
            .arg(text3)
            .arg(text4)
            .arg(text5);
query.clear();
    query.exec(xieru);
    query.clear();

    }


    QMessageBox message(QMessageBox::NoIcon, " ", "保存成功");

             message.exec();


}

 void Window::receivelogin(QString str)
 {
     username = QString(str);

     setupModel();
     mapper = new QDataWidgetMapper(this);
     mapper->setModel(model);
     mapper->addMapping(Edit1, 0);
     mapper->addMapping(Edit2, 1);
     mapper->addMapping(Edit3, 2);
     mapper->addMapping(Edit4, 3);
     mapper->addMapping(diary, 4);
     connect(previousButton, SIGNAL(clicked()),
                 mapper, SLOT(toPrevious()));
         connect(nextButton, SIGNAL(clicked()),
                 mapper, SLOT(toNext()));
         connect(saveButton, SIGNAL(clicked()),
                 this, SLOT(ScheduleSave()));
         connect(mapper, SIGNAL(currentIndexChanged(int)),
                 this, SLOT(updateButtons(int)));
         connect(mapper, SIGNAL(currentIndexChanged(int)),
                 this, SLOT(setSelectedDate(int)));
         connect(calendar, SIGNAL(selectionChanged()),
                 this, SLOT(selectedDateChanged()));
         int d=transd(QDate::currentDate());
     mapper->setCurrentIndex(d);



         this->show();

 }
