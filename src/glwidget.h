#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include "dataobject.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize sizeHint() const;

signals:

public slots:

public:
    void setData(DataObject* iData);

protected:
    void initializeGL();
    void paintEvent(QPaintEvent *event);

    virtual void processData();
    virtual void drawNativeGL();
    virtual void drawQtPainter(QPainter *painter);

private:
    void beginNativeGL();
    void endNativeGL();

protected:
    DataObject *data;
    bool processed;

    int margin;
    QColor bgColor;
};

#endif // GLWIDGET_H
