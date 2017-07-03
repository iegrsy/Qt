#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QStringListModel>

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

    if(filename1.compare(filename2)==0 && fi1.size()==fi2.size()) {
        return true;
    }else {
        return false;
    }
}

static void karsilastir(QStringList files1,QStringList files2,
                        QStringList &file1file2,QStringList &file2file1,
                        QStringList &file )
{
    bool is=false;
    for(int i=0;i<files1.length();i++){
        for(int j=0;j<files2.length();j++){
            if(fileCompare(files1[i],files2[j])){
                is=true;
            }
        }
        if(!is){
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
            file2file1.push_back(files2[i1]);
        }
        is1=false;
    }

    for(int i1=0;i1<files2.length();i1++){
        for(int j1=0;j1<files1.length();j1++){
            if(fileCompare(files2[i1],files1[j1])){
                file.push_back(files2[i1]);
            }
        }
    }

}

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnDr1,SIGNAL(clicked(bool)),this,SLOT(yolYolla1()));
    connect(ui->btnDr2,SIGNAL(clicked(bool)),this,SLOT(yolYolla2()));
    connect(ui->btnCompare,SIGNAL(clicked(bool)),this,SLOT(karsilastirDir()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listele1(){
    QStringListModel *model = new QStringListModel();

    listFiles(dirPath1, dirList1);
    model->setStringList(dirList1);

    ui->lvDir1->setModel(model);
}

void MainWindow::listele2(){
    QStringListModel *model = new QStringListModel();

    listFiles(dirPath2, dirList2);
    model->setStringList(dirList2);

    ui->lvDir2->setModel(model);
}

void MainWindow::yolYolla1(){
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    dirPath1=fileName;

    listele1();
}

void MainWindow::yolYolla2(){
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    dirPath2=fileName;
    listele2();
}

void MainWindow::karsilastirDir(){
    karsilastir(dirList1,dirList2,dl1,dl2,dl);

    QStringListModel *model1 = new QStringListModel();
    QStringListModel *model2 = new QStringListModel();
    QStringListModel *model3 = new QStringListModel();

    model1->setStringList(dl1);
    ui->lvDirList1->setModel(model1);

    model2->setStringList(dl2);
    ui->lvDirList2->setModel(model2);

    model3->setStringList(dl);
    ui->lvDirList->setModel(model3);
}
