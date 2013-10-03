#include "glwidget.h"

#include <iostream>
using namespace std;

#include <QElapsedTimer>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    setAutoFillBackground(false);
    setMinimumSize(200, 200);
    setWindowTitle(tr("Viz"));

    margin = 20;
    bgColor = Qt::lightGray;
    processed = false;
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}


void GLWidget::initializeGL()
{
    glEnable(GL_MULTISAMPLE);
    glDisable(GL_DEPTH);
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QElapsedTimer frameTimer;
    qint64 frameElapsed;

    frameTimer.start();

    // Clear
    qglClearColor(bgColor);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw native GL
    beginNativeGL();
    {
        drawNativeGL();
    }
    endNativeGL();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawQtPainter(&painter);
    painter.end();

    frameElapsed = frameTimer.nsecsElapsed();
    double seconds = (double)frameElapsed * 1e-9;
    double fps = 1.0 / seconds;

    cout << "fps: " << fps << endl;
}

void GLWidget::setData(DataObject *iData)
{
    data = iData;
    processData();
}

void GLWidget::processData()
{

}

void GLWidget::drawNativeGL()
{
    glPointSize(50.0);
    glBegin(GL_POINTS);
    {
        glColor4f(1,0,0,1);
        glVertex2i(width()/2,height()/2);
    }
    glEnd();
}

void GLWidget::drawQtPainter(QPainter *painter)
{
    painter->drawPoint(width()/2,height()/2);
}

void GLWidget::beginNativeGL()
{
    makeCurrent();

    // Why do i need to double these?
    // I really don't know.
    int width2x = width()*2;
    int height2x = height()*2;

    // Set settings for native gl
    glViewport(0, 0, width2x, height2x);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
}

void GLWidget::endNativeGL()
{
    // Revert settings for painter
    glShadeModel(GL_FLAT);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

