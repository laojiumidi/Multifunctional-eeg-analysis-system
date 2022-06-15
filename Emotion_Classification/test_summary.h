#ifndef SUMMARY_H
#define SUMMARY_H

#include <QWidget>
#include "login.h"
#include "test_start.h"
#include <QDebug>

namespace Ui {
class summary;
}

class summary : public QWidget
{
    Q_OBJECT

public:
    explicit summary(QWidget *parent = 0);
    ~summary();
    login log;
    MainWindow mainw;
    int time;
    double posi_rate;
signals:
    void back_testwin(bool corr);
public slots:
   void back_to_testwin();

   void summary_show(bool corr);
private:
    Ui::summary *ui;
};

#endif // SUMMARY_H
