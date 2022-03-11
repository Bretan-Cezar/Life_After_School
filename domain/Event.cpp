#include "Event.h"
#include <cstring>
#include <ctime>

Event::Event() = default;

Event::Event(char *title, char *description, tm datetime, int nr_of_people, char *link) {

    strcpy(this->title, title);
    strcpy(this->description, description);
    this->datetime = datetime;
    this->nr_of_people = nr_of_people;
    strcpy(this->link, link);
}

Event::Event(const Event &e) {

    strcpy(this->title, e.title);
    strcpy(this->description, e.description);
    this->datetime = e.datetime;
    this->nr_of_people = e.nr_of_people;
    strcpy(this->link, e.link);
}


Event& Event::operator=(const Event &e) {

    if(this != &e) {

        strcpy(this->title, e.title);
        strcpy(this->description, e.description);
        this->datetime = e.datetime;
        this->nr_of_people = e.nr_of_people;
        strcpy(this->link, e.link);
    }

    return *this;
}

Event::~Event() = default;

char* Event::getTitle() {

    return this->title;
}

char* Event::getDescription() {

    return this->description;
}

tm Event::getDateTime() const {

    return this->datetime;
}

int Event::getNrOfPeople() const {

    return this->nr_of_people;
}

char* Event::getLink() {

    return this->link;
}

void Event::setNrOfPeople(int new_nr_of_people) {

    this->nr_of_people = new_nr_of_people;
}

bool Event::operator==(Event e) {

    return (strcmp(this->getTitle(), e.getTitle()) == 0 && this->getDateTime().tm_year == e.getDateTime().tm_year && \
            this->getDateTime().tm_mon == e.getDateTime().tm_mon && this->getDateTime().tm_mday == e.getDateTime().tm_mday && \
            this->getDateTime().tm_hour == e.getDateTime().tm_hour && this->getDateTime().tm_min == e.getDateTime().tm_min);
}


std::ostream &operator<<(std::ostream &os, const Event &e) {

    os << "\n" << e.title << " | " << e.datetime.tm_year+1900 << "-" << e.datetime.tm_mon+1 << "-" << e.datetime.tm_mday \
       << " " << e.datetime.tm_hour << ":" << e.datetime.tm_min << " | " << e.nr_of_people << " people attending\n" \
       << e.description << "\nLink: " << e.link << "\n";

    return os;
}

std::ifstream &operator>>(std::ifstream &ifs, Event &e) {

    char title[61], description[251], link[151], ev_str[490];
    int nr_of_people, year, month, day, hour, min;

    ifs.getline(ev_str, 490);

    char *p = strtok(ev_str, "~");

    strcpy(title, p);
    p = strtok(nullptr, "~");
    strcpy(description, p);
    p = strtok(nullptr, "~");
    year = strtol(p, nullptr, 10);
    p = strtok(nullptr, "~");
    month = strtol(p, nullptr, 10);
    p = strtok(nullptr, "~");
    day = strtol(p, nullptr, 10);
    p = strtok(nullptr, "~");
    hour = strtol(p, nullptr, 10);
    p = strtok(nullptr, "~");
    min = strtol(p, nullptr, 10);

    tm datetime{0, min, hour, day, month, year, 0, 0, 0};

    p = strtok(nullptr, "~");
    nr_of_people = strtol(p, nullptr, 10);
    p = strtok(nullptr, "~");
    strcpy(link, p);

    e = Event{title, description, datetime, nr_of_people, link};

    return ifs;
}

std::ofstream &operator<<(std::ofstream &ofs, const Event &e) {

    ofs << e.title << '~' << e.description << '~' << e.datetime.tm_year << '~' << e.datetime.tm_mon << '~' \
        << e.datetime.tm_mday << '~' << e.datetime.tm_hour << '~' << e.datetime.tm_min << '~' << e.nr_of_people << '~'
        << e.link << "\n";

    return ofs;
}
