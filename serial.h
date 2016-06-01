#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QtDebug>
#include <QComboBox>
#include <QMessageBox>
#include <QtGui>
#include <QTableView>
#include <QHeaderView>
#include <QTextEdit>
#include <QTextBrowser>
#include <QtSerialPort/QSerialPort>

class MySerialPort : public QWidget
{
    Q_OBJECT

public:
    MySerialPort(QWidget *parent = 0);
    ~MySerialPort();

    QHBoxLayout * hl0;
    QHBoxLayout * hl1;
    QHBoxLayout * hl2;
    QHBoxLayout * hl3;
    QHBoxLayout * hl4;
    QHBoxLayout * hl5;
    QHBoxLayout * hl6;
    QHBoxLayout * hl7;
    QHBoxLayout * hl8;

    QVBoxLayout * vl0;
    QVBoxLayout * vl1;

    QGridLayout *  gl0;

    QLabel * lb0;
    QLabel * lb1;
    QLabel * lb2;
    QLabel * lb3;
    QLabel * lb4;
    QLabel * lb5;
    QLabel * lb6;

    QComboBox * cb0;
    QComboBox * cb1;
    QComboBox * cb2;
    QComboBox * cb3;
    QComboBox * cb4;

    QPushButton * pb0;
    QPushButton * pb1;
    QPushButton * pb2;
    QPushButton * pb3;
    QPushButton * pb4;

     QTextEdit* te0;
     QLineEdit* le0;

public slots:
    bool readFromSerial(void);
    bool sendToSerial(void);
    bool send(QByteArray data);
    void openSerial(void);
    void clearSendArea(void);
    void clearGetArea(void);
    void saveData(void);


public:
    void TranTest(void);

public:
    QSerialPort serial;
    QByteArray  readBuf;
    QTimer timer;
    int msg;

    int tem;
    int tem_node;
    int tem_shi;
    int tem_ge;


    int lightIntensity;
    int light_node;
    int light_shi;
    int light_ge;

    int flux;
    int flux_shi;
    int flux_ge;
    int flux_node;

    void UIload(void);
    void UIlayout(void);
    void setBaudRate(void);
    void setDataBit(void);
    void setParity(void);
    void setStopBits(void);
    void setComponemtAttribute(void);
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    QGridLayout * gl_tab;
    QTabWidget * QTab_UI;
    MySerialPort * QTab_SerP;
    QWidget * help;
    QTextBrowser * tw0;
    QVBoxLayout * v0_for_help;
    QTimer *timer;
public slots:
    void showEmptyPosi(void);
public:

    int tem;
    int tem_node;
    int tem_shi;
    int tem_ge;


    int lightIntensity;
    int light_node;
    int light_shi;
    int light_ge;

    int flux;
    int flux_shi;
    int flux_ge;
    int flux_node;

    void loadDocument(void);
};

#endif // WIDGET_H
