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
                qDebug()<<"klasor: "<<fileInfo.path();
                klasorAc(QString("%1\\%2").arg(s).arg(fileList[i]));
            }

            if(fileInfo.isFile())
                qDebug()<<"dosya: "<<fileList[i];
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString fPath="C:\\Users\\ibrahimethem\\Documents\\qtProject";

    klasorAc(fPath);

    //    return a.exec();
}

