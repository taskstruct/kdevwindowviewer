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

#ifndef WINDOWLISTMODEL_H
#define WINDOWLISTMODEL_H

#include <QAbstractListModel>

#include <kwindowinfo.h>

class WindowListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    WindowListModel(WId kdevWinId, QObject* parent = 0);
    ~WindowListModel();
    
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

public slots:
    void onWindowAdded(WId id);
    void onWindowRemoved(WId id);
    void onWindowChanged(WId id, uint prop);
    
    KWindowInfo getWindowInfo( QModelIndex index ) const;
private:
    WId m_kdevWinId;
    QList<KWindowInfo> m_winList;
};

#endif // WINDOWLISTMODEL_H
