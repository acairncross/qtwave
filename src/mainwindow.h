#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class FreezeTableWidget;
class QAbstractItemModel;

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
    QAbstractItemModel *model;
    FreezeTableWidget *tableView;
};
#endif // MAINWINDOW_H
