#include "Operation.h"

AddOperation::AddOperation(EventRepository *repo_, Event event_) : \
    repo(repo_), new_event(event_) {

}

void AddOperation::execUndo() {

    this->repo->removeEvent(this->new_event.getTitle(), this->new_event.getDateTime());
}

void AddOperation::execRedo() {

    this->repo->addEvent(this->new_event);
}

RemoveOperation::RemoveOperation(EventRepository *repo_, Event event_) : \
    repo(repo_), old_event(event_) {

}

void RemoveOperation::execUndo() {

    this->repo->addEvent(this->old_event);
}

void RemoveOperation::execRedo() {

    this->repo->removeEvent(this->old_event.getTitle(), this->old_event.getDateTime());
}

UpdateOperation::UpdateOperation(EventRepository *repo_, Event new_event_, Event old_event_) : \
    repo(repo_), new_event(new_event_), old_event(old_event_) {

}

void UpdateOperation::execUndo() {

    this->repo->updateEvent(this->old_event);
}

void UpdateOperation::execRedo() {

    this->repo->updateEvent(this->new_event);
}
