#ifndef TOPWIN_H
#define TOPWIN_H

#include <QWidget>
#include "testwin.h"
#include "drivewin.h"
#include "classwin.h"
#include "standby.h"

namespace Ui {
class topwin;
}

class topwin : public QWidget
{
    Q_OBJECT

public:
    explicit topwin(QWidget *parent = 0);
    ~topwin();

    Widget testwin;
    drive drivewin;
    classwin teachwin;
    standby sleep;

signals:


public slots:
    void testwin_show();
    void testwin_to_topwin(bool corr);

    void drivewin_show();
    void drivewin_to_topwin(bool corr);

    void teachwin_show();
    void teachwin_to_topwin(bool corr);

    void system_sleep();
    void system_weak(bool corr);

private:
    Ui::topwin *ui;
};

#endif // TOPWIN_H
