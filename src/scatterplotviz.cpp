#include "scatterplotviz.h"

#include <QPaintEvent>

#include <iostream>
#include <cmath>
using namespace std;

#include "util.h"

ScatterPlotViz::ScatterPlotViz(QWidget *parent)
    : GLWidget(parent)
{
    xdim = 0;
    ydim = 1;
}

void ScatterPlotViz::processData()
{
    renderPoints.clear();

    xMin = *(data->begin+xdim);
    xMax = *(data->begin+xdim);
    yMin = *(data->begin+ydim);
    yMax = *(data->begin+ydim);

    QVector<qreal>::Iterator p;
    qreal x,y;
    for(p=data->begin; p!=data->end; p+=data->numDimensions)
    {
        x = *(p+xdim);
        y = *(p+ydim);

        xMin = min(xMin,x);
        xMax = max(xMax,x);
        yMin = min(yMin,y);
        yMax = max(yMax,y);

        renderPoints.push_back(x);
        renderPoints.push_back(y);
    }

    processed = true;
}

void ScatterPlotViz::drawNativeGL()
{
    if(!processed)
        return;

    glViewport(margin,
               margin,
               width()-2*margin,
               height()-2*margin);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(xMin, xMax, yMax, yMin, 0, 1);

    glPointSize(10.0f);
    glColor4f(1,0,0,1);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2,GL_FLOAT,0,renderPoints.constData());
    glDrawArrays(GL_POINTS,0,renderPoints.size()/2);
}

void ScatterPlotViz::setDims(int x, int y)
{
    xdim = x;
    ydim = y;

    processData();
    repaint();
}

void ScatterPlotViz::drawQtPainter(QPainter *painter)
{
    if(!processed)
        return;

    QRect plotRect = QRect(margin,margin,
                           rect().width()-2*margin,
                           rect().height()-2*margin);

    // Draw axes
    painter->setBrush(QBrush(QColor(0,0,0)));
    painter->drawLine(plotRect.bottomLeft(),plotRect.topLeft());
    painter->drawLine(plotRect.bottomLeft(),plotRect.bottomRight());

    // Draw axis labels
    painter->drawText(plotRect.bottomLeft()+QPointF(0,10),data->meta[xdim]);
    painter->save();
    painter->translate(plotRect.bottomLeft()-QPointF(5,0));
    painter->rotate(270);
    painter->drawText(QPointF(0,0),data->meta[ydim]);
    painter->restore();
}
