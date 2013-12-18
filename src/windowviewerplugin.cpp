/*
 * kdevwindowviewer - Plugin for KDevelop 4 that allows you to embedded any window
 * Copyright (C) 2013  Nikolay S Nikolov nikolay.fatal.error@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "windowviewerplugin.h"
#include "windowlistview.h"

#include <KPluginFactory>
#include <KLocale>
#include <KAboutData>

#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>

using namespace KDevelop;

K_PLUGIN_FACTORY(KDevWindowViewerFactory, registerPlugin<WindowViewerPlugin>();)
K_EXPORT_PLUGIN(KDevWindowViewerFactory(
    KAboutData("kdevwindowviewer", "kdevwindowviewer", ki18n("WindowViewer"),
               "0.1", ki18n("An example plugin for KDevelop"), KAboutData::License_GPL)
))

class WindowViewerViewFactory: public KDevelop::IToolViewFactory
{
public:
    WindowViewerViewFactory(WindowViewerPlugin *plugin): m_plugin(plugin) {}

    virtual QWidget* create(QWidget *parent = 0)
    {
        WindowListView* ret = new WindowListView(parent);
        return ret;
    }

    virtual Qt::DockWidgetArea defaultPosition()
    {
        return Qt::BottomDockWidgetArea;
    }

    virtual QString id() const
    {
        return "org.kdevelop.WindowViewer";
    }

private:
    WindowViewerPlugin *m_plugin;
};

WindowViewerPlugin::WindowViewerPlugin(QObject* parent, const QVariantList& args) : IPlugin(KDevWindowViewerFactory::componentData(), parent),
    m_viewFactory(new WindowViewerViewFactory(this))
{
    Q_UNUSED(args)
//   KDEV_USE_EXTENSION_INTERFACE( IContextBrowser )

  core()->uiController()->addToolView(i18n("Window Viewer"), m_viewFactory);
}

WindowViewerPlugin::~WindowViewerPlugin()
{

}
