#include <QDate>
#include "UserEventsTableModel.h"

UserEventsTableModel::UserEventsTableModel(Controller &controller_) : controller(controller_) {

}

int UserEventsTableModel::rowCount(const QModelIndex &parent) const {

    return this->controller.user_get_all_events().size();
}

int UserEventsTableModel::columnCount(const QModelIndex &parent) const {

    return 3;
}

QVariant UserEventsTableModel::data(const QModelIndex &index, int role) const {

    int row = index.row(), col = index.column();

    Event curr_event = this->controller.user_get_all_events()[row];
    tm datetime = curr_event.getDateTime();

    if (role == Qt::DisplayRole) {

        switch (col) {

            case 0:

                return QString::fromStdString(curr_event.getTitle());

            case 1:

                return QDate(datetime.tm_year+1900, datetime.tm_mon+1, datetime.tm_mday);

            case 2:

                return QTime(datetime.tm_hour, datetime.tm_min);

            default:

                break;
        }
    }

    return QVariant();
}

QVariant UserEventsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role == Qt::DisplayRole) {

        if (orientation == Qt::Horizontal) {

            switch (section) {

                case 0:
                    return QString("Title");
                case 1:
                    return QString("Date");
                case 2:
                    return QString("Time");
                default:
                    break;
            }
        }

    }
    return QVariant();
}


Qt::ItemFlags UserEventsTableModel::flags(const QModelIndex &index) const {

    if (index.column() == 0)
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    return Qt::ItemFlags();
}

void UserEventsTableModel::deleteRow(int row) {

    Event event = this->controller.user_get_all_events()[row];

    char title[61];
    strcpy(title, event.getTitle());

    this->controller.user_delete_event(title, event.getDateTime());
    this->controller.user_save_database();

    this->removeRow(row);

    QModelIndex topLeft = this->index(0,0);
    QModelIndex bottomRight = this->index(this->controller.user_get_all_events().size()-1, 3);

    emit dataChanged(topLeft, bottomRight);
}
