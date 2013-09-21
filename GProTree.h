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
