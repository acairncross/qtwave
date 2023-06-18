#include "mainwindow.h"

#include "freezetablewidget.h"
#include "vcdparser.h"

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

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream stream(&file);

    vcdParser = new VcdParser(&stream);
    VcdHeader vcdHeader;
    vcdParser->parseHeader(&vcdHeader);

    // Note: The model takes ownership of the item when calling setItem

    model->setItem(0, 0, new QStandardItem(QString("date")));
    model->setItem(1, 0, new QStandardItem(QString("version")));
    model->setItem(2, 0, new QStandardItem(QString("timescale")));

    auto dateItem = new QStandardItem(vcdHeader.date);
    model->setItem(0, 1, dateItem);

    auto versionItem = new QStandardItem(vcdHeader.version);
    model->setItem(1, 1, versionItem);

    auto timescaleItem = new QStandardItem(QString("%1 %2")
                                               .arg(vcdHeader.timescaleNumber)
                                               .arg(static_cast<int>(vcdHeader.timescaleUnit)));
    model->setItem(2, 1, timescaleItem);

    setWindowTitle(fileName);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openFileAction);
}
