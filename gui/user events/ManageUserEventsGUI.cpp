#include "ManageUserEventsGUI.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

ManageUserEventsGUI::ManageUserEventsGUI(UserEventsTableModel* model_) : model(model_) {

    this->initGUI();
    this->makeConnections();
}

void ManageUserEventsGUI::initGUI() {

    this->resize(450, 450);

    auto* centralLayout = new QVBoxLayout{this};

    this->eventsTableView = new QTableView{};

    centralLayout->addWidget(this->eventsTableView);

    this->eventsTableView->setModel(this->model);

    this->deleteEventButton = new QPushButton{"Delete event"};

    centralLayout->addWidget(this->deleteEventButton);
}

int ManageUserEventsGUI::getSelectedIndex() {

    QModelIndexList selectedIndexes = this->eventsTableView->selectionModel()->selectedIndexes();

    if (selectedIndexes.empty()) {

        return -1;
    }
    return selectedIndexes.at(0).row();
}

void ManageUserEventsGUI::makeConnections() {

    QObject::connect(this->deleteEventButton, &QPushButton::clicked, this, &ManageUserEventsGUI::deleteEvent);
}

void ManageUserEventsGUI::deleteEvent() {

    int selected_index = this->getSelectedIndex();
    if (selected_index < 0) {
        QMessageBox::critical(this, "Error", "An event must be selected.");
        return;
    }

    this->model->deleteRow(selected_index);
}
