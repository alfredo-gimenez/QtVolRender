#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QVector>

#include "glwidget.h"
#include "dataobject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void repaintAllVizWidgets();
    int importData();
    DataObject* parseCSVFile(QString dataFileName);

private:
    Ui::MainWindow *ui;

    QVector<GLWidget*> vizWidgets;
    QVector<DataObject*> dataObjects;
};

#endif // MAINWINDOW_H
