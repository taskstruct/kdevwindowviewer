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

#include <QtGui/QListView>
#include <QtGui/QStackedLayout>

#include "windowlistmodel.h"
#include "windowcontainer.h"
#include "windowlistview.h"

WindowListView::WindowListView(QWidget* parent, Qt::WindowFlags f):
    QWidget(parent, f)
{
    m_listView = new QListView(this);
    m_windowModel = new WindowListModel( window()->winId(), this);
    
    m_listView->setModel(m_windowModel);
    
    m_windowContainer = new WindowContainer(this);
    
    m_layout = new QStackedLayout(this);
    m_layout->addWidget(m_listView);
    m_layout->addWidget(m_windowContainer);
    
    connect( m_listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onDoubleClicked(QModelIndex)));
    connect( m_windowContainer, SIGNAL(windowDetached()), this, SLOT(onWindowDetached()) );
}

WindowListView::~WindowListView()
{
}

void WindowListView::onDoubleClicked(QModelIndex index)
{
    if( index.isValid() )
    {
        m_windowContainer->setWindow( m_windowModel->getWindowInfo( index ) );
        m_layout->setCurrentIndex(1);
    }
}

void WindowListView::onWindowDetached()
{
    m_layout->setCurrentIndex(0);
}



#include "windowlistview.moc"
