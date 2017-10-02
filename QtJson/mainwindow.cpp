#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDragEnterEvent>

#include <QFile>

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QStringRef>
#include <QUrl>
#include <QMimeData>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(mySlotJsonParse()));
    connect(ui->comboBox_1,SIGNAL(currentIndexChanged(int)),this,SLOT(mySlotComboBox1()));
    connect(ui->comboBox_2,SIGNAL(currentIndexChanged(int)),this,SLOT(mySlotComboBox2()));

    setAcceptDrops(true);

}

void MainWindow::mySlotJsonParse(){

    ui->listWidget->clear();
    ui->comboBox_1->clear();

    QFile jFile(jFilePath);
    if(jFile.open(QIODevice::ReadOnly)){
        qDebug()<<"File opened.";

        QStringList categories,subcategories;

        QString jFileString = (QString)jFile.readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(jFileString.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonCategories = jsonObject["categories"].toArray();

        foreach (const QJsonValue & value, jsonCategories ) {
            QJsonObject obj = value.toObject();
            categories<<(QString)obj["cat_id"].toString();
        }
        ui->comboBox_1->addItems(categories);
    }else{
        qDebug()<<"File can not open.";
    }
}

void MainWindow::mySlotComboBox1(){

    ui->comboBox_2->clear();

    QFile jFile(jFilePath);
    if(jFile.open(QIODevice::ReadOnly)){
        qDebug()<<"File opened.";

        QStringList subCategories1;

        QString jFileString = (QString)jFile.readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(jFileString.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonCategories = jsonObject["categories"].toArray();

        foreach (const QJsonValue & value, jsonCategories ) {
            QJsonObject obj = value.toObject();
            QJsonArray jsonSubCategories= obj["subcategories"].toArray();

            QString temp=ui->comboBox_1->currentText();
            foreach (const QJsonValue & value, jsonSubCategories) {
                QJsonObject obj = value.toObject();

                if(QString::compare(temp,((QString)obj["cat_id"].toString()).mid(0,temp.length()),
                                    Qt::CaseSensitive)==0){
                    subCategories1<<(QString)obj["cat_id"].toString();
                }
            }
        }
        ui->comboBox_2->addItems(subCategories1);
    }else{
        qDebug()<<"File can not open.";
    }
}

void MainWindow::mySlotComboBox2(){

    ui->comboBox_3->clear();

    QFile jFile(jFilePath);
    if(jFile.open(QIODevice::ReadOnly)){
        qDebug()<<"File opened.";

        QStringList subCategories1;

        QString jFileString = (QString)jFile.readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(jFileString.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonCategories = jsonObject["categories"].toArray();

        foreach (const QJsonValue & value, jsonCategories ) {
            QJsonObject obj = value.toObject();
            QJsonArray jsonSubCategories= obj["subcategories"].toArray();

            QString temp=ui->comboBox_2->currentText();
            foreach (const QJsonValue & value, jsonSubCategories) {
                QJsonObject obj = value.toObject();
                QJsonArray jsonSubCategories= obj["subcategories"].toArray();

                foreach (const QJsonValue & value, jsonSubCategories) {
                    QJsonObject obj = value.toObject();

                    if(QString::compare(temp,((QString)obj["cat_id"].toString()).mid(0,temp.length()),
                                        Qt::CaseSensitive)==0){
                        subCategories1<<(QString)obj["cat_id"].toString();
                    }
                }
            }
        }
        ui->comboBox_3->addItems(subCategories1);
    }else{
        qDebug()<<"File can not open.";
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        jFilePath = url.toLocalFile();
        qDebug() << "Dropped file:" << jFilePath;
        mySlotJsonParse();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
