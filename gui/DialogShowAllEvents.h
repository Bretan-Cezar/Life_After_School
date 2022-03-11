#pragma once
#include <QDialog>
#include "../domain/Event.h"

class DialogShowAllEvents : public QDialog {

private:

    const std::vector<Event> &events;

    void initDialog();

public:

    explicit DialogShowAllEvents(const std::vector<Event> &);
};
