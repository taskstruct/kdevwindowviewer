/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  Nikolay S Nikolov <email>
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

#include <QX11EmbedContainer>
#include <KWindowInfo>
#include <KIcon>

#include "windowcontainer.h"
#include "ui_windowcontainer.h"

WindowContainer::WindowContainer(QWidget* parent, Qt::WindowFlags f):
    QWidget(parent, f)
{
    ui = new Ui::WindowContainer;
    ui->setupUi(this);
    
    m_x11Cont = new QX11EmbedContainer(this);
    
    ui->verticalLayout->addWidget(m_x11Cont);
    
    //TODO: set icons for buttons
    ui->detachButton->setIcon(KIcon("tab-detach"));
    ui->closeButton->setIcon(KIcon("tab-close"));
    
    connect( ui->detachButton, SIGNAL(pressed()), this, SLOT(onDetachPressed()) );
    connect( ui->detachButton, SIGNAL(pressed()), this, SIGNAL(windowDetached()) );
}

WindowContainer::~WindowContainer()
{
    delete ui;
}

void WindowContainer::setWindow(const KWindowInfo &kwi)
{
    m_x11Cont->embedClient(kwi.win());
    
    QString appName = kwi.visibleName();
    
    if( appName.isEmpty() ) {
        appName = kwi.name();
    }
    
    ui->windowTitle->setText( appName );
}

void WindowContainer::onDetachPressed()
{
    m_x11Cont->discardClient();
    ui->windowTitle->setText("");
}


