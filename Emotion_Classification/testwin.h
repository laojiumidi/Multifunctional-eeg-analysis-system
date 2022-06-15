#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDialog>
#include <QProcess>
#include <QApplication>
#include "login.h"
//#include "test_film.h"
#include "test_summary.h"

static const int RETCODE_RESTART = 773;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

//    MulPlayer film;
    summary summ;

signals:
    void back_topwin(bool corr);

    void summary_show(bool corr);
public slots:
    void login_show();

    void start_show();
    void start_to_testwin(bool corr);

    void summary_showup();
    void summary_to_testwin(bool corr);

//    void film_show();
//    void film_to_testwin(bool corr);

    void back_to_topwin();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
