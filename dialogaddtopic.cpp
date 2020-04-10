#include "dialogaddtopic.h"
#include "ui_dialogaddtopic.h"

#include <QDebug>

DialogAddTopic::DialogAddTopic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddTopic)
{
    ui->setupUi(this);
}

DialogAddTopic::~DialogAddTopic()
{
    delete ui;
}

void DialogAddTopic::on_buttonBox_clicked(QAbstractButton *button)
{
    if((QPushButton *)button == ui -> buttonBox -> button(QDialogButtonBox::Ok)) //(QDialogButtonBox::Reset))
    {
        QString nameNewTopic = ui -> lineEdit -> text();
        emit signalCreateTopic(nameNewTopic);
    }
    ui -> lineEdit -> clear();
}

void DialogAddTopic::slotListTopic(QStringList)
{

}
