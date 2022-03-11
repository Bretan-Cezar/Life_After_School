#pragma once
#include "../controller/Controller.h"
class UI {

    private:

        Controller controller;

        static void year_input_ui(int &year_);

        static void month_input_ui(int &month);

        static void day_input_ui(int& day_, int month_, int year_);

        static void time_input_ui(int &hour_, int &min_);

        static void link_input_ui(char *link);

        static void nr_of_people_input_ui(int &nr_of_people);

        void admin_add_event_ui();

        void admin_remove_event_ui();

        void admin_update_event_ui();

        void user_parse_events_ui();

        void user_delete_event_ui();

        void admin_print_events_ui();

        void user_print_events_ui();

        static void admin_print_menu() ;

        static void user_print_menu() ;

    public:

        explicit UI(const Controller& controller_);

        void admin_start_ui();

        void user_start_ui();
};

class InputError: public std::exception {

    private:

        char msg[101]{};

    public:

        explicit InputError(const char msg[]);

        char* getMessage();
};
