#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "operator_tree.h"
#include "manager_storage.h"

#include <memory>

QT_BEGIN_NAMESPACE
class QGridLayout;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::unique_ptr<OperatorTree> ptrOperatorTree;
    ManagerStorage  mManagerStorage;

};
#endif // MAINWINDOW_H

