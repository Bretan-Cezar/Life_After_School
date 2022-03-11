#pragma once
#include <QWidget>
#include <QPushButton>
#include "domain/Event.h"
#include <QLabel>
#include <QListWidget>
#include "UserEventsTableModel.h"
#include <QTableView>

class ManageUserEventsGUI : public QWidget {

private:

    UserEventsTableModel* model;

    QPushButton* deleteEventButton;

    QTableView* eventsTableView;

    void initGUI();
    int getSelectedIndex();
    void deleteEvent();
    void makeConnections();

public:

    ManageUserEventsGUI(UserEventsTableModel*);
};
