/*******************************************************************************
**  Copyright (C) 2013  Marek Wrzeszcz
**  mail: marek.wrzeszcz@hotmail.com
**
**  This file is part of the MGEOSTAT.
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#include "GeoWidget.h"

GeoWidget::GeoWidget(QWidget *parent) :
    QWidget(parent),
    gModel(NULL)
{
    create_widget();
}

GeoWidget::GeoWidget(GeoModel *ptrModel, QWidget *parent):
    QWidget(parent),
    gModel(ptrModel)
{
    create_widget();
}

GeoWidget::~GeoWidget()
{

}

void GeoWidget::slot_update_dane()
{

}

void GeoWidget::slot_update_view()
{

}

void GeoWidget::slot_update_model()
{

}

void GeoWidget::create_widget()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    toolBar = new QToolBar("tools");
    boxLayout = new QVBoxLayout(this);
    boxLayout->setContentsMargins(0,0,0,0);
    boxLayout->setSpacing(0);
    boxLayout->addWidget(toolBar);
}
