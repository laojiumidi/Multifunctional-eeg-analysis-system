#include "change_datebase.h"

Change_Datebase::Change_Datebase()
{
    model = new QSqlRelationalTableModel();
    model->setEditStrategy(QSqlTableModel::OnFieldChange); //字段变化时写入数据库
    model->setTable("User");
    model->select();
}

QStringList Change_Datebase::get_all_name()
{
    model->setTable("User");
    model->select();

    QStringList NameList;
    for(int i=0;i<model->rowCount();i++)
    {
        QSqlRecord record = model->record(i);
        NameList.append(record.value("name").toString());
    }
    return NameList;
}

//Change_Datebase::~Change_Datebase()
//{
//    delete model;
//}
