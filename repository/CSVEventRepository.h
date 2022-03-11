#pragma once
#include "EventRepository.h"

class CSVEventRepository : public EventRepository {

private:

    std::string csv_filename{};

public:

    CSVEventRepository(const char *filename, const char *csv_filename_);

    void save() override;

    std::vector<std::string> getCommand() override;
};