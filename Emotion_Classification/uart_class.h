#ifndef UART_CLASS_H
#define UART_CLASS_H

#include <QObject>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>

#include "test_start.h"

class Uart_Class : public QObject
{
    Q_OBJECT
public:
    Uart_Class();
    ~Uart_Class();
    void start();

    void open_EEG();

    void close_EEG();

    void over();

    int select_flag;

private:
    QSerialPort *myCom;//声明对象

    QTimer *readTimer;

signals:
    void new_Date_max(const QVector<double> &vec, const QVector<double> &vec1);

    void new_Date_EEG(const QVector<double> &vec, const QVector<double> &vec1, const QVector<double> &vec2);

private slots:
    void readMyCom(); //读取串口
};

#endif // UART_CLASS_H
