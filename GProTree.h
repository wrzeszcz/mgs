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

#ifndef PROTREE_H
#define PROTREE_H

#include <QTreeView>
#include <QStandardItemModel>
///
/// \brief The GProTree class
///
class GProTree : public QTreeView
{
    Q_OBJECT
public:
    ///
    /// \brief GProTree
    /// \param parent
    ///
    explicit GProTree(QTreeView *parent = 0);

signals:
    ///
    /// \brief signal_open_win
    ///
    void signal_open_win(QString);
    
public slots:
    ///
    /// \brief slot_clicked
    ///
    void slot_clicked(QModelIndex);

private:
    ///
    /// \brief model
    ///
    QStandardItemModel *model;
    ///
    /// \brief modRoot
    ///
    QStandardItem *modRoot;
    ///
    /// \brief datItem
    ///
    QStandardItem *datItem;
    ///
    /// \brief mapItem
    ///
    QStandardItem *mapItem;
    ///
    /// \brief modItem
    ///
    QStandardItem *modItem;
    ///
    /// \brief rapItem
    ///
    QStandardItem *rapItem;
    ///
    /// \brief varItem
    ///
    QStandardItem *varItem;
};

#endif // PROTREE_H
