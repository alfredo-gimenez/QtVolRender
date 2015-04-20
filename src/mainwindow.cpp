#include <iostream>
using namespace std;

#include <QTimer>
#include <QFileDialog>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_form.h"

#include "scatterplotviz.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Viz"));

    // Create viz widgets
    ScatterPlotViz *scatterPlotViz = new ScatterPlotViz();
    ui->scatterPlotLayout->addWidget(scatterPlotViz);

    // Make UI connections
    // mainwindow
    connect(ui->actionImport_Data, SIGNAL(triggered()),this,SLOT(importData()));

    // Add to viz widgets
    vizWidgets.push_back(scatterPlotViz);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::importData()
{
    // Open a file using a dialog
    QString dataFileName = QFileDialog::getOpenFileName(this, tr("Import Data"),
                                                     "",
                                                     tr("Files (*.*)"));

    return 0;
}
