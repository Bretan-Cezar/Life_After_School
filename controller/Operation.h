#pragma once
#include "../repository/EventRepository.h"

class Operation {

public:

    virtual void execUndo() = 0;
    virtual void execRedo() = 0;
};

class AddOperation : public Operation {

private:

    EventRepository* repo;
    Event new_event;

public:

    AddOperation(EventRepository*, Event);
    void execUndo() override;
    void execRedo() override;
};

class RemoveOperation : public Operation {

private:

    EventRepository* repo;
    Event old_event;

public:

    RemoveOperation(EventRepository*, Event);
    void execUndo() override;
    void execRedo() override;
};

class UpdateOperation : public Operation {

private:

    EventRepository* repo;
    Event new_event;
    Event old_event;

public:

    UpdateOperation(EventRepository*, Event, Event);
    void execUndo() override;
    void execRedo() override;
};

