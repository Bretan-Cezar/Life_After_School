#pragma once
#include <vector>
#include "../domain/Event.h"
#include <cstring>

class EventRepository {

    private:
        char filename[101]{};

        void load_from_file();

        static bool cmp_Event_to_unique_keys(Event e, char *title_, tm datetime_);

    protected:

        std::vector<Event> list;

    public:

        explicit EventRepository(const char *filename_);

        void addEvent(Event e);

        void removeEvent(char title_[61], tm datetime_);

        Event getEvent(char *title_, tm datetime_);

        void updateEvent(Event e);

        std::vector<Event> getAll();

        virtual void save();

        virtual std::vector<std::string> getCommand();
};

class RepositoryError : public std::exception {

    private:
        char msg[101]{};

    public:

        explicit RepositoryError(const char *msg);

        char* getMessage();
};