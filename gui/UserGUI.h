#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include "../controller/Controller.h"
#include "./user events/UserEventsTableModel.h"

class UserGUI : public QMainWindow {

    Q_OBJECT

public:

    Controller controller;

private:

    QPushButton* showAllEventsButton;

    QComboBox* monthSelector;
    QPushButton* parseEventsButton;

    QPushButton* showUserEventListButton;
    QPushButton* openUserEventListButton;

    void initGUI();

    void showAllEventsWidget();
    void manageUserEventsListWidget();
    void openUserEventsListFile();
    void parseEvents();

public:

    explicit UserGUI(Controller&);
    ~UserGUI() override;
};

