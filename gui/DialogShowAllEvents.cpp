#include "DialogShowAllEvents.h"
#include <QListWidget>
#include <QHBoxLayout>
DialogShowAllEvents::DialogShowAllEvents(const std::vector<Event> &events_) : events{events_} {

    this->initDialog();
}

void DialogShowAllEvents::initDialog() {

    this->resize(960, 540);

    auto* centralLayout = new QHBoxLayout{this};
    auto* list = new QListWidget{};


    for (auto it : this->events) {

        list->addItem(it.getTitle());
    }

    centralLayout->addWidget(list);
}
