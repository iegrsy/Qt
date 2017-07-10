#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QModelIndexList>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QTreeView>
#include <QDebug>
#include <QList>
#include <QColor>
#include <QIcon>
#include <QStringList>


#include <QJsonParseError>
#include <QDragEnterEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(myBtnSlot()));

    ui->treeWidget->setHeaderLabel("Categories");

    QString jFilePath="C:\\Users\\ibrahimethem\\Desktop\\cats.json";
    QFile jFile(jFilePath);
    if(jFile.open(QIODevice::ReadOnly)){
        jFileParse(QString(jFile.readAll()));

        currentPageMap();
    }else{
        qDebug()<<"File can not open.";
    }
}

void MainWindow::jFileParse(QString jFile){
    if(!jFile.isEmpty()){

        QJsonDocument jDoc = QJsonDocument::fromJson(jFile.toUtf8());
        QJsonObject jObject = jDoc.object();
        QJsonArray jArray =jObject["categories"].toArray();
        QTreeWidgetItem *categories;

        foreach (const QJsonValue & value, jArray) {
            QJsonObject obj=value.toObject();

            if(!obj["name"].toString().isEmpty()){
                categories =new QTreeWidgetItem(ui->treeWidget);
                categories->setText(0,obj["name"].toString());
                categories->setCheckState(0, Qt::Unchecked);
            }
            if(!obj["subcategories"].toArray().isEmpty()){
                QJsonArray jArray=obj["subcategories"].toArray();

                foreach (const QJsonValue & value, jArray) {
                    QJsonObject obj=value.toObject();
                    QTreeWidgetItem *subcategories;

                    if(!obj["name"].toString().isEmpty()){
                        subcategories =new QTreeWidgetItem(categories);
                        subcategories->setText(0,obj["name"].toString());
                        subcategories->setCheckState(0, Qt::Unchecked);
                    }

                    if(!obj["subcategories"].toArray().isEmpty()){
                        QJsonArray jArray=obj["subcategories"].toArray();

                        foreach (const QJsonValue & value, jArray) {
                            QJsonObject obj=value.toObject();

                            if(!obj["name"].toString().isEmpty()){
                                QTreeWidgetItem *subcategories1 =new QTreeWidgetItem(subcategories);
                                subcategories1->setText(0,obj["name"].toString());
                                subcategories1->setCheckState(0, Qt::Unchecked);
                            }
                        }
                    }
                }
            }
        }


    }else{
        qDebug()<<"Json file error.";
    }
}

QMap<QString, QString> MainWindow::currentPageMap()
{
    QMap<QString, QString> pageMap;
    QStringList checkItemList;

    for (int row = 0; row < ui->treeWidget->topLevelItemCount(); ++row) {
        QTreeWidgetItem *checkItem = ui->treeWidget->topLevelItem(row);

        if (checkItem->checkState(0) == Qt::Checked) {
            qDebug()<<checkItem->text(0);
            checkItemList<<checkItem->text(0);
        }

        for (int childRow = 0; childRow < checkItem->childCount(); ++childRow) {
            QTreeWidgetItem *subCheckItem = checkItem->child(childRow);
            if (subCheckItem->checkState(0) == Qt::Checked){
                qDebug()<<subCheckItem->text(0);
                checkItemList<<subCheckItem->text(0);
            }

            for (int childRow = 0; childRow < subCheckItem->childCount(); ++childRow) {
                QTreeWidgetItem *subCheckItem1 = subCheckItem->child(childRow);
                if (subCheckItem1->checkState(0) == Qt::Checked){
                    qDebug()<<subCheckItem1->text(0);
                    checkItemList<<subCheckItem1->text(0);
                }
            }
        }
    }
    ui->listWidget->clear();
    ui->listWidget->addItems(checkItemList);
    return pageMap;
}

void MainWindow::myBtnSlot(){
    currentPageMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}
