#include "mywidget.h"
#include "mywidgetplugin.h"

#include <QtPlugin>

myWidgetPlugin::myWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void myWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool myWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *myWidgetPlugin::createWidget(QWidget *parent)
{
    return new myWidget(parent);
}

QString myWidgetPlugin::name() const
{
    return QLatin1String("myWidget");
}

QString myWidgetPlugin::group() const
{
    return QLatin1String("");
}

QIcon myWidgetPlugin::icon() const
{
    return QIcon();
}

QString myWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString myWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool myWidgetPlugin::isContainer() const
{
    return false;
}

QString myWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"myWidget\" name=\"myWidget\">\n</widget>\n");
}

QString myWidgetPlugin::includeFile() const
{
    return QLatin1String("mywidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(mywidgetplugin, myWidgetPlugin)
#endif // QT_VERSION < 0x050000
