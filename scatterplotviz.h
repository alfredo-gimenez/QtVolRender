#ifndef SCATTERPLOTVIZ_H
#define SCATTERPLOTVIZ_H

#include <QVector2D>

#include "glwidget.h"

class ScatterPlotViz : public GLWidget
{
    Q_OBJECT

public:
    ScatterPlotViz(QWidget *parent = 0);

signals:

public slots:
    void setDims(int x, int y);

protected:
    void processData();
    void drawNativeGL();
    void drawQtPainter(QPainter *painter);

private:
    long long xdim;
    long long ydim;

    qreal xMin;
    qreal xMax;
    qreal yMin;
    qreal yMax;

    QVector<QPointF> points;
    QVector<GLfloat> renderPoints;

    QRectF plotBBox;
};

#endif // SCATTERPLOTVIZ_H
