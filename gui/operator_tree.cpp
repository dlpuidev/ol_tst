#include "operator_tree.h"
#include <QtWidgets>
#include <memory>

OperatorTree::OperatorTree(ManagerStorage &ptrManagerStorage, QWidget *parent)
    : mManagerStorage(ptrManagerStorage),
    standardModel(new QStandardItemModel),
    rootNode(standardModel->invisibleRootItem()),
    parentItem(new QStandardItem()),
    childItem(new QStandardItem()),
    treeView(std::make_unique<QTreeView>()),
    ptrOperatorEditor(std::make_unique<OperatorEditor>(mManagerStorage, false)),
    ptrEditButton(std::make_unique<ButtonHoverWatcher>(":/icons/blue_baseline-add-24px.svg", ":/icons/baseline-add-24px.svg"))
{
    QGridLayout *mainLayout = new QGridLayout;
    QHBoxLayout *lay = new QHBoxLayout;

    ptrEditButton->setFixedSize(24,24);
    ptrEditButton->setFlat(true);
    ptrEditButton->setStyleSheet("QPushButton:hover"
                                        "{background-color: #ffffff; border-style: inset; }"
                                        "QPushButton:pressed"
                                        "{background-color: #ffffff; border-style: inset; }");

    ptrEditButton->setIconSize(QSize(24,24));

    generateTree();

    connect(ptrEditButton.get(), &QPushButton::clicked, this, &OperatorTree::slotEditButton);
    connect(treeView.get(), &QTreeView::doubleClicked, this, &OperatorTree::slotdoubleClicked);

    treeView->setHeaderHidden(true);

    standardModel->setHeaderData(0, Qt::Horizontal, "");
    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    treeView->header()->setStretchLastSection(false);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    treeView->setModel(standardModel);

    lay->setContentsMargins(0,0,35,25);
    lay->addWidget(ptrEditButton.get(),1, Qt::AlignRight);

    mainLayout->addWidget(treeView.get(),  1, 1, 1, 1);
    mainLayout->addLayout(lay,  1, 1, 1, 1, Qt::AlignBottom | Qt::AlignRight);

    setLayout(mainLayout);
    setWindowTitle(tr("Application"));

}

OperatorTree::~OperatorTree()
{

}

void OperatorTree::slotEditButton()
{
    ptrOperatorEditor = std::make_unique<OperatorEditor>(mManagerStorage, false);
    connect(ptrOperatorEditor.get(), &OperatorEditor::signalInsert, this, &OperatorTree::slotInsert);
    ptrOperatorEditor->show();
}

void OperatorTree::slotdoubleClicked(const QModelIndex &index)
{
    if(index.parent().isValid())
    {
        mManagerStorage._countryStorage.setMcc(standardModel->data(index.parent(), COUNTRY_ROLE_MCC).toInt());
        mManagerStorage._countryStorage.setCode(standardModel->data(index.parent(), COUNTRY_ROLE_CODE).toString());
        mManagerStorage._countryStorage.setName(standardModel->data(index.parent(), COUNTRY_ROLE_NAME).toString());
        mManagerStorage._countryStorage.setMncLength(standardModel->data(index.parent(), COUNTRY_ROLE_LENGTH).toInt());

        mManagerStorage._operatorStorage.setName(standardModel->data(index, OPERATOR_ROLE_NAME).toString());
        mManagerStorage._operatorStorage.setMcc(standardModel->data(index, OPERATOR_ROLE_MCC).toString());
        mManagerStorage._operatorStorage.setMnc(standardModel->data(index, OPERATOR_ROLE_MNC).toString());

        ptrOperatorEditor = std::make_unique<OperatorEditor>(mManagerStorage, true);

        connect(ptrOperatorEditor.get(), &OperatorEditor::signalUpdate, this, &OperatorTree::slotUpdate);
        ptrOperatorEditor->UpdateOperatorEditor(mManagerStorage);
    }
}

void OperatorTree::generateTree()
{
    for(int i = 0; i < mManagerStorage.listCountryStorage.length(); i++)
    {
        parentItem = new QStandardItem(QIcon(":Countries/" + mManagerStorage.listCountryStorage.at(i).getCode() + ".png"), mManagerStorage.listCountryStorage.at(i).getName());

        parentItem->setData(mManagerStorage.listCountryStorage.at(i).getName(), COUNTRY_ROLE_NAME);
        parentItem->setData(mManagerStorage.listCountryStorage.at(i).getMcc(), COUNTRY_ROLE_MCC);
        parentItem->setData(mManagerStorage.listCountryStorage.at(i).getCode(), COUNTRY_ROLE_CODE);
        parentItem->setData(mManagerStorage.listCountryStorage.at(i).getMncLength(), COUNTRY_ROLE_LENGTH);

        rootNode->appendRow(parentItem);

        for(int j = 0; j < mManagerStorage.listOperatorStorage.length(); j++)
        {
            if(mManagerStorage.listCountryStorage.at(i).getMcc() == mManagerStorage.listOperatorStorage.at(j).getMcc().toInt())
            {
                childItem = new QStandardItem(QIcon(":Operators/" + mManagerStorage.listOperatorStorage.at(j).getMcc() + "_" + mManagerStorage.listOperatorStorage.at(j).getMnc() + ".png"),
                                    mManagerStorage.listOperatorStorage.at(j).getName() + "(" + mManagerStorage.listOperatorStorage.at(j).getMcc() + ", " + mManagerStorage.listOperatorStorage.at(j).getMnc() + ")");

                childItem->setData(mManagerStorage.listOperatorStorage.at(j).getMcc(), OPERATOR_ROLE_MCC);
                childItem->setData(mManagerStorage.listOperatorStorage.at(j).getMnc(), OPERATOR_ROLE_MNC);
                childItem->setData(mManagerStorage.listOperatorStorage.at(j).getName(), OPERATOR_ROLE_NAME);

                parentItem->appendRow(childItem);
            }
        }
    }
}

void OperatorTree::slotInsert(OperatorStorage& storage)
{
    if (mManagerStorage.insert_operator(storage)) {
        QStandardItem* countryItem = findCountryItemByMCC(storage.getMcc());
        if (countryItem) {
            QStandardItem* operatorItem = new QStandardItem(QIcon(":Operators/" + storage.getMcc() + "_" + storage.getMnc() + ".png"),
                                                            storage.getName() + "(" + storage.getMcc() + ", " + storage.getMnc() + ")");
            operatorItem->setData(storage.getMcc(), OPERATOR_ROLE_MCC);
            operatorItem->setData(storage.getMnc(), OPERATOR_ROLE_MNC);
            operatorItem->setData(storage.getName(), OPERATOR_ROLE_NAME);

            countryItem->appendRow(operatorItem);
        }
    }
}

void OperatorTree::slotUpdate(OperatorStorage& storage)
{
    if (mManagerStorage.update_operator(storage)) {
        QStandardItem* operatorItem = findOperatorItemByMCCAndMNC(storage.getMcc(), storage.getMnc());
        if (operatorItem) {
            operatorItem->setText(storage.getName() + "(" + storage.getMcc() + ", " + storage.getMnc() + ")");
            operatorItem->setData(storage.getName(), OPERATOR_ROLE_NAME);
        }
    }
}

QStandardItem* OperatorTree::findCountryItemByMCC(const QString& mcc)
{
    for (int i = 0; i < rootNode->rowCount(); ++i) {
        QStandardItem* countryItem = rootNode->child(i, 0);
            if (countryItem->data(COUNTRY_ROLE_MCC).toString() == mcc) {
                return countryItem;
        }
    }

    return nullptr;
}

QStandardItem* OperatorTree::findOperatorItemByMCCAndMNC(const QString& mcc, const QString& mnc)
{
    for (int i = 0; i < rootNode->rowCount(); ++i) {
        QStandardItem* countryItem = rootNode->child(i, 0);

        for (int j = 0; j < countryItem->rowCount(); ++j) {
            QStandardItem* operatorItem = countryItem->child(j, 0);
            if (operatorItem->data(OPERATOR_ROLE_MCC).toString() == mcc &&
                operatorItem->data(OPERATOR_ROLE_MNC).toString() == mnc) {
                return operatorItem;
            }
        }
    }

    return nullptr;
}
