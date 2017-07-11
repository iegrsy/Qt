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


    QString jFilePath="C:\\Users\\ibrahimethem\\Desktop\\cats.json";
    QFile jFile(jFilePath);
    if(!jFile.open(QIODevice::ReadOnly)){

        return;
    }
    QString data = jFile.readAll().data();

    jsonParseFonk(data);
    currentPageMap();
    jFile.close();
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

        int iterCount=0;
        foreach (const QJsonValue & value, jTestsArray) {
            QJsonObject obj=value.toObject();
            QMap<QString,QString> a;
            a.insert(obj["cat_id"].toString(),obj["name"].toString());
            testMultimap.insert(iterCount,a); iterCount++;

            //qDebug()<<"mapping: "<<obj["cat_id"].toString()<<"--"<<obj["name"].toString();
        }

        QMapIterator<int, QMap<QString,QString>> iter(testMultimap);
        while(iter.hasNext())
        {
            iter.next();
            QMapIterator<QString,QString> iter1(iter.value());
            iter1.next();
            //            qDebug() <<"map: "<< iter.key() <<" : "<<iter1.key()<< " : " << iter1.value();
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
                        tests->setCheckState(0, Qt::Unchecked);
                        //                        tests->setBackground(0,colorRed);
                    }

                }

                if(obj["obligation"].toString().compare("compulsory")){
                    categories->setIcon(0,QIcon(":/zorunlu.png"));
                    categories->setCheckState(0, Qt::Unchecked);
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
                                tests->setCheckState(0, Qt::Unchecked);
                                //                                tests->setBackground(0,colorRed);

                            }
                        }


                        if(obj["obligation"].toString().compare("compulsory")){
                            subcategories->setIcon(0,QIcon(":/zorunlu.png"));
                            subcategories->setCheckState(0, Qt::Unchecked);
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
                                        tests->setCheckState(0, Qt::Unchecked);
                                        //                                        tests->setBackground(0,colorRed);
                                    }
                                }

                                if(obj["obligation"].toString().compare("compulsory")){
                                    subcategories1->setIcon(0,QIcon(":/zorunlu.png"));
                                    subcategories1->setCheckState(0, Qt::Unchecked);
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

bool MainWindow::testControl1(QString testName,QMap<int,QMap<QString,QString>> testMap){

    bool result=false;

    QMapIterator<int, QMap<QString,QString>> iter(testMap);
    while(iter.hasNext())
    {
        iter.next();
        QMapIterator<QString,QString> iter1(iter.value());
        iter1.next();

        if(testName.compare(iter1.value())==0){
            result =true;
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
            if(testControl1(checkItem->text(0),testMultimap))
                checkItemList<<checkItem->text(0);
        }

        for (int childRow = 0; childRow < checkItem->childCount(); ++childRow) {
            QTreeWidgetItem *subCheckItem = checkItem->child(childRow);
            if (subCheckItem->checkState(0) == Qt::Checked){
                //                qDebug()<<subCheckItem->text(0);
                if(testControl1(subCheckItem->text(0),testMultimap))
                    checkItemList<<subCheckItem->text(0);
            }

            for (int childRow = 0; childRow < subCheckItem->childCount(); ++childRow) {
                QTreeWidgetItem *subCheckItem1 = subCheckItem->child(childRow);
                if (subCheckItem1->checkState(0) == Qt::Checked){
                    //                    qDebug()<<subCheckItem1->text(0);
                    if(testControl1(subCheckItem1->text(0),testMultimap))
                        checkItemList<<subCheckItem1->text(0);
                }
                for (int childRow = 0; childRow < subCheckItem1->childCount(); ++childRow) {
                    QTreeWidgetItem *subCheckItem2 = subCheckItem1->child(childRow);
                    if (subCheckItem2->checkState(0) == Qt::Checked){
                        //                    qDebug()<<subCheckItem2->text(0);
                        if(testControl1(subCheckItem2->text(0),testMultimap))
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

void MainWindow::jsonParseFonk(QString data){

    QJsonDocument jDoc= QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jObj = jDoc.object();
    QStringList jObjKeys = jObj.keys();
    qDebug()<<"file keys: "<<jObjKeys;
    //    qDebug()<<jObj[jObjKeys[0]].type();
    QTreeWidgetItem *categories;
    QMap<QString, QString> categoriList;
    QMap<int,QMap<QString,QString>> testsList;

    //    QJsonArray array = jObj[jObjKeys[1]].toArray();
    QJsonArray arrayTests = jObj["tests"].toArray();
    for(int i=0;i<arrayTests.count();i++){
        //        qDebug()<<arrayTests.at(i).type();
        QJsonObject obj=arrayTests[i].toObject();
        //        qDebug()<<QString("tests[%1]: ").arg(i)<<obj.keys();
        QStringList objKeys = obj.keys();
        foreach (QString s, objKeys) {
            //            qDebug()<<obj[s].type();
            if(obj[s].isString()){
                //                                qDebug()<<QString("%1 : ").arg(s)<<obj[s].toString();
                QMap<QString,QString> temp;
                temp.insert(obj["cat_id"].toString(),obj["name"].toString());
                testsList.insert(i,temp);
            }
            if(obj[s].isObject()){
                QJsonObject obj1 = obj[s].toObject();
                //                                qDebug()<<QString("%1 : ").arg(s)<<obj1.keys();
                //                QStringList obj1Keys = obj1.keys();

                //                foreach (QString s, obj1Keys) {
                //                    qDebug()<<obj1[s].type();
                //                    qDebug()<<QString("%1 : ").arg(s)<<obj1[s].toString();
                //                }
            }
        }
    }

    //    QMapIterator<int, QMap<QString,QString>> iter(testsList);
    //    while(iter.hasNext())
    //    {
    //        iter.next();
    //        QMapIterator<QString,QString> iter1(iter.value());
    //        iter1.next();
    //        qDebug() <<"map: "<< iter.key() <<" : "<<iter1.key()<< " : " << iter1.value();
    //    }

    QJsonArray arrayCategories = jObj[jObjKeys[0]].toArray();
    //    qDebug()<<arrayCategories.count();
    for(int i=0;i<arrayCategories.count();i++){
        //        qDebug()<<arrayCategories.at(i);
        if(arrayCategories.at(i).isObject()){
            QJsonObject obj = arrayCategories.at(i).toObject();
            QStringList objKeys = obj.keys();
            //            qDebug()<<objKeys;
            categoriList.insert(obj["cat_id"].toString(),obj["name"].toString());
            categories =  new QTreeWidgetItem(ui->treeWidget);
            categories->setText(0,obj["name"].toString());
            categories->setCheckState(0, Qt::Unchecked);

            QStringList s= testControl(obj["cat_id"].toString(),testsList);
            if(!s.isEmpty()){
                foreach (QString a, s) {
                    QTreeWidgetItem *tests =new QTreeWidgetItem(categories);
                    tests->setText(0,a);
                    tests->setIcon(0,QIcon(":/testler.png"));
                    tests->setCheckState(0, Qt::Unchecked);
                    //                        tests->setBackground(0,colorRed);
                }

            }

            QTreeWidgetItem *categories1;

            foreach (QString s, objKeys) {
                //                qDebug()<<obj[s].type();
                if(obj[s].isString()){
                    //                    qDebug()<<s<<"--"<<obj[s].toString();
                }
                if(obj[s].isArray()){
                    //                    qDebug()<<obj[s];
                    QJsonArray array = obj[s].toArray();
                    for(int i=0;i<array.count();i++){
                        //                        qDebug()<<array.at(i).type();
                        if(array.at(i).isObject()){
                            QJsonObject obj = array.at(i).toObject();
                            QStringList objKeys = obj.keys();
                            //                            qDebug()<<s<<"--"<<obj.keys();
                            categoriList.insert(obj["cat_id"].toString(),obj["name"].toString());
                            categories1=  new QTreeWidgetItem(categories);
                            categories1->setText(0,obj["name"].toString());
                            categories1->setCheckState(0, Qt::Unchecked);

                            QStringList s= testControl(obj["cat_id"].toString(),testsList);
                            if(!s.isEmpty()){
                                foreach (QString a, s) {
                                    QTreeWidgetItem *tests =new QTreeWidgetItem(categories1);
                                    tests->setText(0,a);
                                    tests->setIcon(0,QIcon(":/testler.png"));
                                    tests->setCheckState(0, Qt::Unchecked);
                                    //                        tests->setBackground(0,colorRed);
                                }

                            }

                            QTreeWidgetItem *categories2;
                            foreach (QString s, objKeys) {
                                //                                qDebug()<<obj[s].type();
                                if(obj[s].isString()){
                                    //                                    qDebug()<<obj[s].toString();
                                }
                                if(obj[s].isArray()){
                                    QJsonArray array = obj[s].toArray();
                                    for(int i=0;i<array.count();i++){
                                        //                                                                                qDebug()<<array.at(i).type();
                                        QJsonObject obj = array.at(i).toObject();
                                        QStringList objKeys = obj.keys();
                                        //                                        qDebug()<<obj.keys();
                                        categoriList.insert(obj["cat_id"].toString(),obj["name"].toString());
                                        categories2=  new QTreeWidgetItem(categories1);
                                        categories2->setText(0,obj["name"].toString());
                                        categories2->setCheckState(0, Qt::Unchecked);

                                        QStringList s= testControl(obj["cat_id"].toString(),testsList);
                                        if(!s.isEmpty()){
                                            foreach (QString a, s) {
                                                QTreeWidgetItem *tests =new QTreeWidgetItem(categories2);
                                                tests->setText(0,a);
                                                tests->setIcon(0,QIcon(":/testler.png"));
                                                tests->setCheckState(0, Qt::Unchecked);
                                                //                        tests->setBackground(0,colorRed);
                                            }
                                        }
                                        foreach (QString s, objKeys) {
                                            //                                            qDebug()<< obj[s].type();
                                            if(obj[s].isString()){
                                                //                                                qDebug()<<obj[s].toString();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

//    QMapIterator<QString,QString> iter(categoriList);
//    while(iter.hasNext())
//    {
//        iter.next();
//        qDebug() <<"map: "<< iter.key() <<" : " << iter.value();
//    }

    testMultimap=testsList;
}


