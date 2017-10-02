#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QUrl>
#include <QMainWindow>
#include <QNetworkReply>
#include <QList>

namespace Ui {
class MainWindow;
}

struct doviz {
    QString name;
    QString value;
    QString nameID;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QList<doviz> dovizList;

    QUrl url;
    QString filePath="/home/ieg/Masaüstü/ieggit/Qt/QtXmlWorkingtoday.xml";

    void writeFile(QString path,QString text);
    void parseXml();

    void listele();
private:
    Ui::MainWindow *ui;

public slots:
    void pageConnect();
    void htmlRead();
    void updateProgress(qint64 bytesReceived, qint64 bytesTotal);

    void mySlot();
};

#endif // MAINWINDOW_H
