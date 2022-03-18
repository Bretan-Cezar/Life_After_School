# Life_After_School
An event planner (client+admin) I made in C++ Qt for the 2nd semester.
All OOP concepts and MVC architecture are being made use out of.

Admin mode features:
  
  - Event addition, removal and updating
  - Undo/Redo (using Command Design Pattern)
  - 
  ![admin_page](https://user-images.githubusercontent.com/39191865/159026119-2514769f-829e-4d9b-80f9-e176e3d2b8e7.png)


User mode features:

  - Viewing of all the titles of all the events

  - Viewing of complete description of each event in a selected month
  - Addition of any event to a personal user event list that hasn't been previously added (this also increments the number of attendants on the admin side)
  ![user_page1](https://user-images.githubusercontent.com/39191865/159025458-8f11f83b-fbc2-496b-ab6b-ccf5fb57ba70.png)
  
  - User event list management (removal of certain events)
  ![user_page3](https://user-images.githubusercontent.com/39191865/159025574-96033e6c-76fa-44be-9a49-ec886d8eaf72.png)

  - User event list exportable and viewable via CSV and HTML (issue: hardcoded browser path) formats
  ![user_page2](https://user-images.githubusercontent.com/39191865/159025596-32902105-7195-4a6b-9608-10def6d0ae11.png)
