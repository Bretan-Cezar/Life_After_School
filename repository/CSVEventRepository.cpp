#include "CSVEventRepository.h"
#include <iostream>

CSVEventRepository::CSVEventRepository(const char *filename, const char *csv_filename_)
        : EventRepository(filename), csv_filename(csv_filename_){

}

void CSVEventRepository::save() {

    EventRepository::save();

    std::ofstream csv(this->csv_filename.c_str());

    for(auto e : this->list) {

        csv << e.getTitle() << ',' << e.getDescription() << ',' << e.getDateTime().tm_year << ',' << e.getDateTime().tm_mon << ',' \
            << e.getDateTime().tm_mday << ',' << e.getDateTime().tm_hour << ',' << e.getDateTime().tm_min << ',' << e.getNrOfPeople() << ','
            << e.getLink() << "\n";

    }
    csv.close();
}

std::vector<std::string> CSVEventRepository::getCommand() {

    std::vector<std::string> command;
    std::string exe_path = R"(C:\Program Files (x86)\Microsoft Office\root\Office16\EXCEL.EXE)";

    command.push_back(exe_path);
    command.push_back(this->csv_filename);

    return command;
}
