#include "SingleEventGUI.h"
#include <QVBoxLayout>
#include <windows.h>

SingleEventGUI::SingleEventGUI(const Event& event_, Controller& controller_, int month_, int index_) : event{event_}, controller{controller_}, month{month_}, index{index_} {

    this->initGUI();
    QObject::connect(this->yesButton, &QPushButton::clicked, this, &SingleEventGUI::addEvent);
    QObject::connect(this->noButton, &QPushButton::clicked, this, &SingleEventGUI::skipEvent);
}

void SingleEventGUI::initGUI() {

    auto* centralLayout = new QVBoxLayout{this};

    auto* infoWidget = new QWidget{};

    auto* infoLayout = new QVBoxLayout{infoWidget};

    auto* title = new QLabel{this->event.getTitle()};

    title->setAlignment(Qt::AlignHCenter);

    title->setFont(QFont("Arial", 40));

    auto* description = new QLabel{this->event.getDescription()};
    description->setFont(QFont("Arial", 16));

    QString date_str = "Date: ";
    date_str += std::to_string(this->event.getDateTime().tm_year + 1900).c_str();
    date_str += " - ";
    date_str += std::to_string(this->event.getDateTime().tm_mon + 1).c_str();
    date_str += " - ";
    date_str += std::to_string(this->event.getDateTime().tm_mday).c_str();

    auto* date = new QLabel{date_str};
    date->setFont(QFont("Arial", 24));

    QString time_str = "Time: ";
    time_str += std::to_string(this->event.getDateTime().tm_hour).c_str();
    time_str += ":";
    time_str += std::to_string(this->event.getDateTime().tm_min).c_str();

    auto* time = new QLabel{time_str};
    time->setFont(QFont("Arial", 24));

    QString nr_p_str = "Number of Participants: ";
    nr_p_str += std::to_string(this->event.getNrOfPeople()).c_str();

    auto* nr_of_people = new QLabel{nr_p_str};
    nr_of_people->setFont(QFont("Arial", 24));

    infoLayout->addWidget(title);
    infoLayout->addWidget(description);
    infoLayout->addWidget(date);
    infoLayout->addWidget(time);
    infoLayout->addWidget(nr_of_people);

    auto* buttonWidget = new QWidget{};

    auto* buttonLayout = new QHBoxLayout{buttonWidget};

    auto* question = new QLabel("Would you like to take part in this event?");
    question->setFont(QFont("Arial", 14));

    this->yesButton = new QPushButton{"Yes"};
    this->noButton = new QPushButton{"No"};

    buttonLayout->addWidget(question);
    buttonLayout->addWidget(this->yesButton);
    buttonLayout->addWidget(this->noButton);

    centralLayout->addWidget(infoWidget);

    centralLayout->addWidget(buttonWidget);

    //ShellExecute(nullptr, nullptr, this->event.getLink(), nullptr, nullptr, SW_SHOWNORMAL);
}

SingleEventGUI::~SingleEventGUI() = default;


void SingleEventGUI::addEvent() {

    this->controller.user_add_event(this->event);
    this->controller.user_save_database();
    this->close();
}

void SingleEventGUI::skipEvent() {

    std::vector<Event> filtered_list = this->controller.get_filtered_events_by_month(this->month);
    SingleEventGUI *eventWidget;
    if (this->index < filtered_list.size()-1) {
        eventWidget = new SingleEventGUI{filtered_list[this->index + 1], this->controller, this->month,
                                         this->index + 1};
        eventWidget->show();
    }
    else if (filtered_list.size() > 1) {
        eventWidget = new SingleEventGUI{filtered_list[0], this->controller, this->month, 0};
        eventWidget->show();
    }

    this->close();
}

