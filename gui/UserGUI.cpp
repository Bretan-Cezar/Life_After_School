#include "UserGUI.h"
#include <QHBoxLayout>
#include "DialogShowAllEvents.h"
#include "gui/user events/ManageUserEventsGUI.h"
#include "SingleEventGUI.h"
#include <windows.h>
#include <QMessageBox>

UserGUI::UserGUI(Controller &controller_) : controller{controller_} {

    this->initGUI();

    QObject::connect(this->showAllEventsButton, &QPushButton::clicked, this, &UserGUI::showAllEventsWidget);
    QObject::connect(this->showUserEventListButton, &QPushButton::clicked, this, &UserGUI::manageUserEventsListWidget);
    QObject::connect(this->openUserEventListButton, &QPushButton::clicked, this, &UserGUI::openUserEventsListFile);
    QObject::connect(this->parseEventsButton, &QPushButton::clicked, this, &UserGUI::parseEvents);
}

UserGUI::~UserGUI() = default;

void UserGUI::initGUI() {

    this->resize(600, 400);

    auto* layoutWidget = new QWidget(this);
    auto* layout1 = new QVBoxLayout(layoutWidget);

    this->showAllEventsButton = new QPushButton("Show All Events");
    layout1->addWidget(this->showAllEventsButton);

    this->showUserEventListButton = new QPushButton("Manage Events You're Attending");
    layout1->addWidget(this->showUserEventListButton);

    this->openUserEventListButton = new QPushButton("Open File w/ Events You're Attending");
    layout1->addWidget(this->openUserEventListButton);

    auto* parseEventsWidget = new QWidget{};
    auto* hlayout = new QHBoxLayout{parseEventsWidget};

    this->monthSelector = new QComboBox();

    QString months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    this->monthSelector->addItem(months[0]);
    this->monthSelector->addItem(months[1]);
    this->monthSelector->addItem(months[2]);
    this->monthSelector->addItem(months[3]);
    this->monthSelector->addItem(months[4]);
    this->monthSelector->addItem(months[5]);
    this->monthSelector->addItem(months[6]);
    this->monthSelector->addItem(months[7]);
    this->monthSelector->addItem(months[8]);
    this->monthSelector->addItem(months[9]);
    this->monthSelector->addItem(months[10]);
    this->monthSelector->addItem(months[11]);

    this->parseEventsButton = new QPushButton("Go Through Events");

    hlayout->addWidget(this->monthSelector);
    hlayout->addWidget(this->parseEventsButton);

    layout1->addWidget(parseEventsWidget);

    this->setCentralWidget(layoutWidget);

}

void UserGUI::showAllEventsWidget() {

    auto* dialog = new DialogShowAllEvents{this->controller.get_all_events_ordered()};

    dialog->show();
}

void UserGUI::manageUserEventsListWidget() {

    auto* model = new UserEventsTableModel{this->controller};

    auto* events_widget = new ManageUserEventsGUI{model};

    events_widget->show();
}

void UserGUI::openUserEventsListFile() {

    std::vector<std::string> doc_open = this->controller.user_get_doc_open_command();

    this->controller.user_save_database();

    ShellExecute(nullptr, "open", doc_open[0].c_str(), doc_open[1].c_str(), nullptr, SW_SHOWNORMAL);
}

void UserGUI::parseEvents() {

    int month = this->monthSelector->currentIndex() + 1;
    std::vector<Event> filtered_list = this->controller.get_filtered_events_by_month(month);

    if (!filtered_list.empty()) {
        auto *eventWidget = new SingleEventGUI{filtered_list[0], this->controller, month, 0};
        eventWidget->show();
    }
    else {
        QMessageBox::information(this, "Information", "No events found for the given month.");
    }
}



