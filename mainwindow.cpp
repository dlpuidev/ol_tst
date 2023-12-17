#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mManagerStorage(nullptr)
{
    mManagerStorage.initialize("QSQLITE", QCoreApplication::applicationDirPath() + "/OM system.db");
    ptrOperatorTree = std::make_unique<OperatorTree>(mManagerStorage);

    auto central = new QWidget;
    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->addWidget(ptrOperatorTree.get(),  1, 1, 1, 1);

    central->setLayout(mainLayout);
    setCentralWidget(central);

    setWindowTitle(tr("Test Application"));
    setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{

}
