#include "serial.h"
#include <QFile>
#include <QTextStream>
#include <QtSerialPort/QSerialPortInfo>
#include <QTime>
#include <QDate>
#include <QTimer>
#include <QString>
#include <QComboBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(tr("SerialPort"));
    QTab_UI= new QTabWidget;
    QTab_SerP = new MySerialPort;
    help = new QWidget;

    gl_tab = new QGridLayout;
    v0_for_help = new QVBoxLayout;
    QTab_UI->addTab(QTab_SerP,tr("(&T)串口设置界面"));
    QTab_UI->addTab(help,tr("(&H)帮助页面"));

    gl_tab->addWidget(QTab_UI);
    gl_tab->setContentsMargins(0,0,0,0);
    this->setLayout(gl_tab); // 为窗口设置布局
    timer = new QTimer(this); // 定时器 1秒 用于更新车位的状态
    timer->start(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(showEmptyPosi()));
    loadDocument(); // 加载帮助界面的文档
}

Widget::~Widget()
{

}

MySerialPort::MySerialPort(QWidget *parent)
{
    UIload();
    UIlayout();
    setComponemtAttribute();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        cb0->addItem(info.portName());
    }

    connect(pb0,SIGNAL(clicked(bool)),this,SLOT(openSerial()));
    connect(pb3,SIGNAL(clicked(bool)),this,SLOT(sendToSerial()));
    connect(&serial,SIGNAL(readyRead()),this,SLOT(readFromSerial()));
    connect(pb1,SIGNAL(clicked(bool)),this,SLOT(clearSendArea()));
    connect(pb4,SIGNAL(clicked(bool)),this,SLOT(clearGetArea()));
    connect(pb2,SIGNAL(clicked(bool)),this,SLOT(saveData()));
}

MySerialPort::~MySerialPort()
{

}

bool MySerialPort::readFromSerial()
{
    readBuf.append(serial.readAll());
    te0->append(readBuf);
    msg = readBuf[3];
    if(msg == 103){
        light_node = readBuf[0]-0x30;
        light_shi = readBuf[1] - 0x30;
        light_ge = readBuf[2] - 0x30;
        lightIntensity = light_shi * 10 + light_ge;
    }else if(msg == 119){
        tem_node = readBuf[0]-0x30;
        tem_shi = readBuf[1] - 0x30;
        tem_ge = readBuf[2] - 0x30;
        tem = tem_shi * 10 + tem_ge;
    }else if(msg == 115){
        flux_shi = readBuf[1] - 0x30;
        flux_ge = readBuf[2] - 0x30;
        flux = flux_shi * 10 + flux_shi;
    }


    qDebug()<<readBuf.length();
    qDebug()<<readBuf[0];
    qDebug()<<readBuf[1];
    qDebug()<<readBuf[2];

    readBuf.clear();
}

bool MySerialPort::sendToSerial()
{
    serial.write(le0->text().toLocal8Bit());
}

bool MySerialPort::send(QByteArray data)
{
     serial.write(data);
}

void MySerialPort::openSerial()
{

    if(pb0->text()=="(&O)打开串口"){
        pb0->setText(tr("(&O)关闭串口"));
        serial.setPortName(cb0->currentText());
        serial.open(QIODevice::ReadWrite);
        setBaudRate();
        setDataBit();
        setParity();
        setStopBits();

        cb0->setEnabled(false);
        cb1->setEnabled(false);
        cb2->setEnabled(false);
        cb3->setEnabled(false);
        cb4->setEnabled(false);
    }else{
        serial.close();
        pb0->setText(tr("(&O)打开串口"));
        cb0->setEnabled(true);
        cb1->setEnabled(true);
        cb2->setEnabled(true);
        cb3->setEnabled(true);
        cb4->setEnabled(true);
    }
}

void MySerialPort::clearSendArea()
{
    te0->clear();
}

void MySerialPort::clearGetArea()
{
    le0->clear();
}

void MySerialPort::saveData()
{    QTime tim;
     qDebug()<<tim.currentTime().toString();
     QDate td;
     qDebug()<<td.currentDate().toString();

    QFile data("SerialPortRecord.txt");
    if (data.open(QFile::WriteOnly | QFile::Append)) {
        QTextStream out(&data);
        out<<"Save time:"<<td.currentDate().toString()<<"    " \
          <<tim.currentTime().toString()\
          <<"\nData:"<<te0->document()->toPlainText()<<"\n\n";
    }
}

void MySerialPort::TranTest()
{

}

void MySerialPort::UIload()
{
    hl0 = new QHBoxLayout;
    hl1 = new QHBoxLayout;
    hl2 = new QHBoxLayout;
    hl3 = new QHBoxLayout;
    hl4 = new QHBoxLayout;
    hl5 = new QHBoxLayout;
    hl6 = new QHBoxLayout;
    hl7 = new QHBoxLayout;
    hl8 = new QHBoxLayout;

    vl0 = new QVBoxLayout;
    vl1 = new QVBoxLayout;

    gl0 = new QGridLayout;

    lb0 = new QLabel(tr("(&B)串口号："));
    lb1 = new QLabel(tr("(&V)波特率："));
    lb2 = new QLabel(tr("(&E)数据位："));
    lb3 = new QLabel(tr("(&P)停止位："));
    lb4 = new QLabel(tr("(&J)校验位："));
    lb5 = new QLabel(tr("(&G)数据接收区："));
    lb6 = new QLabel(tr("(&D)数据发送区："));

    cb0 = new QComboBox;
    cb1 = new QComboBox;
    cb2 = new QComboBox;
    cb3 = new QComboBox;
    cb4 = new QComboBox;

    pb0 = new QPushButton(tr("(&O)打开串口"));
    pb1 = new QPushButton(tr("(&L)清空数据发送区"));
    pb2 = new QPushButton(tr("(&A)保存数据"));
    pb3 = new QPushButton(tr("(&E)发送数据"));
    pb4 = new QPushButton(tr("(&G)清空数据接收区"));

    te0 = new QTextEdit;
    le0 = new QLineEdit;

}

void MySerialPort::UIlayout()
{
    hl0->addWidget(lb0);
    hl0->addWidget(cb0);
    hl1->addWidget(lb1);
    hl1->addWidget(cb1);
    hl2->addWidget(lb2);
    hl2->addWidget(cb2);
    hl3->addWidget(lb3);
    hl3->addWidget(cb3);
    hl4->addWidget(lb4);
    hl4->addWidget(cb4);

    hl5->addWidget(pb1);
    hl5->addWidget(pb2);
    hl6->addWidget(pb3);
    hl6->addWidget(pb4);

    vl0->addWidget(pb0);
    vl0->addLayout(hl0);
    vl0->addLayout(hl1);
    vl0->addLayout(hl2);
    vl0->addLayout(hl3);
    vl0->addLayout(hl4);


    vl1->addWidget(lb6);
    vl1->addLayout(hl6);
    vl1->addWidget(le0);
    vl1->addWidget(lb5);
    vl1->addLayout(hl5);
    vl1->addWidget(te0);

    gl0->addLayout(vl0,0,0);
    gl0->addLayout(vl1,0,1);
    gl0->setSpacing(20);
    this->setLayout(gl0);

}

void MySerialPort::setBaudRate()
{
    if(cb1->currentText() == tr("9600"))
        serial.setBaudRate(QSerialPort::Baud9600);
    else if(cb1->currentText() == tr("1200"))
        serial.setBaudRate(QSerialPort::Baud1200);
    else if(cb1->currentText() == tr("2400"))
        serial.setBaudRate(QSerialPort::Baud2400);
    else if(cb1->currentText() == tr("4800"))
        serial.setBaudRate(QSerialPort::Baud4800);
    else if(cb1->currentText() == tr("19200"))
        serial.setBaudRate(QSerialPort::Baud19200);
    else if(cb1->currentText() == tr("38400"))
        serial.setBaudRate(QSerialPort::Baud38400);
    else if(cb1->currentText() == tr("57600"))
        serial.setBaudRate(QSerialPort::Baud57600);
    else if(cb1->currentText() == tr("115200"))
        serial.setBaudRate(QSerialPort::Baud115200);
}

void MySerialPort::setDataBit()
{
    if(cb2->currentText() == tr("Data5"))
        serial.setDataBits(QSerialPort::Data5);
    else if(cb2->currentText() == tr("Data6"))
        serial.setDataBits(QSerialPort::Data6);
    else if(cb2->currentText() == tr("Data7"))
        serial.setDataBits(QSerialPort::Data7);
    else if(cb2->currentText() == tr("Data8"))
        serial.setDataBits(QSerialPort::Data8);
}

void MySerialPort::setParity()
{
    if(cb4->currentText() == tr("NoParity"))
        serial.setParity(QSerialPort::NoParity);
    else if(cb4->currentText() == tr("EvenParity"))
        serial.setParity(QSerialPort::EvenParity);
    else if(cb4->currentText() == tr("OddParity"))
        serial.setParity(QSerialPort::OddParity);
    else if(cb4->currentText() == tr("SpaceParity"))
        serial.setParity(QSerialPort::SpaceParity);
    else if(cb4->currentText() == tr("MarkParity"))
        serial.setParity(QSerialPort::MarkParity);
}

void MySerialPort::setStopBits()
{
    if(cb3->currentText() == tr("OneStop"))
        serial.setStopBits(QSerialPort::OneStop);
    else if(cb3->currentText() == tr("OneAndHalfStop"))
        serial.setStopBits(QSerialPort::OneAndHalfStop);
    else if(cb3->currentText() == tr("TwoStop"))
        serial.setStopBits(QSerialPort::TwoStop);
}

void MySerialPort::setComponemtAttribute()
{
    cb1->addItem(tr("38400"));
    cb1->addItem(tr("9600"));
    cb1->addItem(tr("1200"));
    cb1->addItem(tr("2400"));
    cb1->addItem(tr("4800"));
    cb1->addItem(tr("19200"));
    cb1->addItem(tr("57600"));
    cb1->addItem(tr("115200"));

    cb2->addItem(tr("Data8"));
    cb2->addItem(tr("Data5"));
    cb2->addItem(tr("Data6"));
    cb2->addItem(tr("Data7"));

    cb3->addItem(tr("OneStop"));
    cb3->addItem(tr("OneAndHalfStop"));
    cb3->addItem(tr("TwoStop"));

    cb4->addItem(tr("NoParity"));
    cb4->addItem(tr("EvenParity"));
    cb4->addItem(tr("OddParity"));
    cb4->addItem(tr("SpaceParity"));
    cb4->addItem(tr("MarkParity"));

    pb0->setFixedWidth(120);
    pb1->setFixedWidth(120);
    pb2->setFixedWidth(120);
    pb3->setFixedWidth(120);
    pb4->setFixedWidth(120);

    te0->setEnabled(true);
    cb0->setFixedWidth(100);
    cb1->setFixedWidth(100);
    cb2->setFixedWidth(100);
    cb3->setFixedWidth(100);
    cb4->setFixedWidth(100);

    lb5->setBuddy(te0);
    lb6->setBuddy(le0);

    lb0->setBuddy(cb0);
    lb1->setBuddy(cb1);
    lb2->setBuddy(cb2);
    lb3->setBuddy(cb3);
    lb4->setBuddy(cb4);
}


void Widget::showEmptyPosi()
{
    tem = QTab_SerP->tem;
    tem_node = QTab_SerP->tem_node;
    lightIntensity = QTab_SerP->lightIntensity;
    light_node = QTab_SerP->light_node;
    flux = QTab_SerP->flux;
}

void Widget::loadDocument()
{
    tw0 = new QTextBrowser;
    v0_for_help->addWidget(tw0);
    help->setLayout(v0_for_help);
    QByteArray str;
    QFile file("Readme.txt");
    if(file.open(QFile::ReadOnly)){
        str.append(file.readAll());
        file.close();
    }
    tw0->setText(str);
}

