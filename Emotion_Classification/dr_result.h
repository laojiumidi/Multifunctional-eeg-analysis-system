#ifndef DR_RESULT_H
#define DR_RESULT_H

#include <QWidget>
#include <QFile>
#include <QVector>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <qwt_plot_renderer.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_barchart.h>
#include <qwt_column_symbol.h>
#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>
#include <qapplication.h>
#include <qmainwindow.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <QPaintEvent>
#include <qwt_plot.h>
#include <qwt_plot_histogram.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "bar.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class dr_result;
}

class dr_result : public QWidget
{
    Q_OBJECT

public:
    explicit dr_result(QWidget *parent = 0);
    void readXML();
    void barchart();
    ~dr_result();

    int RowCont;

    QString user;
    QString ave_att;
    QString date;
    QString timelapse;
    QString warn_times;

    QVector<int>sum_times;
    QVector<int>sum_warn_times;
    QStringList userList;

    bar barcharts;

    bool flag_barshow;

signals:
    void back_drivewin(bool corr);

public slots:
    void back_to_drivewin();

    void delStrPtnClicked();

    void writeXML();

    void writetable();

//    void bar_show();
private:
    Ui::dr_result *ui;

    QVector<QString> m_data;
};

#endif // DR_RESULT_H




