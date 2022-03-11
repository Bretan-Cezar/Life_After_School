#pragma once
#include <../controller/Controller.h>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QCalendarWidget>
#include <QTimeEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QTableWidget>
#include <QShortcut>

class AdminGUI : public QMainWindow {

    Q_OBJECT

private:

    Controller controller;

    QTableWidget* eventTableWidget;
    QLineEdit* eventTitleWidget;
    QTextEdit* eventDescriptionWidget;
    QCalendarWidget* eventDateWidget;
    QTimeEdit* eventTimeWidget;
    QLineEdit* eventNrOfPeopleWidget;
    QLineEdit* eventLinkWidget;
    QPushButton* addEventButton;
    QPushButton* removeEventButton;
    QPushButton* updateEventButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QShortcut* undoKeys;
    QShortcut* redoKeys;

    void initGUI();

    int getSelectedIndex() const;

    void makeConnections();

    void addEvent();

    void removeEvent();

    void updateEvent();

    void undo();

    void redo();
public:

    AdminGUI(const Controller&);

    ~AdminGUI();

};
