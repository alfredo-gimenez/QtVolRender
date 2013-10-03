#include <iostream>
using namespace std;

#include <QTimer>
#include <QFileDialog>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scatterplotviz.h"

// Correlation matrix based on selection
// 3D scatterplot using cubes as elements
// Reset parallel coordinates spacing

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

    //for(int i=0; i<vizWidgets.size(); i++)
    //{
    //    connect(vizWidgets[i], SIGNAL(repaintAll()), this, SLOT(repaintAllVizWidgets()));
    //}
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::repaintAllVizWidgets()
{
    for(int i=0; i<vizWidgets.size(); i++)
    {
        vizWidgets[i]->repaint();
    }
}

int MainWindow::importData()
{
    // Open a file using a dialog
    QString dataFileName = QFileDialog::getOpenFileName(this, tr("Import Data"),
                                                     "",
                                                     tr("Files (*.*)"));

    DataObject *dobj = parseCSVFile(dataFileName);
    if(dobj == NULL)
        return -1;

    dataObjects.push_back(dobj);

    for(int i=0; i<vizWidgets.size(); i++)
        vizWidgets[i]->setData(dobj);

    repaintAllVizWidgets();

    return 0;
}

DataObject* MainWindow::parseCSVFile(QString dataFileName)
{
    DataObject *dobj = new DataObject();

    // Open the file
    QFile dataFile(dataFileName);

    if (!dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return NULL;

    // Create text stream
    QTextStream dataStream(&dataFile);
    QString line;
    QStringList lineValues;
    long long elemid = 0;

    // Get metadata from first line
    line = dataStream.readLine();
    dobj->meta = line.split(',');
    dobj->numDimensions = dobj->meta.size();

    // Get data
    while(!dataStream.atEnd())
    {
        line = dataStream.readLine();
        lineValues = line.split(',');

        if(lineValues.size() != dobj->numDimensions)
        {
            cerr << "ERROR: element dimensions do not match metadata!" << endl;
            cerr << "At element " << elemid << endl;
            return NULL;
        }

        for(int i=0; i<lineValues.size(); i++)
        {
            dobj->vals.push_back(lineValues[i].toDouble());
        }

        elemid++;
    }

    // Close and return
    dataFile.close();

    dobj->init();

    return dobj;
}

