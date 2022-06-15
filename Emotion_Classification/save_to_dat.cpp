#include "save_to_dat.h"

save_to_dat::save_to_dat(QVector<double> &input_vec,QVector<double> &input_vec1,QString current_date)
{
    QString att_1,att_2;
    if(input_vec1.size() >= 2)
    {
        att_1 = QString::number(input_vec1[0],10,2);
        att_2 = QString::number(input_vec1[1],10,2);
    }

    QString path_str;
    path_str.append(att_1);
    path_str.append("_");
    path_str.append(att_2);
    path_str.append(current_date);
    path_str.append(".dat");
    QFile path_f(path_str);
    if (path_f.open(QFile::ReadWrite | QIODevice::Append))
    {
        QDataStream stream(&path_f);
        stream << input_vec ;
    }
    path_f.close();
    qDebug() << "save dat finish";
}

