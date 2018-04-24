#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include<QPixmap>

QT_BEGIN_NAMESPACE
class QCalendarWidget;
class QCheckBox;
class QComboBox;
class QDate;
class QDateEdit;
class QGridLayout;
class QGroupBox;
class QLabel;
class QDataWidgetMapper;
class QLineEdit;
class QPushButton;
class QStandardItemModel;
class QStringListModel;
class QTextEdit;
QT_END_NAMESPACE


class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
 QString username;

public slots:
 void receivelogin(QString str);
private slots:
    void updateButtons(int row);
    void selectedDateChanged();
    void setSelectedDate(int r);
    void ScheduleSave();


private:


    bool        mMoveing;
       QPoint      mMovePosition;

    bool connectDB();
    void createPreviewGroupBox();
    void createScheduleGroupBox();
    void createDiaryGroupBox();
    void widgetDesign();

    QGroupBox *previewGroupBox;
    QGridLayout *previewLayout;
    QCalendarWidget *calendar;

    QGroupBox *scheduleGroupBox;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *labelD;
    QLabel *labelL;
    QLabel *labelR;
    QLabel *labelS;


    QTextEdit *Edit1;
    QTextEdit *Edit2;
    QTextEdit *Edit3;
    QTextEdit *Edit4;
    QGroupBox *diaryGroupBox;
    QTextEdit *diary;

     QPixmap back_pixmap;




    void setupModel();
    int transd(QDate d);
    QDate transr(int row);

    QPushButton *nextButton;
    QPushButton *previousButton,*saveButton;


    QStringList sche1;
    QStringList sche2;
    QStringList sche3;
    QStringList sche4;
    QStringList d;
    QStandardItemModel *model;
    QDataWidgetMapper *mapper;


    bool m_move;
        QPoint m_startPoint;
        QPoint m_windowPoint;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};
#endif
