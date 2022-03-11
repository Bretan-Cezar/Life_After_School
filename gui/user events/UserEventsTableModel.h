#pragma once
#include <QAbstractItemModel>
#include "Controller.h"

class UserEventsTableModel : public QAbstractTableModel {

private:

    Controller& controller;

public:

    explicit UserEventsTableModel(Controller&);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

signals:

    void deleteRow(int row);
};

