#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QString jFilePath="C:\\Users\\ibrahimethem\\Documents\\qtProject\\QtJson\\cats.json";
    QString cboTag1,cboTag2,cboTag3;

    ~MainWindow();

public slots:
    void mySlotJsonParse();
    void mySlotComboBox1();
    void mySlotComboBox2();

    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
