#pragma once
#include "../repository/EventRepository.h"
#include "../repository/CSVEventRepository.h"
#include "../repository/HTMLEventRepository.h"
#include "Operation.h"
#include <stack>

class Controller {

    private:

        EventRepository* admin_repo;
        EventRepository* user_repo;

        std::stack<Operation*> undoStack{};
        std::stack<Operation*> redoStack{};

    public:

        Controller(EventRepository *adminRepo, EventRepository *userRepo);

        void admin_add_event(char *title_, char *description_, tm datetime_, int nr_of_people_, char *link_);

        void admin_remove_event(char *title_, tm datetime_);

        void admin_update_event(char *title_, char *description_, tm datetime_, int nr_of_people_, char *link_);

        void user_add_event(const Event& event);

        void user_delete_event(char *title_, tm datetime_);

        std::vector<Event> admin_get_all_events();

        std::vector<Event> user_get_all_events();

        std::vector<Event> get_all_events_ordered();

        std::vector<Event> get_filtered_events_by_month(int month);

        void admin_save_database();

        void user_save_database();

        std::vector<std::string> user_get_doc_open_command();

        void undoLastOperation();

        void redoLastOperation();
};

class ControllerError : public std::exception {

private:

    std::string msg;

public:

    ControllerError(std::string);
    std::string get_msg();
};