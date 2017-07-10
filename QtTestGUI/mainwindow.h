#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndexList>
#include <QTreeWidgetItem>
#include <QList>
#include <QIcon>
#include <QPixmap>


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
    QStringList testControl(QString testID, QMap<int, QMap<QString, QString> > testMap);


public slots:

    void myBtnSlot();
    void updateChecks(QTreeWidgetItem *item, int column);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
