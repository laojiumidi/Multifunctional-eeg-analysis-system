#ifndef SUCCESS_WARNING_H
#define SUCCESS_WARNING_H

#include <QWidget>

namespace Ui {
class success_warning;
}

class success_warning : public QWidget
{
    Q_OBJECT

public:
    explicit success_warning(QWidget *parent = 0);
    ~success_warning();
signals:

public slots:
    void warning_slot(bool corr);
private:
    Ui::success_warning *ui;
};

#endif // SUCCESS_WARNING_H
