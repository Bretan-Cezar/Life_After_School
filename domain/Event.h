#pragma once
#include <ctime>
#include <iostream>
#include <fstream>

class Event {

    private:

        char title[61]{};
        char description[251]{};
        tm datetime{};
        int nr_of_people{};
        char link[151]{};

    public:

        Event();

        Event(char title[61], char description[61], tm datetime, int nr_of_people, char link[151]);

        Event(const Event &e);

        Event& operator=(const Event &e);

        ~Event();

        char* getTitle();

        char* getDescription();

        tm getDateTime() const;

        int getNrOfPeople() const;

        char* getLink();

        void setNrOfPeople(int new_nr_of_people);

        bool operator==(Event e);

        friend std::ostream& operator<<(std::ostream& os, const Event& e);

        friend std::ifstream& operator>>(std::ifstream& ifs, Event& e);

        friend std::ofstream& operator<<(std::ofstream& ofs, const Event& e);
};

