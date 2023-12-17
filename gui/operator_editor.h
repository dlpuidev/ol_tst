#ifndef OPERATOREDITOR_H
#define OPERATOREDITOR_H

#include <QWidget>

#include "manager_storage.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QLineEdit;
class QGridLayout;
class QDialogButtonBox;
class QHBoxLayout;
QT_END_NAMESPACE

class OperatorEditor : public QWidget
{
    Q_OBJECT
public:
    OperatorEditor(ManagerStorage &ptrManagerStorage, bool isOperator, QWidget *parent = nullptr);
    ~OperatorEditor();

    void UpdateOperatorEditor(ManagerStorage &ptrManagerStorage);

private:
    ManagerStorage &mManagerStorage;
    bool isOperator = false;

    QLabel *firstIcon;
    QLabel *secondIcon;
    QLabel *lableWindowName;

    QLabel *labelName;
    QLabel *labelMcc;
    QLabel *labelMnc;

    QLineEdit *lineEditName;
    QLineEdit *lineEditMcc;
    QLineEdit *lineEditMnc;

    QPushButton *buttonSave;
    QPushButton *buttonCancel;

    QGridLayout *lay;
    QGridLayout *layout;

    QHBoxLayout *hbLayout;

    QDialogButtonBox *buttonBox;

    QString IconDefaultPath;
    QString IconOperatorPath;
    QString IconCountryPath;

    void headerOperatorEditor(void);
    void bodyOperatorEditor(void);
    void footerOperatorEditor(void);

    void fileIsValid(const QString& path);

signals:
    void signalInsert(OperatorStorage& storage);
    void signalUpdate(OperatorStorage& storage);

private slots:
    void SlotButtonSave();
    void SlotButtonClose();

    void nameChanged(const QString &);
    void mccChanged(const QString &);
    void mncChanged(const QString &);
};

#endif // OPERATOREDITOR_H
