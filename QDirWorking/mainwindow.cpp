#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QStringListModel>
#include <QHash>
#include <QListWidget>

static void listFiles(QString folder, QStringList &list)
{
    QDir dir(folder);

    QStringList files = dir.entryList(QStringList(), QDir::NoDotAndDotDot | QDir::Files);

    foreach (const QString &file, files)
        list << dir.filePath(file);

    files = dir.entryList(QStringList(), QDir::NoDotAndDotDot | QDir::Dirs);

    foreach (const QString &d, files)
        listFiles(dir.filePath(d), list);
}

static bool fileCompare(QString fp1,QString fp2)
{
    QFile f1(fp1),f2(fp2);
    QFileInfo fi1(f1.fileName()),fi2(f2.fileName());
    QString filename1(fi1.fileName()),filename2(fi2.fileName());
    QByteArray file1Bayt,file2Bayt;

    if(f1.open(QIODevice::ReadOnly)){
        file1Bayt=f1.readAll();
    }
    f1.close();
    if(f2.open(QIODevice::ReadOnly)){
        file2Bayt=f2.readAll();
    }
    f2.close();

    if(qHash(file1Bayt)==qHash(file2Bayt)) {
        return true;
    }else {
        return false;
    }
}

static void karsilastir(QStringList files1,QStringList files2,
                        QStringList &file1file2,QStringList &file2file1,
                        QStringList &file )
{
    qDebug()<<"karsilastır.";

    bool is=false;
    for(int i=0;i<files1.length();i++){
        for(int j=0;j<files2.length();j++){
            if(fileCompare(files1[i],files2[j])){
                is=true;
            }
        }
        if(!is){
//            qDebug()<<files1[i]<<"file1file2";
            file1file2.push_back(files1[i]);
        }
        is=false;
    }

    bool is1=false;
    for(int i1=0;i1<files2.length();i1++){
        for(int j1=0;j1<files1.length();j1++){
            if(fileCompare(files2[i1],files1[j1])){
                is1=true;
            }
        }
        if(!is1){
//            qDebug()<<files2[i1]<<"file2file1";
            file2file1.push_back(files2[i1]);
        }
        is1=false;
    }

    for(int i1=0;i1<files2.length();i1++){
        for(int j1=0;j1<files1.length();j1++){
            if(fileCompare(files2[i1],files1[j1])){
//                qDebug()<<files2[i1]<<"file";
                file.push_back(files2[i1]);
            }
        }
    }

}

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnDr1, SIGNAL(clicked(bool)), this, SLOT(btnPress()));

    connect(ui->btnDr2, SIGNAL(clicked(bool)), this, SLOT(btnPress()));

    connect(ui->btnCompare,SIGNAL(clicked(bool)),this,SLOT(karsilastirDir()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listele(QListWidget* lw,QString &url ,QStringList &myList){

    listFiles(url, myList);

    lw->clear();
    lw->addItems(myList);
}

void MainWindow::yolYolla(QListWidget* lw, QString &url, QStringList &list ){
    url = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                            "C:\\Users\\ibrahimethem\\Desktop\\sil",
                                            QFileDialog::ShowDirsOnly
                                            | QFileDialog::DontResolveSymlinks);
    list.clear();
    listele(lw,url,list);
}

void MainWindow::karsilastirDir(){

    dl1.clear();
    dl2.clear();
    dl.clear();

    karsilastir(dirList1,dirList2,dl1,dl2,dl);

    ui->lvDirList1->clear();
    ui->lvDirList1->addItems(dl1);

    ui->lvDirList2->clear();
    ui->lvDirList2->addItems(dl2);

    ui->lvDirList->clear();
    ui->lvDirList->addItems(dl);
}

void MainWindow::btnPress(){

    QObject* obj = sender();
       if( obj == ui->btnDr1 )
       {
          yolYolla(ui->lvDir1, dirPath1, dirList1);
       }
       else if (obj == ui->btnDr2)
       {
           yolYolla(ui->lvDir2, dirPath2, dirList2);
       }
       else
       {
           qDebug()<<"hata btnPress";
       }



}
