# Life_After_School
An event planner (client+admin) I made in C++ Qt for the 2nd semester.
All OOP concepts and MVC architecture are being made use out of.

Admin mode features:
  
  - Event addition, removal and updating
  - Undo/Redo (using Command Design Pattern)

User mode features:

  - Viewing of all the titles of all the events
  - Viewing of complete description of each event in a selected month
  - Addition of any event to a personal user event list that hasn't been previously added (this also increments the number of attendants on the admin side)
  - User event list management (removal of certain events)
  - User event list exportable and viewable via CSV and HTML (issue: hardcoded browser path) formats
