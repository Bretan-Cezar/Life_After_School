#include "EventRepository.h"
#include <cstring>
#include <fstream>

RepositoryError::RepositoryError(const char *msg_) {

    strcpy(this->msg, msg_);
}

char *RepositoryError::getMessage() {
    return this->msg;
}

bool EventRepository::cmp_Event_to_unique_keys(Event e, char *title_, tm datetime_) {

    return (strcmp(e.getTitle(), title_) == 0 && e.getDateTime().tm_year == datetime_.tm_year && \
        e.getDateTime().tm_mon == datetime_.tm_mon && e.getDateTime().tm_mday == datetime_.tm_mday && \
        e.getDateTime().tm_hour == datetime_.tm_hour && e.getDateTime().tm_min == datetime_.tm_min);
}

EventRepository::EventRepository(const char *filename_) {

    strcpy(this->filename, filename_);
    this->load_from_file();
}

void EventRepository::save() {

    std::ofstream fout (this->filename);

    fout << this->list.size() << "\n";

    for(const auto& it : this->list) {

        fout << it;
    }

    fout.close();
}

void EventRepository::load_from_file() {

    std::ifstream fin (this->filename);

    char n_str[7];

    fin.getline(n_str, 7);

    int n = strtol(n_str, nullptr, 10);

    for(int i = 0; i < n; i++) {

        Event event{};
        fin >> event;
        this->addEvent(event);
    }
    fin.close();

}

void EventRepository::addEvent(Event e) {

    for(auto it : this->list) {

        if(it == e) {

            throw RepositoryError("Event hasn't been added due to it being a duplicate.\n");
        }
    }

    this->list.push_back(e);
}

void EventRepository::removeEvent(char *title_, tm datetime_) {

    int i = 0;
    for(auto it : this->list) {

        if(cmp_Event_to_unique_keys(it, title_, datetime_)) {

            this->list.erase(this->list.begin() + i);
            return;
        }
        i++;
    }

    throw RepositoryError("Event hasn't been removed due to it not being found.\n");
}

void EventRepository::updateEvent(Event e) {

    int i = 0;
    for(auto it : this->list) {

        if(it == e) {

            this->list[i] = e;
            return;
        }
        i++;
    }

    throw RepositoryError("Event hasn't been updated due to it not being found.\n");
}

Event EventRepository::getEvent(char *title_, tm datetime_) {

    for(auto it : this->list) {

        if (cmp_Event_to_unique_keys(it, title_, datetime_))
            return it;
    }

    tm dt{};
    Event default_event{(char*)"", (char*)"", dt, 0, (char*)""};
    return default_event;
}

std::vector<Event> EventRepository::getAll() {

    std::vector<Event> list_copy = this->list;
    return list_copy;
}

std::vector<std::string> EventRepository::getCommand() {
    return std::vector<std::string>();
}
