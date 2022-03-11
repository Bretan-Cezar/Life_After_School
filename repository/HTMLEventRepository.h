#pragma once
#include "EventRepository.h"

class HTMLEventRepository : public EventRepository {

private:

    std::string html_filename{};

public:

    HTMLEventRepository(const char *filename, const char *html_filename_);

    void save() override;

    std::vector<std::string> getCommand() override;
};
