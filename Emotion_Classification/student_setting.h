#ifndef STUDENT_SETTING_H
#define STUDENT_SETTING_H

#include <QDialog>

#include <QSqlRelationalTableModel>
#include <QSqlRecord>

#include <QMessageBox>

#include <QDebug>

namespace Ui {
class Student_Setting;
}

class Student_Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Student_Setting(QWidget *parent = 0);
    ~Student_Setting();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_add1_clicked();

private:
    Ui::Student_Setting *ui;

    QSqlRelationalTableModel *model;
};

#endif // STUDENT_SETTING_H
