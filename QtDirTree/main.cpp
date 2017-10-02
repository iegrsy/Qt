#include <QCoreApplication>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>

void klasorAc(QString s)
{
    if(!s.isEmpty())
    {
        QStringList myFilePath;

        QDir myDir;
        myDir.setPath(s);

        QStringList fileList=myDir.entryList();
        QString st=s;
        for(int i=2;i<fileList.length();i++)
        {
            //            qDebug()<<fileList[i];

            QFileInfo fileInfo(QString("%1\\%2").arg(s).arg(fileList[i]));
            if(fileInfo.isDir())
            {
                //                qDebug()<<"klasor: "<<fileInfo.path();
                klasorAc(QString("%1\\%2").arg(s).arg(fileList[i]));
                //                qDebug()<<"klasor ac: "<<QString("%1\\%2").arg(s).arg(fileList[i]);
            }

            if(fileInfo.isFile())
            {
                qDebug()<<"dosya: "<<fileList[i];
            }

        }

    }
    else
    {
        qDebug()<<"Dosya yolu bulunamadi.";
        return;
    }
}

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

bool dosyaKontrol(QString fName1,qint64 fSize1 , QString fName2,qint64 fSize2)
{
    if(fName1.compare(fName2)==0 && (fSize1==fSize2) )
    {
        return true;
    }
    else
    {
        return false;
    }

}

void dosyaCompare(QString fPath1, QString fPath2)
{
    QStringList fList1, fList2;
    QStringList fileNameList1,fileNameList2;
    QVector<qint64> fileSizeList1,fileSizeList2;

    listFiles(fPath1,fList1);
    listFiles(fPath2,fList2);

    foreach (const QString &d, fList1)
    {
        QFile f(d);
        QFileInfo fileInfo(f.fileName());
        QString filename(fileInfo.fileName());

        fileNameList1<<filename;
        fileSizeList1.push_back(fileInfo.size());

//        qDebug()<<"1."<<d<<"--"<<filename<<"--"<<fileInfo.size();
    }

    foreach (const QString &d, fList2)
    {
        QFile f(d);
        QFileInfo fileInfo(f.fileName());
        QString filename(fileInfo.fileName());

        fileNameList2<<filename;
        fileSizeList2.push_back(fileInfo.size());

//        qDebug()<<"2."<<d<<"--"<<filename<<"--"<<fileInfo.size();
    }

    for(int i=0;i<fList1.length();i++)
    {
        for(int j=0;j<fList2.length();j++)
        {
            if(dosyaKontrol(fileNameList1[i],fileSizeList1[i],fileNameList2[j],fileSizeList2[j]))
            {
                qDebug()<<fList1[i]<<"==="<<fList2[j];
            }
        }
    }

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    C:\Users\ibrahimethem\Documents\qtProject\QtDirTree

    QString fPath1="/home/ieg/Masaüstü/ieggit";
    QString fPath2="/home/ieg/Masaüstü/ieggit/opencv";

    dosyaCompare(fPath1,fPath2);


    //    return a.exec();
}

