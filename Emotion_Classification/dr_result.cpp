#include "dr_result.h"
#include "ui_dr_result.h"

dr_result::dr_result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dr_result)
{
    ui->setupUi(this);
    //    barchart.d_chart
    flag_barshow = 0;
    QStringList strategyTableHeadList;
    strategyTableHeadList.append(tr("      User      "));
    strategyTableHeadList.append(tr("      Warning Time      "));
    strategyTableHeadList.append(tr("      TimeLapse      "));
    strategyTableHeadList.append(tr("      AVE Attention      "));
    strategyTableHeadList.append(tr("Dates"));
    ui->strategyTableWidget->setColumnCount(5);
    ui->strategyTableWidget->setHorizontalHeaderLabels(strategyTableHeadList);

    QHeaderView *strategyHeader = ui->strategyTableWidget->verticalHeader();
    strategyHeader->setHidden(true);// 隐藏行号

    ui->strategyTableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->strategyTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->delStrPushButton,SIGNAL(clicked(bool)),this,SLOT(delStrPtnClicked()));
    connect(ui->editStrPushButton,SIGNAL(clicked(bool)),this,SLOT(writeXML()));

    connect(ui->back,&QPushButton::clicked,this,&dr_result::back_to_drivewin);

    connect(ui->barpic,&QPushButton::clicked,this,&dr_result::barchart);

    readXML();
}


void dr_result::readXML(){
    QFile file("/opt/ec/dr_res.xml");
//        QFile file("dr_res.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug()<<"Error: cannot open file";
        return;
    }
    qDebug()<<"read file";
    QXmlStreamReader reader;
    reader.setDevice(&file);
    while (!reader.atEnd()){
        QXmlStreamReader::TokenType type = reader.readNext();
        if (type == QXmlStreamReader::Characters&& !reader.isWhitespace()){
            QString temp(reader.text().toUtf8());
            m_data.append(temp);
        }
    }
    int k=0;
    if(m_data.size()/5==0)
        return;
    for(int i=0;i<m_data.size()/5;i++){
        ui->strategyTableWidget->insertRow(ui->strategyTableWidget->rowCount());
        for(int j=0;j<5;j++){
            QTableWidgetItem *newItem=new QTableWidgetItem();
            newItem->setText(m_data.at(k++));
            ui->strategyTableWidget->setItem(i,j,newItem);
        }
    }
    ui->strategyTableWidget->horizontalHeader()->setStretchLastSection(true);
    for(int i = 0;i<ui->strategyTableWidget->rowCount();i++)
    {
        for(int j = 0;j<ui->strategyTableWidget->columnCount();j++)
        {
            ui->strategyTableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
        ui->strategyTableWidget->horizontalHeader()->setSectionResizeMode(i,QHeaderView::ResizeToContents);
    }
}

void dr_result::delStrPtnClicked(){
    if(ui->strategyTableWidget->currentItem()==NULL)
        return;
    ui->strategyTableWidget->removeRow(ui->strategyTableWidget->currentRow());

}

void dr_result::writeXML(){
    QFile file("/opt/ec/dr_res.xml");
//        QFile file("dr_res.xml");
    if (!file.open(QFile::ReadWrite|QIODevice::Truncate)){
        qDebug() << "Error: cannot open file";
        return;
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("strategy");
    for(int i=0;i<ui->strategyTableWidget->rowCount();i++){
        writer.writeStartElement("number");
        writer.writeTextElement("user",ui->strategyTableWidget->item(i,0)->text());
        writer.writeTextElement("warn_times",ui->strategyTableWidget->item(i,1)->text());
        writer.writeTextElement("timelapse",ui->strategyTableWidget->item(i,2)->text());
        writer.writeTextElement("ave_att",ui->strategyTableWidget->item(i,3)->text());
        writer.writeTextElement("date",ui->strategyTableWidget->item(i,4)->text());
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}

dr_result::~dr_result()
{
    delete ui;
}

void dr_result::back_to_drivewin()
{
    emit back_drivewin(true);
    dr_result::hide();
}

void dr_result::writetable()
{
    RowCont=ui->strategyTableWidget->rowCount();
    ui->strategyTableWidget->insertRow(RowCont);

    ui->strategyTableWidget->setItem(RowCont,0,new QTableWidgetItem(user));
    ui->strategyTableWidget->setItem(RowCont,1,new QTableWidgetItem(warn_times));
    ui->strategyTableWidget->setItem(RowCont,2,new QTableWidgetItem(timelapse));
    ui->strategyTableWidget->setItem(RowCont,3,new QTableWidgetItem(ave_att));
    ui->strategyTableWidget->setItem(RowCont,4,new QTableWidgetItem(date));

    ui->strategyTableWidget->horizontalHeader()->setStretchLastSection(true);

    for(int j = 0;j<ui->strategyTableWidget->columnCount();j++)
    {
        ui->strategyTableWidget->item(RowCont,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}

void dr_result::barchart()
{
    int RowCont;
    QString usr;
    int sumtimes = 1;
    int warntimes;
    bool flag_repeat = 0;
    userList.clear();
    sum_times.clear();
    sum_warn_times.clear();
    RowCont=ui->strategyTableWidget->rowCount();
    for(int i = 0;i<RowCont;i++)
    {
        usr = ui->strategyTableWidget->item(i,0)->text();
        for(int k = 0;k<userList.count();k++)
        {
            if(usr == userList.at(k))
            {
                flag_repeat = !flag_repeat;
                break;
            }
        }
        if(!flag_repeat)
        {
            warntimes = ui->strategyTableWidget->item(i,1)->text().toInt();
            for(int j = i+1;j<RowCont;j++)
            {
                if(ui->strategyTableWidget->item(j,0)->text() == usr)
                {
                    sumtimes++;
                    warntimes += ui->strategyTableWidget->item(j,1)->text().toInt();
                }
            }
            userList.append(usr);
            sum_times.append(sumtimes);
            sum_warn_times.append(warntimes);
        }
        sumtimes = 1;
        warntimes = 0;
        flag_repeat = 0;
    }
    if(!flag_barshow)
    {
        barcharts.setbar(userList,sum_times,sum_warn_times);
        flag_barshow = !flag_barshow;
        ui->barpic->setText("Close BarChart");
    }
    else
    {
        barcharts.hide();
        //        barcharts.setWindowFlags(barcharts.windowFlags() &~ Qt::WindowStaysOnTopHint);
        flag_barshow = !flag_barshow;
        ui->barpic->setText("Show BarChart");
    }

}













