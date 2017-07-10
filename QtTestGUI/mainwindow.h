#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndexList>
#include <QTreeWidgetItem>
#include <QList>

typedef QList<QTreeWidgetItem *> StyleItems;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void jFileParse(QString jFile);
    QMap<QString, QString> currentPageMap();
public slots:

    void myBtnSlot();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
