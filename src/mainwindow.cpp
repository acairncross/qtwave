#include "mainwindow.h"

#include "freezetablewidget.h"
#include "vcdparser.h"
#include "waveformdelegate.h"
#include "waveformitem.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QStandardItemModel>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();

    model = new QStandardItemModel(this);
    tableView = new FreezeTableWidget(model);

    tableView->setItemDelegate(new WaveformDelegate);

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

    VcdParser vcdParser(&stream);
    VcdHeader vcdHeader;
    vcdParser.parseHeader(&vcdHeader);

    QMap<QString, Waveform> vcdBody;
    vcdParser.parseBody(&vcdBody);

    // Note: The model takes ownership of the item when calling setItem

    int ctr = 0;
    for (auto i = vcdBody.cbegin(); i != vcdBody.cend(); i++) {
        QString name = i.key();
        Waveform waveform = i.value();
        model->setItem(ctr, 0, new QStandardItem(name));
        model->setItem(ctr, 1, new WaveformItem(waveform));
        ctr += 1;
    }

//    model->setItem(0, 0, new QStandardItem(QString("date")));
//    model->setItem(1, 0, new QStandardItem(QString("version")));
//    model->setItem(2, 0, new QStandardItem(QString("timescale")));

//    auto dateItem = new QStandardItem(vcdHeader.date);
//    model->setItem(0, 1, dateItem);

//    auto versionItem = new QStandardItem(vcdHeader.version);
//    model->setItem(1, 1, versionItem);

//    auto timescaleItem = new QStandardItem(QString("%1 %2")
//                                               .arg(vcdHeader.timescaleNumber)
//                                               .arg(static_cast<int>(vcdHeader.timescaleUnit)));
//    model->setItem(2, 1, timescaleItem);

//    model->setItem(4, 4, new WaveformItem(vcdBody["*$"]));

    setWindowTitle(fileName);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openFileAction);
}
