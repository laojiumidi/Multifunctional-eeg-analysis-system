#ifndef SAVE_TO_DAT_H
#define SAVE_TO_DAT_H

#include <QVector>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QDataStream>


class save_to_dat
{
public:
    save_to_dat(QVector<double> &input_vec, QVector<double> &input_vec1, QString current_date);
};

#endif // SAVE_TO_DAT_H
