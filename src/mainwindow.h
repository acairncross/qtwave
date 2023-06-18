#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class FreezeTableWidget;
class QStandardItemModel;

QT_BEGIN_NAMESPACE
class QGraphicsView;
QT_END_NAMESPACE

class VcdParser;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();

private:
    void createActions();
    void createMenus();

    QStandardItemModel *model;
    FreezeTableWidget *tableView;

    QAction *openFileAction;

    QMenu *fileMenu;

    VcdParser *vcdParser;
};
#endif // MAINWINDOW_H
