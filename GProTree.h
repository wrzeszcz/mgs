#ifndef PROTREE_H
#define PROTREE_H

#include <QTreeView>
#include <QStandardItemModel>

class GProTree : public QTreeView
{
    Q_OBJECT
public:
    explicit GProTree(QTreeView *parent = 0);

signals:
    void signal_open_win(QString);
    
public slots:
    void slot_clicked(QModelIndex);

private:
    QStandardItemModel *model;
    QStandardItem *modRoot;
    QStandardItem *datItem;
    QStandardItem *mapItem;
    QStandardItem *modItem;   
    QStandardItem *rapItem;
    QStandardItem *varItem;
};

#endif // PROTREE_H
