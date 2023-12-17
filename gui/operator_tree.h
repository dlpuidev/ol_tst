#ifndef OPERATOR_TREE_H
#define OPERATOR_TREE_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#include "manager_storage.h"
#include "operator_editor.h"
#include "buttonhoverwatcher.h"

const int COUNTRY_ROLE_MCC = Qt::UserRole + 1;
const int COUNTRY_ROLE_CODE = Qt::UserRole + 2;
const int COUNTRY_ROLE_NAME = Qt::UserRole + 3;
const int COUNTRY_ROLE_LENGTH = Qt::UserRole + 4;

const int OPERATOR_ROLE_MCC = Qt::UserRole + 5;
const int OPERATOR_ROLE_MNC = Qt::UserRole + 6;
const int OPERATOR_ROLE_NAME = Qt::UserRole + 7;

QT_BEGIN_NAMESPACE
class QListView;
class QTreeView;
class QGridLayout;
class QStandardItemModel;
class QItemSelection;
class QStandardItem;
class QMessageBox;
QT_END_NAMESPACE

class OperatorTree : public QWidget
{
    Q_OBJECT

public:
    OperatorTree(ManagerStorage &ptrManagerStorage, QWidget *parent = nullptr);
    ~OperatorTree();

private:
    ManagerStorage &mManagerStorage;

    QStandardItemModel* standardModel;

    QStandardItem* rootNode;
    QStandardItem* parentItem;
    QStandardItem* childItem;

    std::unique_ptr<QTreeView> treeView;
    std::unique_ptr<OperatorEditor> ptrOperatorEditor;
    std::unique_ptr<ButtonHoverWatcher> ptrEditButton;

private:
    void generateTree(void);
    QStandardItem* findCountryItemByMCC(const QString& mcc);
    QStandardItem* findOperatorItemByMCCAndMNC(const QString& mcc, const QString& mnc);

public slots:
    void slotInsert(OperatorStorage& storage);
    void slotUpdate(OperatorStorage& storage);

private slots:
    void slotEditButton();
    void slotdoubleClicked(const QModelIndex &index);
};
#endif // OPERATOR_TREE_H
