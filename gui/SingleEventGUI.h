#pragma once
#include <QWidget>
#include "Event.h"
#include "Controller.h"
#include <QPushButton>
#include <QLabel>

class SingleEventGUI : public QWidget {

private:

    Controller& controller;
    Event event;
    int month;
    int index;

    QPushButton* yesButton{};
    QPushButton* noButton{};

    void initGUI();

public:

    SingleEventGUI(const Event&, Controller&, int, int);
    ~SingleEventGUI();

    void addEvent();
    void skipEvent();
};

