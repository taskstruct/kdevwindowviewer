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

#ifndef WINDOWLISTVIEW_H
#define WINDOWLISTVIEW_H

#include <QWidget>
#include <QModelIndex>

class QStackedLayout;
class WindowContainer;
class QListView;
class WindowListModel;

class WindowListView : public QWidget
{
    Q_OBJECT

public:
    WindowListView(QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~WindowListView();

private slots:
    void onDoubleClicked(QModelIndex index);
    void onWindowDetached();
    
private:
    QListView *m_listView;
    WindowListModel *m_windowModel;
    WindowContainer *m_windowContainer;
    QStackedLayout *m_layout;
};

#endif // WINDOWLISTVIEW_H
