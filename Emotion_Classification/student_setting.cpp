#include "student_setting.h"
#include "ui_student_setting.h"

Student_Setting::Student_Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Student_Setting)
{
    ui->setupUi(this);
    setGeometry(0,0,1024,768);
    //sql
    model = new QSqlRelationalTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnFieldChange); //字段变化时写入数据库
    model->setTable("User");

    model->select();
    ui->tableView->horizontalHeader()->setDefaultSectionSize(180);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);    //使其不可编辑
    ui->tableView->verticalHeader()->hide();
}

Student_Setting::~Student_Setting()
{
    delete ui;
//    delete model;
}

void Student_Setting::on_pushButton_back_clicked()
{
    accept();
}

void Student_Setting::on_pushButton_add_clicked()
{
    int temp = ui->lineEdit_id->text().isEmpty() + \
            ui->lineEdit_device->text().isEmpty() + \
            ui->lineEdit_name->text().isEmpty();
    if(temp==0)
    {
        model->setTable("User");
        model->select();
        int rowNum = model->rowCount();
        model->insertRow(rowNum); //添加一行
        model->setData(model->index(rowNum,0),ui->lineEdit_id->text());
        model->setData(model->index(rowNum,1),ui->lineEdit_device->text());
        model->setData(model->index(rowNum,2),ui->lineEdit_name->text());
        if(model->submitAll())//可以直接提交
        {
            qDebug() << "submit success.";
        }
        else
        {
            QMessageBox::warning(this,tr("添加"),tr("学号已经存在"),QMessageBox::Yes);
            qDebug() << "submit fail.";
        }

        model->setTable("Score");
        model->select();
        rowNum = model->rowCount();
        model->insertRow(rowNum); //添加一行
        model->setData(model->index(rowNum,0),ui->lineEdit_id->text());
        model->setData(model->index(rowNum,1),ui->lineEdit_name->text());

        if(model->submitAll())//可以直接提交
        {
            qDebug() << "submit success.";
        }
        else
        {
            QMessageBox::warning(this,tr("添加"),tr("学号已经存在"),QMessageBox::Yes);
            qDebug() << "submit fail.";
        }

        model->setTable("User");
        model->select();
    }
}

void Student_Setting::on_pushButton_add1_clicked()
{
     QMessageBox::warning(this,tr("添加"),tr("添加成功!"),QMessageBox::Yes);
     model->setTable("Score");
     model->select();
}
