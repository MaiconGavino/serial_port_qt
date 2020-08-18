#include "dialog.h"
#include "ui_dialog.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    arduino_is_available = false;
    arduino_port_name = "";
    arduino=new QSerialPort;


/* Identificar a porta, o ID do fornecedor e o ID do produto
    qDebug() << "Porta Numero:" <<
                QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        qDebug() <<"Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier())
        {
            qDebug() <<"Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier())
        {
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }
*/

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
        {
            if(serialPortInfo.vendorIdentifier()==arduino_uno_vendor_id)
            {
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id)
                {
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
        if(arduino_is_available)
        {
            //abri e configurar o serial
            arduino->setPortName(arduino_port_name);
            arduino->open(QSerialPort::WriteOnly);
            arduino->setBaudRate(QSerialPort::Baud9600);
            arduino->setDataBits(QSerialPort::Data8);
            arduino->setParity(QSerialPort::NoParity);
            arduino->setStopBits(QSerialPort::OneStop);
            arduino->setFlowControl(QSerialPort::NoFlowControl);
        }
        else
        {
            //informar error
            QMessageBox::warning(this, "Port Error", "Arduino não conectado a porta");

        }
    }
}

Dialog::~Dialog()
{
    if(arduino->isOpen())
    {
        arduino->close();
    }
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    if(arduino->isWritable())
    {
        arduino->write("1");
    }
    else
    {
        qDebug() << "erro na porta serial";
    }
}

void Dialog::on_pushButton_2_clicked()
{
    if(arduino->isWritable())
    {
        arduino->write("0");
    }
}
