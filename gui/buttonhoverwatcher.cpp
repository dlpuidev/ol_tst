#include "buttonhoverwatcher.h"


ButtonHoverWatcher::ButtonHoverWatcher(QWidget *parent) : QPushButton (parent)
{
    setMouseTracking(true);
    installEventFilter(this);
}

ButtonHoverWatcher::ButtonHoverWatcher(QString pathEnterIcon, QString pathLeaveIcon, QWidget *parent): QPushButton (parent)
{
    EnterIcon = new QIcon(pathEnterIcon);
    LeaveIcon = new QIcon(pathLeaveIcon);
    setIcon(*LeaveIcon);
    setMouseTracking(true);
    installEventFilter(this);
}

ButtonHoverWatcher::ButtonHoverWatcher(QIcon *ptrEnterIcon, QIcon *ptrLeaveIcon, QWidget *parent): QPushButton (parent)
{
    EnterIcon = ptrEnterIcon;
    LeaveIcon = ptrLeaveIcon;
    setIcon(*LeaveIcon);
    setMouseTracking(true);
    installEventFilter(this);
}

ButtonHoverWatcher::~ButtonHoverWatcher()
{
    delete EnterIcon;
    delete LeaveIcon;
}

void ButtonHoverWatcher::setEnterIcon(QIcon *ptrNewIcon)
{
    EnterIcon = ptrNewIcon;
}

void ButtonHoverWatcher::setLeaveIcon(QIcon *ptrNewIcon)
{
    LeaveIcon = ptrNewIcon;
}

void ButtonHoverWatcher::onEnterIcon(void)
{
    setIcon(*EnterIcon);
}

void ButtonHoverWatcher::onLeaveIcon(void)
{
    setIcon(*LeaveIcon);
}

bool ButtonHoverWatcher::eventFilter(QObject *watched, QEvent *event)
{

    if(watched == this)
    {

        if (event->type() == QEvent::Enter)
        {
            setIcon(*EnterIcon);
        }

        if (event->type() == QEvent::Leave)
        {
            setIcon(*LeaveIcon);
        }
    }

    return QWidget::eventFilter(watched, event);
}
