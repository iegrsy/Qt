#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void listele1();
    void listele2();

private:
    Ui::MainWindow *ui;
    QString dirPath1,dirPath2;
    QStringList dirList1,dirList2;
    QStringList dl1,dl2,dl;

public slots:
    void yolYolla1();
    void yolYolla2();
    void karsilastirDir();
};

#endif // MAINWINDOW_H
