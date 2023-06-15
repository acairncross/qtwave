#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class WaveScene;

QT_BEGIN_NAMESPACE
class QGraphicsView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    WaveScene *scene;
    QGraphicsView *view;
};
#endif // MAINWINDOW_H
