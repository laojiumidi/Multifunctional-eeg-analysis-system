#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QDebug>
#include "success_warning.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    QString ID;
    QString ID_text;
    int Aa = 0;

    success_warning login_succ;

signals:

public slots:
    void clear_slot();
    void ensure_slot();

public:
    void K_0();
    void K_1();
    void K_2();
    void K_3();
    void K_4();
    void K_5();
    void K_6();
    void K_7();
    void K_8();
    void K_9();
    void K_A();
    void K_B();
    void K_C();
    void K_D();
    void K_E();
    void K_F();
    void K_G();
    void K_H();
    void K_I();
    void K_J();
    void K_K();
    void K_L();
    void K_M();
    void K_N();
    void K_O();
    void K_P();
    void K_Q();
    void K_R();
    void K_S();
    void K_T();
    void K_U();
    void K_V();
    void K_W();
    void K_X();
    void K_Y();
    void K_Z();
    void CapsLk();
    void backspace();
    void space();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
