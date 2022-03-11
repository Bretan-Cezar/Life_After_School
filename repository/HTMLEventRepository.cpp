#include "HTMLEventRepository.h"
#include <fstream>
#include <iomanip>

HTMLEventRepository::HTMLEventRepository(const char *filename, const char *html_filename_)
        : EventRepository(filename), html_filename(html_filename_) {

}

void HTMLEventRepository::save() {

    EventRepository::save();

    std::ofstream html(this->html_filename.c_str());

    html << "<!DOCTYPE html>\n<html>\n<head>\n" << std::right << std::setfill(' ')
         << std::setw(4) << "<title>Events</title>\n"
         << "</head>\n<body>\n<table border=\"1\">\n"
         << std::setw(4) << "<tr>\n"
         << std::setw(8) << "<td>Title</td>\n"
         << std::setw(8) << "<td>Description</td>\n"
         << std::setw(8) << "<td>Date</td>\n"
         << std::setw(8) << "<td>Time</td>\n"
         << std::setw(8) << "<td>Event Link</td>\n"
         << std::setw(4) << "</tr>\n";

    for(auto it : this->list) {

        html << std::right << std::setfill(' ')
             << std::setw(4) << "<tr>\n"
             << std::setw(8) << "<td>" << it.getTitle() << "</td>\n"
             << std::setw(8) << "<td>" << it.getDescription() << "</td>\n"
             << std::setw(8) << "<td>" << it.getDateTime().tm_year+1900 << "-" << it.getDateTime().tm_mon+1 << "-" << it.getDateTime().tm_mday << "</td>\n"
             << std::setw(8) << "<td>" << it.getDateTime().tm_hour << ":" << it.getDateTime().tm_min << "</td>\n"
             << std::setw(8) << "<td><a href=\"" << it.getLink() << "\">Link</a></td>\n"
             << std::setw(4) << "</tr>\n";
    }

    html << "</table>\n</body>\n</html>";

    html.close();
}

std::vector<std::string> HTMLEventRepository::getCommand() {

    std::vector<std::string> command;

    command.emplace_back(R"(C:\Program Files\Google\Chrome\Application\chrome.exe)");
    command.push_back(R"("C:\Users\Cezar Bretan\Documents\GitHub\Life_After_School\cmake-build-debug/")" + this->html_filename);

    return command;
}
