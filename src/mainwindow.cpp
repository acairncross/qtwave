#include "mainwindow.h"

#include "freezetablewidget.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();

    model = new QStandardItemModel(this);
    tableView = new FreezeTableWidget(model);

    setCentralWidget(tableView);
    setWindowTitle(tr("QtWave"));
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    openFileAction = new QAction(QIcon::fromTheme("document-open"), tr("&Open"), this);
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open VCD file", QString(),
                                                    "VCD files (*.vcd);;All files (*)");

    if (fileName.isEmpty()) return;

    setWindowTitle(fileName);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openFileAction);
}
