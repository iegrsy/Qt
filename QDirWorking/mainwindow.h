#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QString>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void listele(QListWidget *lw,QString &url, QStringList &myList);
    void yolYolla(QListWidget* lw, QString &url, QStringList &list );

private:
    Ui::MainWindow *ui;
    QString dirPath1,dirPath2;
    QStringList dirList1,dirList2;
    QStringList dl1,dl2,dl;

public slots:
    void karsilastirDir();
    void btnPress();

};

#endif // MAINWINDOW_H
