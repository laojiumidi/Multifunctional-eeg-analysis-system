#ifndef CLASSWIN_H
#define CLASSWIN_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "teacher_dialog.h"
#include "student_setting.h"
#include "student_score.h"
#include "teacher_score.h"

namespace Ui {
class classwin;
}

class classwin : public QWidget
{
    Q_OBJECT

public:
    explicit classwin(QWidget *parent = 0);
    ~classwin();

signals:
    void back_topwin(bool corr);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_setting_clicked();

    void on_pushButton_student_clicked();

    void on_pushButton_teacher_clicked();

    void back_to_topwin();
private:
    Ui::classwin *ui;
};

#endif // CLASSWIN_H

