#ifndef CHANGE_DATEBASE_H
#define CHANGE_DATEBASE_H

#include <QString>
#include <QStringList>
//sql
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>

class Change_Datebase
{
public:
    Change_Datebase();

    QStringList get_all_name();

//    ~Change_Datebase();

private:
    QSqlRelationalTableModel *model;
};

#endif // CHANGE_DATEBASE_H
