#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QString>
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include <QtGlobal>
#include <QXmlStreamReader>
#include <QFile>
#include <QTextStream>
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->txtUrl->setText("http://www.tcmb.gov.tr/kurlar/today.xml");
    connect(ui->btnClient,SIGNAL(clicked(bool)),this,SLOT(pageConnect()));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(mySlot()));
}

void MainWindow::pageConnect(){

    url=ui->txtUrl->text();
    qDebug()<<"pageConnecting....";

    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString xml = response->readAll(); // Source should be stored here

    if(response->isFinished()){
        ui->textBrowser->setText(xml);
        qDebug()<<"xml: dosyaya yazıldı.";
        writeFile(filePath,xml);
    }
}

void MainWindow::writeFile(QString path,QString text){
    QString filename=path;
    QFile file( filename );
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream( &file );
        stream << text.toLatin1()<<endl;
    }else{
        qDebug()<<"Dosya yazılırken hata oluştu.";
    }
}

void MainWindow::mySlot(){
    parseXml();
}

void MainWindow::parseXml(){
    QFile file(filePath);
    qDebug()<<filePath;

    if(!file.open(QFile::ReadWrite| QFile::Text)){
        qDebug() << "Cannot read file" << file.errorString();
        exit(0);
    }

    QXmlStreamReader reader(&file);
    doviz d;
    if (reader.readNextStartElement()) {
        if (reader.name() == "Tarih_Date"){
            while(reader.readNextStartElement()){
                if(reader.name() == "Currency"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "CurrencyName"){
                            QString s = reader.readElementText();
                            d.name = s;
                            qDebug()<<s;
                        }else if(reader.name() == "ForexBuying"){
                            QString s = reader.readElementText();
                            d.value=s;
                            qDebug()<<s;
                        }
                        else{
                            reader.skipCurrentElement();
                        }
                    }
                    qDebug()<<"appand";
                    dovizList.append(d);
                }
                else
                    reader.skipCurrentElement();
            }
        }
        else
            reader.raiseError(QObject::tr("Incorrect file"));
        qDebug()<<"*******";
    }
}

void MainWindow::htmlRead(){
    qDebug()<<"htmlReading";
}

void MainWindow::updateProgress(qint64 bytesReceived,qint64 bytesTotal){
    qDebug()<<"----------------------------------------------------";
    qDebug()<<"read: "<<bytesReceived<<"total: "<<bytesTotal;
    qDebug()<<"----------------------------------------------------";
}


MainWindow::~MainWindow()
{
    delete ui;
}

