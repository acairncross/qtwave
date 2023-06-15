#include "mainwindow.h"
#include "wavescene.h"

#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new WaveScene(this);
    scene->setSceneRect(QRectF(0, 0, 800, 400));

    view = new QGraphicsView(scene);

    setCentralWidget(view);
    setWindowTitle(tr("QtWave"));
}

MainWindow::~MainWindow()
{
}
