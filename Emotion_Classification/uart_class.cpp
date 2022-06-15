#include "uart_class.h"

Uart_Class::Uart_Class()
{
    qDebug() << "Uart_Class in:" ;

    readTimer = new QTimer();

    connect(readTimer,SIGNAL(timeout()),this,SLOT(readMyCom()));
}

Uart_Class::~Uart_Class()
{
//    delete myCom;
}

void Uart_Class::start()
{
    myCom = new QSerialPort();
    myCom->setPortName("/dev/ttySAC3");
    myCom->open(QIODevice::ReadWrite);
    myCom->setBaudRate(QSerialPort::Baud57600);
    myCom->setDataBits(QSerialPort::Data8);
    myCom->setParity(QSerialPort::NoParity);
    myCom->setStopBits(QSerialPort::OneStop);
    myCom->setFlowControl(QSerialPort::NoFlowControl);

    readTimer->start(1000);
    qDebug() << "Uart_Class start:" ;
}

void Uart_Class::open_EEG()
{
    select_flag = 1;
}

void Uart_Class::close_EEG()
{
    select_flag = 0;
}

void Uart_Class::over()
{
    readTimer->stop();

    myCom->clear();
    myCom->close();
    myCom->deleteLater();
}

void Uart_Class::readMyCom()
{

    static vector<unsigned char> uart_buff_vec;

    QByteArray temp = myCom->readAll();

    int len_temp = temp.size();
    qDebug() << "len_temp:" << len_temp;
    if(len_temp == 0)
    {
        return;
    }
    for(int i=0;i<len_temp;i++)
    {
        uart_buff_vec.push_back(temp[i]);
    }

    date_accquire* my_date_accquire = new date_accquire();

    my_date_accquire->Attention_accquire(uart_buff_vec);
    qDebug() << "Length_Of_ATT is:" << my_date_accquire->Attention_vec.size();
    emit new_Date_max(my_date_accquire->Attention_vec,my_date_accquire->Meditation_vec);

    if(select_flag == 1)
    {
        my_date_accquire->original_date_accquire(uart_buff_vec);
        qDebug() << "Length_Of_EEG is:" << my_date_accquire->EEG_signal.size();
        emit new_Date_EEG(my_date_accquire->EEG_signal, my_date_accquire->Attention_vec, my_date_accquire->Meditation_vec);
    }
    delete my_date_accquire;

    uart_buff_vec.clear();
}
