#ifndef STANDBY_H
#define STANDBY_H

#include <QWidget>

namespace Ui {
class standby;
}

class standby : public QWidget
{
    Q_OBJECT

public:
    explicit standby(QWidget *parent = 0);
    ~standby();

private:
    Ui::standby *ui;

signals:
    void weak(bool corr);

public slots:
    void system_weak();
};

#endif // STANDBY_H
