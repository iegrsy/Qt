#include <QCoreApplication>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>

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

static void karsilastir(QStringList files1,QStringList files2,QStringList &file1file2,QStringList &file2file1,QStringList &file )
{
    //    foreach (QString s, files1) {
    //        qDebug()<<"1.file:"<<s;
    //    }
    //    foreach (QString s, files2) {
    //        qDebug()<<"2.file"<<s;
    //    }

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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString fPath1="/home/ieg/Masaüstü/ieggit/MenuExample";
    QString fPath2="/home/ieg/Masaüstü/ieggit/opencv";

    QStringList files1,files2;

    listFiles(fPath1,files1);
    listFiles(fPath2,files2);

    foreach (QString d, files1) {
        qDebug()<<"1."<<d;
    }

    foreach (QString d, files2) {
        qDebug()<<"2."<<d;
    }

    QStringList lr,rl,eq;
    karsilastir(files1,files2,lr,rl,eq);

    qDebug()<<"sol sag karsilastirma:";
    foreach (QString d, lr) {
        qDebug()<<d;
    }
    qDebug()<<"sag sol karsilastirma::";
    foreach (QString d, rl) {
        qDebug()<<d;
    }
    qDebug()<<"esit olanlar:";
    foreach (QString d, eq) {
        qDebug()<<d;
    }

    //    return a.exec();
}

