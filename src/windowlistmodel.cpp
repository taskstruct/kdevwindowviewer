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

#include <QIcon>

#include <netwm_def.h>
#include <kwindowsystem.h>

#include "windowlistmodel.h"

#include <QDebug>

WindowListModel::WindowListModel( WId kdevWinId, QObject* parent):
    QAbstractListModel(parent),
    m_kdevWinId(kdevWinId)
{
    KWindowSystem *kws = KWindowSystem::self();
    
//     QList<WId> winList = kws->windows();
//     
//     QList<WId>::ConstIterator it;
//     QList<WId>::ConstIterator end = KWindowSystem::windows().end();
//     for ( it = KWindowSystem::windows().begin(); it != end; ++it )
//     {
//         KWindowInfo kwi = kws->windowInfo(*it, NET::WMName | NET::WMVisibleName | NET::WMVisibleIconName | NET::WMWindowType);
//         
//         if( kwi.windowType(NET::NormalMask) == NET::Normal ) {
//             m_winList.append( kwi );
// //             qDebug() << "Adding window " << kwi.visibleName() << "(" << kwi.win() << ")";
//         }
//     }
    
    connect( kws, SIGNAL(windowAdded(WId)), this, SLOT(onWindowAdded(WId)));
    connect( kws, SIGNAL(windowRemoved(WId)), this, SLOT(onWindowRemoved(WId)));
    connect( kws, SIGNAL(windowChanged(WId,uint)), this, SLOT(onWindowChanged(WId,uint)) );
}

WindowListModel::~WindowListModel()
{
    m_winList.clear();
}

QVariant WindowListModel::data(const QModelIndex& index, int role) const
{
    if( !index.isValid() ) {
        return QVariant();
    }
    
    if( index.row() >= m_winList.count() ) {
        return QVariant();
    }
    
    if( index.column() > 0 ) {
        return QVariant();
    }
    
    switch(role)
    {
        case Qt::DisplayRole: {
            return m_winList[index.row()].visibleName();
        }
        
//         case Qt::DecorationRole: {
//             qDebug() << "ICON: " << m_winList[index.row()].visibleIconName();
//             return QIcon(m_winList[index.row()].visibleIconName());
//         }

        default: break;
    }
    
    return QVariant();
}

int WindowListModel::rowCount(const QModelIndex& parent) const
{
    return m_winList.count();
}

void WindowListModel::onWindowAdded(WId id)
{
    KWindowInfo kwi = KWindowSystem::self()->windowInfo(id, NET::WMName | NET::WMVisibleName | NET::WMVisibleIconName | NET::WMWindowType);
    if( ( kwi.windowType(NET::NormalMask) == NET::Normal ) && ( id != m_kdevWinId ) ) {
        beginInsertRows( QModelIndex(), m_winList.count(), m_winList.count() + 1 );
        m_winList.append( kwi );
//         qDebug() << "onWindowAdded " << kwi.visibleName() << "(" << id << ")";
        endInsertRows();
    }
}

void WindowListModel::onWindowRemoved(WId id)
{
    int count = m_winList.count();
    
    int iter = 0;
    bool found = false;
    
    while( iter < count )
    {
        if( m_winList[iter].win() == id ) {
            found = true;
            break;
        }
        
        ++iter;
    }
    
    if( found )
    {
        beginRemoveRows( QModelIndex(), iter, iter + 1 );
        m_winList.removeAt(iter);
        endRemoveRows();
    }
}

void WindowListModel::onWindowChanged(WId id, uint prop)
{
    int index = 0;
    const int count = m_winList.count();
    
    while( index < count )
    {
        if( m_winList[index].win() == id && ( ( prop & (NET::WMName | NET::WMVisibleName | NET::WMVisibleIconName | NET::WMWindowType) ) != 0 ) )
        {
            m_winList[index] = KWindowInfo(id, NET::WMName | NET::WMVisibleName | NET::WMVisibleIconName | NET::WMWindowType);
            const QModelIndex topLeft = createIndex( index, 0 );
            const QModelIndex bottomRight = createIndex( index, 0);
            emit dataChanged( topLeft, bottomRight );
        }
        
        ++index;
    }
}


KWindowInfo WindowListModel::getWindowInfo( QModelIndex index ) const
{
    if( index.isValid() && ( index.row() < m_winList.count() ) )
    {
        return m_winList[index.row()];
    }
    
    return KWindowInfo();
}



#include "windowlistmodel.moc"
