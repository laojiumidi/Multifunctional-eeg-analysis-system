#ifndef DRIVE_H
#define DRIVE_H

#include <QWidget>
#include "dr_result.h"
#include "dr_monitor.h"
#include "login.h"

namespace Ui {
class drive;
}

class drive : public QWidget
{
    Q_OBJECT

public:
    explicit drive(QWidget *parent = 0);
    ~drive();

    dr_monitor monitor;
    dr_result result;
    login dr_login;

private:
    Ui::drive *ui;

signals:
   void back_topwin(bool corr);

public slots:
   void back_to_topwin();

   void monitor_show();
   void monitor_to_drivewin(bool corr);

   void result_show();
   void result_to_drivewin(bool corr);

   void dr_login_show();


};

#endif // DRIVE_H
