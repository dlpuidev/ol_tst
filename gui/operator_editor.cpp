#include "operator_editor.h"
#include <QtWidgets>

OperatorEditor::OperatorEditor(ManagerStorage &ptrManagerStorage, bool isOperator, QWidget *parent)
    : QWidget(parent)
    , mManagerStorage(ptrManagerStorage)
    , isOperator(isOperator)
{
    IconDefaultPath = ":/icons/question.png";

    headerOperatorEditor();
    bodyOperatorEditor();
    footerOperatorEditor();

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addLayout(hbLayout,  1, 1, 1, 1);
    mainLayout->addLayout(layout,  2, 1, 1, 1);
    mainLayout->addWidget(buttonBox,  3, 1, 1, 1);

    setMinimumWidth(250);
    setMaximumWidth(250);

    setMinimumHeight(150);
    setMaximumHeight(150);

    setLayout(mainLayout);
    setWindowTitle(tr("Application name"));

    connect(buttonSave, &QPushButton::clicked, this, &OperatorEditor::SlotButtonSave);
    connect(buttonCancel, &QPushButton::clicked, this, &OperatorEditor::SlotButtonClose);

    connect(lineEditName, &QLineEdit::textChanged, this, &OperatorEditor::nameChanged);
    connect(lineEditMcc, &QLineEdit::textChanged, this, &OperatorEditor::mccChanged);
    connect(lineEditMnc, &QLineEdit::textChanged, this, &OperatorEditor::mncChanged);
}

OperatorEditor::~OperatorEditor()
{

}

void OperatorEditor::headerOperatorEditor(void)
{    
    hbLayout = new QHBoxLayout;

    firstIcon = new QLabel();
    lableWindowName = new QLabel("Operator editor");

    lableWindowName->setFont(QFont("Times", 10, 100, 0));

    QPixmap myPixmap( IconDefaultPath );
    firstIcon->setPixmap( myPixmap );

    hbLayout->addWidget(firstIcon, 1, Qt::AlignLeft);
    hbLayout->addWidget(lableWindowName, 2);
}

void OperatorEditor::bodyOperatorEditor(void)
{
    layout = new QGridLayout;
    labelName = new QLabel(tr("Name"));
    labelMcc = new QLabel(tr("MCC"));
    labelMnc = new QLabel(tr("MNC"));

    lineEditName = new QLineEdit;
    lineEditMcc = new QLineEdit;
    lineEditMnc = new QLineEdit;

    lineEditMcc->setReadOnly(isOperator);
    lineEditMnc->setReadOnly(isOperator);

    secondIcon = new QLabel();
    QPixmap myPixmap( ":/icons/question.png" );
    secondIcon->setPixmap( myPixmap );

    layout->addWidget(labelName,  1, 1, 1, 1);
    layout->addWidget(lineEditName,  1, 2, 1, 2);
    layout->addWidget(labelMcc,  2, 1, 1, 1);
    layout->addWidget(lineEditMcc,  2, 2, 1, 1);
    layout->addWidget(secondIcon,  2, 3, 1, 1);

    layout->addWidget(labelMnc,  3, 1, 1, 1);
    layout->addWidget(lineEditMnc,  3, 2, 1, 2);
}

void OperatorEditor::footerOperatorEditor(void)
{
    buttonSave = new QPushButton(tr("Save"));
    buttonCancel = new QPushButton(tr("Cancel"));

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(buttonSave, QDialogButtonBox::ActionRole);
    buttonBox->addButton(buttonCancel, QDialogButtonBox::ActionRole);
}

void OperatorEditor::SlotButtonClose()
{
    lineEditName->clear();
    lineEditMcc->clear();
    lineEditMnc->clear();

    OperatorEditor::close();
}

void OperatorEditor::SlotButtonSave()
{
    mManagerStorage._operatorStorage.setName(lineEditName->text());
    mManagerStorage._operatorStorage.setMcc(lineEditMcc->text());
    mManagerStorage._operatorStorage.setMnc(lineEditMnc->text());

    if(isOperator)
        emit signalUpdate(mManagerStorage._operatorStorage);
    else
        emit signalInsert(mManagerStorage._operatorStorage);

    lineEditName->clear();
    lineEditMcc->clear();
    lineEditMnc->clear();

    OperatorEditor::close();
}

void OperatorEditor::nameChanged(const QString &)
{
    mManagerStorage._operatorStorage.setName(lineEditName->text());
}

void OperatorEditor::mccChanged(const QString &)
{
    mManagerStorage._operatorStorage.setMcc(lineEditMcc->text());
    IconOperatorPath = ":/Operators/" + mManagerStorage._operatorStorage.getMcc() + "_" + mManagerStorage._operatorStorage.getMnc() + ".png";

    IconCountryPath = IconDefaultPath;

    for(int i = 0; i < mManagerStorage.listCountryStorage.length(); i++)
    {
        CountryStorage tempStorage = (mManagerStorage.listCountryStorage.at(i));
        if(mManagerStorage._operatorStorage.getMcc().toInt() == tempStorage.getMcc())
        {
            IconCountryPath = ":/Countries/" + tempStorage.getCode() + ".png";
            break;
        }
    }

    QFileInfo File(IconCountryPath);
    if(File.exists())
    {
        secondIcon->setPixmap( IconCountryPath );
    }

    fileIsValid(IconOperatorPath);
}

void OperatorEditor::mncChanged(const QString &)
{
    mManagerStorage._operatorStorage.setMnc(lineEditMnc->text());
    IconOperatorPath = ":/Operators/" + mManagerStorage._operatorStorage.getMcc() + "_" + mManagerStorage._operatorStorage.getMnc() + ".png";
    fileIsValid(IconOperatorPath);
}

void OperatorEditor::fileIsValid(const QString& path)
{
    QFileInfo File(path);
    if(!File.exists())
    {
        firstIcon->setPixmap( IconDefaultPath );
    }

    else if(File.isReadable())
    {
        firstIcon->setPixmap( path );
    }
}

void OperatorEditor::UpdateOperatorEditor(ManagerStorage &ptrManagerStorage)
{
    QString pixmapOperator = ":/Operators/" + ptrManagerStorage._operatorStorage.getMcc() + "_" + ptrManagerStorage._operatorStorage.getMnc() + ".png";
    QString pixmapCountries = ":/Countries/" + ptrManagerStorage._countryStorage.getCode() + ".png";

    firstIcon->setPixmap( pixmapOperator );
    secondIcon->setPixmap( pixmapCountries );
    lineEditName->setText(tr("%1").arg(ptrManagerStorage._operatorStorage.getName()));
    lineEditMcc->setText(tr("%1").arg(ptrManagerStorage._operatorStorage.getMcc()));
    lineEditMnc->setText(tr("%1").arg(ptrManagerStorage._operatorStorage.getMnc()));

    OperatorEditor::show();
}
