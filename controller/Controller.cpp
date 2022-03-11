#include "Controller.h"
#include <algorithm>
#include <utility>

Controller::Controller(EventRepository *adminRepo, EventRepository *userRepo): admin_repo(adminRepo), user_repo(userRepo) {

}

void Controller::admin_add_event(char *title_, char *description_, tm datetime_, int nr_of_people_, char *link_) {

    Event new_event{title_, description_, datetime_, nr_of_people_, link_};

    auto* new_add_operation = new AddOperation(this->admin_repo, new_event);

    this->admin_repo->addEvent(new_event);

    this->undoStack.push(new_add_operation);

    while(!this->redoStack.empty()) this->redoStack.pop();

}

void Controller::admin_remove_event(char *title_, tm datetime_) {

    auto* new_remove_operation = new RemoveOperation(this->admin_repo, this->admin_repo->getEvent(title_, datetime_));

    this->admin_repo->removeEvent(title_, datetime_);

    this->undoStack.push(new_remove_operation);

    while(!this->redoStack.empty()) this->redoStack.pop();

    try {

        this->user_repo->removeEvent(title_, datetime_);
    }
    catch(RepositoryError &re){}
}

void Controller::admin_update_event(char *title_, char *description_, tm datetime_, int nr_of_people_, char *link_) {

    Event new_event{title_, description_, datetime_, nr_of_people_, link_};

    auto* new_update_operation = new UpdateOperation(this->admin_repo, new_event, this->admin_repo->getEvent(title_, datetime_));
    
    this->admin_repo->updateEvent(new_event);

    this->undoStack.push(new_update_operation);

    while(!this->redoStack.empty()) this->redoStack.pop();

    try {

        this->user_repo->updateEvent(new_event);
    }
    catch(RepositoryError &re){}
}


void Controller::user_add_event(const Event& event) {

    this->user_repo->addEvent(event);
}

void Controller::user_delete_event(char *title_, tm datetime_) {

    this->user_repo->removeEvent(title_, datetime_);

    Event updated_event = this->admin_repo->getEvent(title_, datetime_);
    updated_event.setNrOfPeople(updated_event.getNrOfPeople() - 1);
    this->admin_repo->updateEvent(updated_event);
}


std::vector<Event> Controller::admin_get_all_events() {

    return this->admin_repo->getAll();
}

std::vector<Event> Controller::user_get_all_events() {

    return this->user_repo->getAll();
}


std::vector<Event> Controller::get_all_events_ordered() {

    std::vector<Event> ordered_list = this->admin_repo->getAll();

    std::sort(ordered_list.begin(), ordered_list.end(), \
        [](const Event& a, const Event& b) { tm d_a = a.getDateTime(), d_b = b.getDateTime(); return difftime(mktime(&d_a), mktime(&d_b)) < 0;});

    return ordered_list;

}


std::vector<Event> Controller::get_filtered_events_by_month(int month) {

    std::vector<Event> filtered_list;
    std::vector<Event> main_list = this->admin_repo->getAll();
    std::vector<Event> exclusion_list = this->user_repo->getAll();

    for(auto it_main : main_list) {

        if(it_main.getDateTime().tm_mon + 1 == month) {

            bool _found = false;

            for (auto it_exc : exclusion_list)
                if (it_main == it_exc)
                    _found = true;

            if(!_found)
                filtered_list.push_back(it_main);
        }
    }

    return filtered_list;
}


void Controller::admin_save_database() {

    this->admin_repo->save();
}

void Controller::user_save_database() {

    this->user_repo->save();
}

std::vector<std::string> Controller::user_get_doc_open_command() {

    return this->user_repo->getCommand();
}

void Controller::undoLastOperation() {

    if (this->undoStack.empty()) {
        throw ControllerError("No more operations to be undone!");
    }

    this->undoStack.top()->execUndo();
    this->redoStack.push(this->undoStack.top());
    this->undoStack.pop();
}

void Controller::redoLastOperation() {

    if (this->redoStack.empty()) {
        throw ControllerError("No more operations to be redone!");
    }

    this->redoStack.top()->execRedo();
    this->undoStack.push(this->redoStack.top());
    this->redoStack.pop();
}

ControllerError::ControllerError(std::string msg_) : msg(std::move(msg_)) {

}

std::string ControllerError::get_msg() {
    return this->msg;
}
