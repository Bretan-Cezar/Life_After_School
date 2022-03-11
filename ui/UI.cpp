#include "UI.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <windows.h>

char *InputError::getMessage() {
    return this->msg;
}

InputError::InputError(const char *msg_) {

    strcpy(this->msg, msg_);
}


UI::UI(const Controller& controller_): controller(controller_) {

    this->controller = controller_;
}

void UI::year_input_ui(int& year_) {

    char y_str[5];

    printf("Enter event year (YYYY): ");
    std::cin.getline(y_str, 50);

    if(strlen(y_str) != 4) throw InputError("Invalid year!\n");
    if(!isdigit(y_str[0]) || y_str[0] == '0') throw InputError("Invalid year!\n");

    for (int i = 1; i < 4; i++)
        if(!isdigit(y_str[i])) throw InputError("Invalid year!\n");

    year_ = strtol(y_str, nullptr, 10);
}

void UI::month_input_ui(int& month_) {

    char m_str[3];

    printf("Enter event month: ");
    std::cin.getline(m_str, 50);

    if(strlen(m_str) != 1 && strlen(m_str) != 2) throw InputError("Invalid month!\n");
    if(!isdigit(m_str[0]) || m_str[0] == '0') throw InputError("Invalid month!\n");
    if(strlen(m_str) == 2 && !isdigit(m_str[1])) throw InputError("Invalid month!\n");
    if(strtol(m_str, nullptr, 10) > 12) throw InputError("Invalid month!\n");

    month_ = strtol(m_str, nullptr, 10);

}

void UI::day_input_ui(int& day_, int month_, int year_) {

    char d_str[3];

    printf("Enter event day: ");
    std::cin.getline(d_str, 50);

    if(strlen(d_str) != 1 && strlen(d_str) != 2) throw InputError("Invalid day!\n");
    if(!isdigit(d_str[0]) || d_str[0] == '0') throw InputError("Invalid day!\n");
    if(strlen(d_str) == 2 && !isdigit(d_str[1])) throw InputError("Invalid day!\n");
    if(strtol(d_str, nullptr, 10) > 31) throw InputError("Invalid day!\n");
    if(month_ == 2 && strtol(d_str, nullptr, 10) > 29) throw InputError("Invalid day!\n");
    if(year_%4 != 0 && month_ == 2 && strtol(d_str, nullptr, 10) > 28) throw InputError("Invalid day!\n");
    if((month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11) && strtol(d_str, nullptr, 10) == 31) throw InputError("Invalid day!\n");

    day_ = strtol(d_str, nullptr, 10);
}


void UI::time_input_ui(int &hour_, int &min_) {

    char t_str[6];

    printf("Enter event time (HH:MM): ");
    std::cin.getline(t_str, 50);

    if(!isdigit(t_str[0]) || !isdigit(t_str[1]) || t_str[2] != ':' || !isdigit(t_str[3]) || !isdigit(t_str[4]))
        throw InputError("Invalid time!\n");

    char h_str[3], m_str[3];

    h_str[0] = t_str[0];
    h_str[1] = t_str[1];
    h_str[2] = 0;

    m_str[0] = t_str[3];
    m_str[1] = t_str[4];
    m_str[2] = 0;

    if(strtol(h_str, nullptr, 10) >= 24) throw InputError("Invalid time!\n");
    if(strtol(m_str, nullptr, 10) >= 60) throw InputError("Invalid time!\n");

    hour_ = strtol(h_str, nullptr, 10);
    min_ = strtol(m_str, nullptr, 10);
}

void UI::nr_of_people_input_ui(int &nr_of_people) {

    char n_str[8];

    printf("Enter the number of people attending the event: ");

    std::cin.getline(n_str, 50);

    if(strlen(n_str) == 0) throw InputError("Invalid number!\n");

    for(int i = 0; i < strlen(n_str); i++)
        if(!isdigit(n_str[i])) throw InputError("Invalid number!\n");

    nr_of_people = strtol(n_str, nullptr, 10);
}

void UI::link_input_ui(char link[151]) {

    char link_tmp[151];

    const char link_prefix[9] = "https://";

    printf("Enter event link (~ invalid character): ");

    std::cin.getline(link_tmp, 151);

    if(strchr(link_tmp, '~')) throw InputError("Invalid link!\n");

    if(strncmp(link_tmp, link_prefix, 8) != 0) throw InputError("Invalid link!\n");

    strcpy(link, link_tmp);
}




void UI::admin_add_event_ui() {

    char title[61] = "~,", description[251] = "~,", link[151];
    int nr_of_people, year, month, day, hour, min;

    while(strchr(title, '~') || strchr(title, ',')) {
        printf("Enter event title (can't be empty, ~ and , invalid characters): ");
        std::cin.getline(title, 61);
        if(title[0] == 0) { title[0] = '~'; title[1] = ','; title[2] = 0; }
    }

    while(strchr(description, '~') || strchr(description, ',')) {
        printf("Enter event description (~ and , invalid characters): ");
        std::cin.getline(description, 251);
    }

    if(description[0] == 0) {
        description[0] = ' ';
        description[1] = 0;
    }

    bool valid_year = false, valid_month = false, valid_day = false, valid_time = false, valid_nr = false, valid_link = false;

    while(!valid_year) {
        try {
            this->year_input_ui(year);
            valid_year = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_month) {
        try {
            this->month_input_ui(month);
            valid_month = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_day) {
        try {
            this->day_input_ui(day, month, year);
            valid_day = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_time) {
        try {
            this->time_input_ui(hour, min);
            valid_time = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    tm datetime{0, min, hour, day, month-1, year-1900, 0, 0, 0};

    while(!valid_nr) {
        try {
            this->nr_of_people_input_ui(nr_of_people);
            valid_nr = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_link) {
        try {
            this->link_input_ui(link);
            valid_link = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    try {
        this->controller.admin_add_event(title, description, datetime, nr_of_people, link);
        printf("Event successfully added.\n");
    }
    catch (RepositoryError &re) {
        printf("%s", re.getMessage());
    }
}

void UI::admin_remove_event_ui() {

    char title[61] = "~,";
    int year, month, day, hour, min;

    while(strchr(title, '~') || strchr(title, ',')) {
        printf("Enter event title (can't be empty, ~ and , invalid characters): ");
        std::cin.getline(title, 61);
        if(title[0] == 0) { title[0] = '~'; title[1] = ','; title[2] = 0; }
    }

    bool valid_year = false, valid_month = false, valid_day = false, valid_time = false;

    while(!valid_year) {
        try {
            this->year_input_ui(year);
            valid_year = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_month) {
        try {
            this->month_input_ui(month);
            valid_month = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_day) {
        try {
            this->day_input_ui(day, month, year);
            valid_day = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_time) {
        try {
            this->time_input_ui(hour, min);
            valid_time = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    tm datetime{0, min, hour, day, month-1, year-1900, 0, 0, 0};

    try {
        this->controller.admin_remove_event(title, datetime);
        printf("Event successfully removed.\n");
    }
    catch (RepositoryError &re) {
        printf("%s", re.getMessage());
    }
}

void UI::admin_update_event_ui() {

    char title[61] = "~,", description[251] = "~,", link[151];
    int nr_of_people, year, month, day, hour, min;

    while(strchr(title, '~') || strchr(title, ',')) {
        printf("Enter event title (can't be empty, ~ and , invalid characters): ");
        std::cin.getline(title, 61);
        if(title[0] == 0) { title[0] = '~'; title[1] = ','; title[2] = 0; }
    }

    while(strchr(description, '~') || strchr(description, ',')) {
        printf("Enter event description (~ and , invalid characters): ");
        std::cin.getline(description, 251);
    }

    bool valid_year = false, valid_month = false, valid_day = false, valid_time = false, valid_nr = false, valid_link = false;

    while(!valid_year) {
        try {
            this->year_input_ui(year);
            valid_year = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_month) {
        try {
            this->month_input_ui(month);
            valid_month = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_day) {
        try {
            this->day_input_ui(day, month, year);
            valid_day = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_time) {
        try {
            this->time_input_ui(hour, min);
            valid_time = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    tm datetime{0, min, hour, day, month-1, year-1900, 0, 0, 0};

    while(!valid_nr) {
        try {
            this->nr_of_people_input_ui(nr_of_people);
            valid_nr = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_link) {
        try {
            this->link_input_ui(link);
            valid_link = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    try {
        this->controller.admin_update_event(title, description, datetime, nr_of_people, link);
        printf("Event successfully updated.\n");
    }
    catch (RepositoryError &re) {
        printf("%s", re.getMessage());
    }
}

void UI::user_parse_events_ui() {

    char m_str[3];
    int month;

    bool valid_month = false;

    while(!valid_month) {

        bool ok = true;
        printf("Enter event month or press ENTER to see all events: ");
        std::cin.getline(m_str, 50);

        if(m_str[0] == 0) break;

        if(strlen(m_str) != 1 && strlen(m_str) != 2) ok = false;
        if(!isdigit(m_str[0]) || m_str[0] == '0') ok = false;
        if(strlen(m_str) == 2 && !isdigit(m_str[1])) ok = false;
        if(strtol(m_str, nullptr, 10) > 12) ok = false;

        if(ok) {
            month = strtol(m_str, nullptr, 10);
            valid_month = true;
        }
        else printf("Invalid month!\n");
    }

    if(!valid_month) {

        std::vector<Event> event_list = this->controller.get_all_events_ordered();

        for(auto it : event_list) {

            printf("\n%s | %d-%d-%d %d:%d | %d people attending\n%s\n", it.getTitle(), \
            it.getDateTime().tm_year+1900, it.getDateTime().tm_mon+1, it.getDateTime().tm_mday, \
            it.getDateTime().tm_hour, it.getDateTime().tm_min, it.getNrOfPeople(), \
            it.getDescription());
        }

        printf("\n");
    }
    else {

        std::vector<Event> filtered_list = this->controller.get_filtered_events_by_month(month);

        char str_yes_no[4] = "";

        int i = 0;
        while(i < filtered_list.size()) {

            std::cout << filtered_list[i];

            ShellExecute(nullptr, nullptr, filtered_list[i].getLink(), nullptr, nullptr, SW_SHOWNORMAL);

            while(strcmp(str_yes_no, "yes") != 0 && strcmp(str_yes_no, "no") != 0) {

                printf("\nAdd this event to your list? (yes / no): ");
                std::cin.getline(str_yes_no, 51);
            }

            if(!strcmp(str_yes_no, "yes")) {
                this->controller.user_add_event(filtered_list[i]);
                this->controller.admin_update_event(filtered_list[i].getTitle(), filtered_list[i].getDescription(), \
                                                    filtered_list[i].getDateTime(), \
                                                    filtered_list[i].getNrOfPeople()+1, \
                                                    filtered_list[i].getLink());

                printf("See ya there!\n");
                break;
            }
            else {
                printf("\n");
                str_yes_no[0] = 0;
                if(i == filtered_list.size() - 1 && filtered_list.size() > 1) i = 0;
                else i++;
            }
        }
    }
}

void UI::user_delete_event_ui() {

    char title[61] = "~,";
    int year, month, day, hour, min;

    while(strchr(title, '~') || strchr(title, ',')) {
        printf("Enter event title (can't be empty, ~ and , invalid characters): ");
        std::cin.getline(title, 61);
        if(title[0] == 0) { title[0] = '~'; title[1] = ','; title[2] = 0; }
    }

    bool valid_year = false, valid_month = false, valid_day = false, valid_time = false;
    while(!valid_year) {
        try {
            this->year_input_ui(year);
            valid_year = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_month) {
        try {
            this->month_input_ui(month);
            valid_month = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_day) {
        try {
            this->day_input_ui(day, month, year);
            valid_day = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    while(!valid_time) {
        try {
            this->time_input_ui(hour, min);
            valid_time = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    tm datetime{0, min, hour, day, month-1, year-1900, 0, 0, 0};

    try {
        this->controller.user_delete_event(title, datetime);
        printf("Event successfully removed from your list.\n");
    }
    catch (RepositoryError &re) {
        printf("%s", re.getMessage());
    }

}

void UI::admin_print_events_ui() {

    std::vector<Event> event_list = this->controller.admin_get_all_events();

    for(const auto& it : event_list) {

        std::cout << it;
    }

    printf("\n");
}

void UI::user_print_events_ui() {

    std::vector<Event> event_list = this->controller.user_get_all_events();

    for(const auto& it : event_list) {

        std::cout << it;
    }

    printf("\n");
}


void UI::admin_print_menu() {

    printf("1. Add an event.\n");
    printf("2. Remove an event.\n");
    printf("3. Update an event.\n");
    printf("4. Show all events.\n");
    printf("0. Exit program.\n");
}

void UI::user_print_menu() {

    printf("1. Go through the events in a month.\n");
    printf("2. Show the events you are currently set to attend.\n");
    printf("3. Display the events you are attending in a CSV / HTML file.\n");
    printf("4. Delete an event from your list.\n");
    printf("0. Exit program.\n");
}

void UI::admin_start_ui() {

    this->admin_print_menu();
    char command[3];

    const char admin_command_list[5][2] = {"0", "1", "2", "3", "4"};

    bool done = false;

    while(!done) {

        printf("Admin>> ");
        std::cin.getline(command, 50);

        int command_number = -1;

        for (int i = 0; i < 5; i++)
            if(strcmp(admin_command_list[i], command) == 0) command_number = i;

        switch(command_number) {

            case 1:

                this->admin_add_event_ui();
                break;

            case 2:

                this->admin_remove_event_ui();
                break;

            case 3:

                this->admin_update_event_ui();
                break;

            case 4:

                this->admin_print_events_ui();
                break;

            case 0:

                this->controller.admin_save_database();
                this->controller.user_save_database();
                printf("Program terminated.\n");
                done = true;
                break;

            default:

                printf("Invalid command number!\n");
                break;
        }

    }

}


void UI::user_start_ui() {

    this->user_print_menu();
    const char user_command_list[5][2] = {"0", "1", "2", "3", "4"};

    std::vector<std::string> doc_open;

    char command[3];

    bool done = false;

    while(!done) {

        printf("LifeAfterSchool>> ");
        std::cin.getline(command, 50);

        int command_number = -1;

        for (int i = 0; i < 4; i++)
            if(strcmp(user_command_list[i], command) == 0) command_number = i;

        switch(command_number) {

            case 1:

                this->user_parse_events_ui();
                break;

            case 2:

                this->user_print_events_ui();
                break;

            case 3:

                doc_open = this->controller.user_get_doc_open_command();

                this->controller.user_save_database();

                ShellExecute(nullptr, "open", doc_open[0].c_str(), doc_open[1].c_str(), nullptr, SW_SHOWNORMAL);
                break;

            case 4:

                this->user_delete_event_ui();
                break;

            case 0:

                this->controller.admin_save_database();
                this->controller.user_save_database();
                printf("Program terminated.\n");
                done = true;
                break;

            default:

                printf("Invalid command number!\n");
                break;
        }

    }

}