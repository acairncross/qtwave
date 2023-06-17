#include "mainwindow.h"

#include "freezetablewidget.h"

#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    model = new QStandardItemModel(this);
    tableView = new FreezeTableWidget(model);

    setCentralWidget(tableView);
    setWindowTitle(tr("QtWave"));
}

MainWindow::~MainWindow()
{
}
