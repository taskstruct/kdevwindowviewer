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

#ifndef WINDOWVIEWER_PLUGIN_H
#define WINDOWVIEWER_PLUGIN_H

#include <interfaces/iplugin.h>

#include <QtCore/QVariantList>

class WindowViewerViewFactory;

class WindowViewerPlugin : public KDevelop::IPlugin
{
    Q_OBJECT
    
public:
    explicit WindowViewerPlugin(QObject *parent, const QVariantList& args = QVariantList());
    virtual ~WindowViewerPlugin();
    
private:
    WindowViewerViewFactory* m_viewFactory;
};

#endif // WINDOWVIEWER_PLUGIN_H

