#include "classwin.h"
#include "ui_classwin.h"


classwin::classwin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::classwin)
{
    ui->setupUi(this);
    setGeometry(0,0,1024,768);
    //sql
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/bin/database_wq.db");
    if(!db.open()) qDebug() << "sql connect fail.!";
    QSqlQuery query;
    query.exec("create table User (ID int auto_increment primary key,Device int, Name vchar)");
    query.exec("create table IF NOT EXISTS Score \
               (ID int primary key,Name vchar,\
                Chinese int,Math int,\
                English int, Physics int, \
                Chemistry int, Biology int)");

               connect(ui->back,&QPushButton::clicked,this,&classwin::back_to_topwin);

}

classwin::~classwin()
{
    delete ui;
}

void classwin::on_pushButton_clicked()
{
    classwin::hide();
    Teacher_Dialog* my_Teacher_Dialog = new Teacher_Dialog();

    my_Teacher_Dialog->exec();

    delete my_Teacher_Dialog;
    classwin::show();
}

void classwin::on_pushButton_setting_clicked()
{
    classwin::hide();
    Student_Setting* my_Student_Setting = new Student_Setting();

    my_Student_Setting->exec();

    delete my_Student_Setting;
    classwin::show();

}

void classwin::on_pushButton_student_clicked()
{
    classwin::hide();
    Student_Score* my_Student_Score = new Student_Score();

    my_Student_Score->exec();


    delete my_Student_Score;
    classwin::show();
}

void classwin::on_pushButton_teacher_clicked()
{
    classwin::hide();
    Teacher_Score* my_Teacher_Score = new Teacher_Score();

    my_Teacher_Score->exec();

    delete my_Teacher_Score;

    classwin::show();

}

void classwin::back_to_topwin()
{
    emit back_topwin(true);
    classwin::hide();
}
