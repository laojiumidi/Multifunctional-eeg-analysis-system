#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setGeometry(250,250,643,292);
    connect(ui->clear,&QPushButton::clicked,this,&login::clear_slot);
    connect(ui->ensure,&QPushButton::clicked,this,&login::ensure_slot);

    ui->line_id->setText(ID);
    if(Aa == 1)
        ui->CapsLk->setText("ABC");
    if(Aa == 0)
        ui->CapsLk->setText("abc");

    connect(ui->K_0,&QPushButton::clicked,this,&login::K_0);
    connect(ui->K_1,&QPushButton::clicked,this,&login::K_1);
    connect(ui->K_2,&QPushButton::clicked,this,&login::K_2);
    connect(ui->K_3,&QPushButton::clicked,this,&login::K_3);
    connect(ui->K_4,&QPushButton::clicked,this,&login::K_4);
    connect(ui->K_5,&QPushButton::clicked,this,&login::K_5);
    connect(ui->K_6,&QPushButton::clicked,this,&login::K_6);
    connect(ui->K_7,&QPushButton::clicked,this,&login::K_7);
    connect(ui->K_8,&QPushButton::clicked,this,&login::K_8);
    connect(ui->K_9,&QPushButton::clicked,this,&login::K_9);
    connect(ui->K_A,&QPushButton::clicked,this,&login::K_A);
    connect(ui->K_B,&QPushButton::clicked,this,&login::K_B);
    connect(ui->K_C,&QPushButton::clicked,this,&login::K_C);
    connect(ui->K_D,&QPushButton::clicked,this,&login::K_D);
    connect(ui->K_E,&QPushButton::clicked,this,&login::K_E);
    connect(ui->K_F,&QPushButton::clicked,this,&login::K_F);
    connect(ui->K_G,&QPushButton::clicked,this,&login::K_G);
    connect(ui->K_H,&QPushButton::clicked,this,&login::K_H);
    connect(ui->K_I,&QPushButton::clicked,this,&login::K_I);
    connect(ui->K_J,&QPushButton::clicked,this,&login::K_J);
    connect(ui->K_K,&QPushButton::clicked,this,&login::K_K);
    connect(ui->K_L,&QPushButton::clicked,this,&login::K_L);
    connect(ui->K_M,&QPushButton::clicked,this,&login::K_M);
    connect(ui->K_N,&QPushButton::clicked,this,&login::K_N);
    connect(ui->K_O,&QPushButton::clicked,this,&login::K_O);
    connect(ui->K_P,&QPushButton::clicked,this,&login::K_P);
    connect(ui->K_Q,&QPushButton::clicked,this,&login::K_Q);
    connect(ui->K_R,&QPushButton::clicked,this,&login::K_R);
    connect(ui->K_S,&QPushButton::clicked,this,&login::K_S);
    connect(ui->K_T,&QPushButton::clicked,this,&login::K_T);
    connect(ui->K_U,&QPushButton::clicked,this,&login::K_U);
    connect(ui->K_V,&QPushButton::clicked,this,&login::K_V);
    connect(ui->K_W,&QPushButton::clicked,this,&login::K_W);
    connect(ui->K_X,&QPushButton::clicked,this,&login::K_X);
    connect(ui->K_Y,&QPushButton::clicked,this,&login::K_Y);
    connect(ui->K_Z,&QPushButton::clicked,this,&login::K_Z);
    connect(ui->K_space,&QPushButton::clicked,this,&login::space);
    connect(ui->CapsLk,&QPushButton::clicked,this,&login::CapsLk);
    connect(ui->K_back,&QPushButton::clicked,this,&login::backspace);
}

login::~login()
{
    delete ui;
}

void login::clear_slot()
{
    ID.clear();
    ui->line_id->setText(ID);
}

void login::ensure_slot()
{
    login_succ.show();
    ID_text=ui->line_id->text().trimmed();
    qDebug()<<ID_text<<endl;
    login::hide();
    qDebug()<<ID_text<<endl;
}


void login::K_0()
{
    ID.append("0");
    ui->line_id->setText(ID);
}

void login::K_1()
{
    ID.append("1");
    ui->line_id->setText(ID);
}

void login::K_2()
{
    ID.append("2");
    ui->line_id->setText(ID);
}

void login::K_3()
{
    ID.append("3");
    ui->line_id->setText(ID);
}

void login::K_4()
{
    ID.append("4");
    ui->line_id->setText(ID);
}

void login::K_5()
{
    ID.append("5");
    ui->line_id->setText(ID);
}

void login::K_6()
{
    ID.append("6");
    ui->line_id->setText(ID);
}

void login::K_7()
{
    ID.append("7");
    ui->line_id->setText(ID);
}

void login::K_8()
{
    ID.append("8");
    ui->line_id->setText(ID);
}

void login::K_9()
{
    ID.append("9");
    ui->line_id->setText(ID);
}

void login::K_A()
{
    if(Aa)
        ID.append("A");
    if(!Aa)
        ID.append("a");
    ui->line_id->setText(ID);
}

void login::K_B()
{
    if(Aa)
        ID.append("B");
    if(!Aa)
        ID.append("b");
    ui->line_id->setText(ID);
}

void login::K_C()
{
    if(Aa)
        ID.append("C");
    if(!Aa)
        ID.append("c");
    ui->line_id->setText(ID);
}

void login::K_D()
{
    if(Aa)
        ID.append("D");
    if(!Aa)
        ID.append("d");
    ui->line_id->setText(ID);
}

void login::K_E()
{
    if(Aa)
        ID.append("E");
    if(!Aa)
        ID.append("e");
    ui->line_id->setText(ID);
}

void login::K_F()
{
    if(Aa)
        ID.append("F");
    if(!Aa)
        ID.append("f");
    ui->line_id->setText(ID);
}

void login::K_G()
{
    if(Aa)
        ID.append("G");
    if(!Aa)
        ID.append("g");
    ui->line_id->setText(ID);
}

void login::K_H()
{
    if(Aa)
        ID.append("H");
    if(!Aa)
        ID.append("h");
    ui->line_id->setText(ID);
}

void login::K_I()
{
    if(Aa)
        ID.append("I");
    if(!Aa)
        ID.append("i");
    ui->line_id->setText(ID);
}

void login::K_J()
{
    if(Aa)
        ID.append("J");
    if(!Aa)
        ID.append("j");
    ui->line_id->setText(ID);
}

void login::K_K()
{
    if(Aa)
        ID.append("K");
    if(!Aa)
        ID.append("k");
    ui->line_id->setText(ID);
}

void login::K_L()
{
    if(Aa)
        ID.append("L");
    if(!Aa)
        ID.append("l");
    ui->line_id->setText(ID);
}

void login::K_M()
{
    if(Aa)
        ID.append("M");
    if(!Aa)
        ID.append("m");
    ui->line_id->setText(ID);
}

void login::K_N()
{
    if(Aa)
        ID.append("N");
    if(!Aa)
        ID.append("n");
    ui->line_id->setText(ID);
}

void login::K_O()
{
    if(Aa)
        ID.append("O");
    if(!Aa)
        ID.append("o");
    ui->line_id->setText(ID);
}

void login::K_P()
{
    if(Aa)
        ID.append("P");
    if(!Aa)
        ID.append("p");
    ui->line_id->setText(ID);
}

void login::K_Q()
{
    if(Aa)
        ID.append("Q");
    if(!Aa)
        ID.append("q");
    ui->line_id->setText(ID);
}

void login::K_R()
{
    if(Aa)
        ID.append("R");
    if(!Aa)
        ID.append("r");
    ui->line_id->setText(ID);
}

void login::K_S()
{
    if(Aa)
        ID.append("S");
    if(!Aa)
        ID.append("s");
    ui->line_id->setText(ID);
}

void login::K_T()
{
    if(Aa)
        ID.append("T");
    if(!Aa)
        ID.append("t");
    ui->line_id->setText(ID);
}

void login::K_U()
{
    if(Aa)
        ID.append("U");
    if(!Aa)
        ID.append("u");
    ui->line_id->setText(ID);
}

void login::K_V()
{
    if(Aa)
        ID.append("V");
    if(!Aa)
        ID.append("v");
    ui->line_id->setText(ID);
}

void login::K_W()
{
    if(Aa)
        ID.append("W");
    if(!Aa)
        ID.append("w");
    ui->line_id->setText(ID);
}

void login::K_X()
{
    if(Aa)
        ID.append("X");
    if(!Aa)
        ID.append("x");
    ui->line_id->setText(ID);
}

void login::K_Y()
{
    if(Aa)
        ID.append("Y");
    if(!Aa)
        ID.append("y");
    ui->line_id->setText(ID);
}

void login::K_Z()
{
    if(Aa)
        ID.append("Z");
    if(!Aa)
        ID.append("z");
    ui->line_id->setText(ID);
}

void login::CapsLk()
{
    if(Aa == 0)
    {
        Aa = 1;
        ui->CapsLk->setText("ABC");
    }
    else {
        Aa = 0;
        ui->CapsLk->setText("abc");
    }
}

void login::space()
{
    ID.append(" ");
    ui->line_id->setText(ID);
}

void login::backspace()
{
    ID = ID.left(ID.length()-1);
    ui->line_id->setText(ID);
}
