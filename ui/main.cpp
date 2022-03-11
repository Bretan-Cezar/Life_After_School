#include "./ui/UI.h"
#include "CSVEventRepository.h"
#include "HTMLEventRepository.h"

void mode_input(std::string &mode, std::string &filetype) {

    char mode_tmp[6], filetype_tmp[5];

    printf("Enter mode (admin / user): ");
    std::cin.getline(mode_tmp, 50);
    if(strcmp(mode_tmp, "admin") != 0 and strcmp(mode_tmp, "user") != 0) throw InputError("Invalid mode!\n");

    mode = mode_tmp;

    if(strcmp(mode_tmp, "user") == 0) {

        printf("Enter file type (csv / html): ");
        std::cin.getline((filetype_tmp), 50);
        if(strcmp(filetype_tmp, "csv") != 0 and strcmp(filetype_tmp, "html") != 0) throw InputError("Invalid file type!\n");

        filetype = filetype_tmp;
    }
}

/*
int main() {

    auto *admin_repo_ = new EventRepository{"admin_db.txt"};

    std::string mode, filetype;
    bool valid_mode = false;

    while(!valid_mode) {
        try {
            mode_input(mode, filetype);
            valid_mode = true;
        }
        catch (InputError &ie) {
            printf("%s", ie.getMessage());
        }
    }

    EventRepository *user_repo_;

    if(mode == "admin") {

        user_repo_ = new EventRepository{"user_db.txt"};

        Controller controller_{admin_repo_, user_repo_};
        UI ui_{controller_};

        ui_.admin_start_ui();
    }
    else {

        if(filetype == "csv")
            user_repo_ = new CSVEventRepository{"user_db.txt", "user_events.csv"};
        else
            user_repo_ = new HTMLEventRepository{"user_db.txt", "user_events.html"};

        Controller controller_{admin_repo_, user_repo_};
        UI ui_{controller_};
        ui_.user_start_ui();
    }

    return 0;
}
*/