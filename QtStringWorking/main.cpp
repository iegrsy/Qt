#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <windows.h>
#include <qtextcodec.h>
#include <QTextCodec>


using namespace std;

void tabloVerileriniSirala(int sutun);
void qstringDenemeleri();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    tabloVerileriniSirala(2);
    qstringDenemeleri();

    return a.exec();
}

void tabloVerileriniSirala(int sutun)
{
    QString fileName="C:\\Users\\ibrahimethem\\Documents\\qtProject\\QStringWorking\\veriler.csv";
    QString yazi;

    QFile qf(fileName);
    if (qf.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        yazi=qf.readAll();
        qf.close();
    }
    else
    {
        cout<<"Dosya okumada hata olustu!!"<<endl;
    }

    //    cout<<yazi.toUtf8().constData()<<endl;

    QStringList listRows;
    listRows = yazi.split('\n');

    int col=sutun;

    QStringList listCols;
    for(int i=0;i<listRows.length()-1;i++)
    {
        listCols=listRows[i].split(';');
        if(!((QString)listCols[col]).isNull() && !((QString)listCols[col]).isEmpty())
        {
            try
            {
                cout<<listCols[col].toUtf8().constData()<<endl;
            }catch(exception e){
                cout<<"Listelerken hata olustu."<<endl;
            }
        }
    }
}

void qstringDenemeleri()
{
    QString testCumle = "Çiftçi ile Padişah Hikayesi. "
                        "Bir varmış, bir yokmuş. Evvel zaman içinde bir gün padişahlar "
                        "padişahı av için şehirden uzaklaşmış. "
                        "Yolda giderken pek çok insanın çalıştığı bir tarla görmüş. "
                        "%1 %2 %3 %4 %5 %6";

    qDebug() << testCumle <<endl;
    qDebug() << testCumle.arg("1.deneme","2.deneme","3.deneme","4.deneme","5.deneme","6.deneme")<<endl;
    //(condition) ? (if_true) : (if_false)
    qDebug() << ((testCumle.contains("ile",Qt::CaseInsensitive)) ? ("içerir."):("içermez."))<<endl;
    qDebug() << testCumle.at(1) <<endl;
    qDebug() << testCumle.begin() <<endl;
    qDebug() << testCumle.replace("ile","ve") <<endl;
    qDebug() << testCumle.insert(28,"..(Burada bir ara verelim.)..") <<endl;
    qDebug() << ((testCumle.isRightToLeft()) ? ("RightToLeft true."):("RightToLeft false.")) <<endl;

    qDebug() << testCumle.length() <<endl;
    qDebug() << testCumle.capacity() <<endl;
    qDebug() << QString("Cümle %1 karakterden oluşur.").arg(testCumle.count()) <<endl;

    qDebug() << testCumle.mid(0,20) <<endl;
    qDebug() << testCumle.prepend("cv ektedir.") <<endl;
    testCumle.push_back("...push_back...");
    testCumle.push_front("...push_front...");
    qDebug() << testCumle <<endl;

    qDebug() << testCumle.remove(0,15) <<endl;
    qDebug() << QString("hey corç").repeated(3) <<endl;

    qDebug()<<testCumle.replace("a","i")<<endl;
}
