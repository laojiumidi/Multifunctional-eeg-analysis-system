#include "success_warning.h"
#include "ui_success_warning.h"

success_warning::success_warning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::success_warning)
{
    ui->setupUi(this);
    setGeometry(380,300,177,149);
    setWindowTitle("Success!");
}

success_warning::~success_warning()
{
    delete ui;
}

void success_warning::warning_slot(bool corr)
{
    if(corr)
        success_warning::show();
}
