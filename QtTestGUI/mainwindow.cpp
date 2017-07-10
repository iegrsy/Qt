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
    connect(ui->treeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(updateChecks(QTreeWidgetItem*,int)));
    ui->treeWidget->setHeaderLabel("Categories");


    QString jFilePath="C:\\Users\\ibrahimethem\\Desktop\\testdefs.json";
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
        QJsonArray jCategoriesArray =jObject["categories"].toArray();
        QJsonArray jTestsArray =jObject["tests"].toArray();

        QTreeWidgetItem *categories;
//        QBrush colorYellow( Qt::yellow );
//        QBrush colorGreen( Qt::green );
//        QBrush colorWhite(Qt::white);
//        QBrush colorRed(Qt::red);

        //Tests mapping
        QMap< int, QMap< QString, QString> > testMultimap;
        int iterCount=0;
        foreach (const QJsonValue & value, jTestsArray) {
            QJsonObject obj=value.toObject();
            QMap<QString,QString> a;
            a.insert(obj["cat_id"].toString(),obj["name"].toString());
            testMultimap.insert(iterCount,a); iterCount++;

            //            qDebug()<<"mapping: "<<obj["cat_id"].toString()<<"--"<<obj["name"].toString();
        }

        QMapIterator<int, QMap<QString,QString>> iter(testMultimap);
        while(iter.hasNext())
        {
            iter.next();
            QMapIterator<QString,QString> iter1(iter.value());
            iter1.next();
            qDebug() <<"map: "<< iter.key() <<" : "<<iter1.key()<< " : " << iter1.value();
        }


        //Json parse
        foreach (const QJsonValue & value, jCategoriesArray) {
            QJsonObject obj=value.toObject();

            if(!obj["name"].toString().isEmpty()){
                categories =new QTreeWidgetItem(ui->treeWidget);
                categories->setText(0,obj["name"].toString());

                QStringList s= testControl(obj["cat_id"].toString(),testMultimap);
                if(!s.isEmpty()){
                    foreach (QString a, s) {
                        QTreeWidgetItem *tests =new QTreeWidgetItem(categories);
                        tests->setText(0,a);
                        tests->setIcon(0,QIcon(":/testler.png"));
                        tests->setCheckState(0, Qt::Checked);
//                        tests->setBackground(0,colorRed);
                    }

                }

                if(obj["obligation"].toString().compare("compulsory")){
                    categories->setIcon(0,QIcon(":/zorunlu.png"));
                    categories->setCheckState(0, Qt::Checked);
//                    categories->setBackground(0,colorGreen);
                }else if(obj["obligation"].toString().compare("optional")) {
                    categories->setIcon(0,QIcon(":/secmeli.png"));
                    categories->setCheckState(0, Qt::Unchecked);
//                    categories->setBackground(0,colorYellow);
                }else{
//                    categories->setBackground(0,colorWhite);
                }
            }
            if(!obj["subcategories"].toArray().isEmpty()){
                QJsonArray jArray=obj["subcategories"].toArray();

                foreach (const QJsonValue & value, jArray) {
                    QJsonObject obj=value.toObject();
                    QTreeWidgetItem *subcategories;

                    if(!obj["name"].toString().isEmpty()){
                        subcategories =new QTreeWidgetItem(categories);
                        subcategories->setText(0,obj["name"].toString());

                        QStringList s= testControl(obj["cat_id"].toString(),testMultimap);
                        if(!s.isEmpty()){
                            foreach (QString a, s) {
                                QTreeWidgetItem *tests =new QTreeWidgetItem(subcategories);
                                tests->setText(0,a);
                                tests->setIcon(0,QIcon(":/testler.png"));
                                tests->setCheckState(0, Qt::Checked);
//                                tests->setBackground(0,colorRed);

                            }
                        }


                        if(obj["obligation"].toString().compare("compulsory")){
                            subcategories->setIcon(0,QIcon(":/zorunlu.png"));
                            subcategories->setCheckState(0, Qt::Checked);
//                            subcategories->setBackground(0,colorGreen);

                        }else if(obj["obligation"].toString().compare("optional")) {
                            subcategories->setIcon(0,QIcon(":/secmeli.png"));
                            subcategories->setCheckState(0, Qt::Unchecked);
//                            subcategories->setBackground(0,colorYellow);
                        }else{
//                            subcategories->setBackground(0,colorWhite);
                        }
                    }
                    if(!obj["subcategories"].toArray().isEmpty()){
                        QJsonArray jArray=obj["subcategories"].toArray();
                        QTreeWidgetItem *subcategories1;

                        foreach (const QJsonValue & value, jArray) {
                            QJsonObject obj=value.toObject();

                            if(!obj["name"].toString().isEmpty()){
                                subcategories1 =new QTreeWidgetItem(subcategories);
                                subcategories1->setText(0,obj["name"].toString());

                                QStringList s= testControl(obj["cat_id"].toString(),testMultimap);
                                if(!s.isEmpty()){
                                    foreach (QString a, s) {
                                        QTreeWidgetItem *tests =new QTreeWidgetItem(subcategories1);
                                        tests->setText(0,a);
                                        tests->setIcon(0,QIcon(":/testler.png"));
                                        tests->setCheckState(0, Qt::Checked);
//                                        tests->setBackground(0,colorRed);
                                    }
                                }

                                if(obj["obligation"].toString().compare("compulsory")){
                                    subcategories1->setIcon(0,QIcon(":/zorunlu.png"));
                                    subcategories1->setCheckState(0, Qt::Checked);
//                                    subcategories1->setBackground(0,colorGreen);

                                }else if(obj["obligation"].toString().compare("optional")) {
                                    subcategories1->setIcon(0,QIcon(":/secmeli.png"));
                                    subcategories1->setCheckState(0, Qt::Unchecked);
//                                    subcategories1->setBackground(0,colorYellow);
                                }else{
//                                    subcategories1->setBackground(0,colorWhite);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        qDebug()<<"Json file error.";
    }
}

QStringList MainWindow::testControl(QString testID,QMap<int,QMap<QString,QString>> testMap){

    QStringList result;

    QMapIterator<int, QMap<QString,QString>> iter(testMap);
    while(iter.hasNext())
    {
        iter.next();
        QMapIterator<QString,QString> iter1(iter.value());
        iter1.next();

        if(testID.compare(iter1.key())==0){
            //            qDebug() <<"sonuc: "<< iter.key() <<" : "<<iter1.key()<< " : " << iter1.value();
            result.append(iter1.value());
        }else{

        }
    }
    return result;
}

QMap<QString, QString> MainWindow::currentPageMap()
{
    QMap<QString, QString> pageMap;
    QStringList checkItemList;

    for (int row = 0; row < ui->treeWidget->topLevelItemCount(); ++row) {
        QTreeWidgetItem *checkItem = ui->treeWidget->topLevelItem(row);

        if (checkItem->checkState(0) == Qt::Checked) {
            //            qDebug()<<checkItem->text(0);
            checkItemList<<checkItem->text(0);
        }

        for (int childRow = 0; childRow < checkItem->childCount(); ++childRow) {
            QTreeWidgetItem *subCheckItem = checkItem->child(childRow);
            if (subCheckItem->checkState(0) == Qt::Checked){
                //                qDebug()<<subCheckItem->text(0);
                checkItemList<<subCheckItem->text(0);
            }

            for (int childRow = 0; childRow < subCheckItem->childCount(); ++childRow) {
                QTreeWidgetItem *subCheckItem1 = subCheckItem->child(childRow);
                if (subCheckItem1->checkState(0) == Qt::Checked){
                    //                    qDebug()<<subCheckItem1->text(0);
                    checkItemList<<subCheckItem1->text(0);
                }
                for (int childRow = 0; childRow < subCheckItem1->childCount(); ++childRow) {
                    QTreeWidgetItem *subCheckItem2 = subCheckItem1->child(childRow);
                    if (subCheckItem2->checkState(0) == Qt::Checked){
                        //                    qDebug()<<subCheckItem2->text(0);
                        checkItemList<<subCheckItem2->text(0);
                    }
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

void MainWindow::updateChecks(QTreeWidgetItem *item, int column)
{
    bool diff = false;
    if(column != 0 && column!=-1)
        return;
    if(item->childCount()!=0 && item->checkState(0)!=Qt::PartiallyChecked && column!=-1){
        Qt::CheckState checkState = item->checkState(0);
        for (int i = 0; i < item->childCount(); ++i) {
            item->child(i)->setCheckState(0, checkState);
        }
    } else if (item->childCount()==0 || column==-1) {
        if(item->parent()==0)
            return;
        for (int j = 0; j < item->parent()->childCount(); ++j) {
            if(j != item->parent()->indexOfChild(item) && item->checkState(0)!=item->parent()->child(j)->checkState(0)){
                diff = true;
            }
        }
        if(diff)
            item->parent()->setCheckState(0,Qt::PartiallyChecked);
        else
            item->parent()->setCheckState(0,item->checkState(0));
        if(item->parent()!=0)
            updateChecks(item->parent(),-1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
