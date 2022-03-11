#include "AdminGUI.h"
#include <QFormLayout>
#include <QModelIndex>
#include <QMessageBox>

AdminGUI::AdminGUI(const Controller &controller_) : controller(controller_) {

    this->initGUI();
    this->makeConnections();
}

AdminGUI::~AdminGUI() = default;


void AdminGUI::initGUI() {

    this->setWindowTitle("[ADMIN] Life After School");
    this->resize(1024, 768);

    auto* centralWidget = new QWidget{this};
    auto* centralLayout = new QHBoxLayout{centralWidget};

    /*
    this->eventListWidget = new QListWidget{};
    std::vector<Event> event_list = this->controller.admin_get_all_events();

    for (auto it : event_list) {

        this->eventListWidget->addItem(it.getTitle());
    }
*/
    this->eventTableWidget = new QTableWidget{0,3};
    std::vector<Event> event_list = this->controller.admin_get_all_events();

    int r = 0;
    for (auto it : event_list) {

        auto *title = new QTableWidgetItem(it.getTitle());
        auto *date = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_year+1900) + "-" + std::to_string(it.getDateTime().tm_mon+1) + "-" + std::to_string(it.getDateTime().tm_mday)));
        auto *time = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_hour) + ":" + std::to_string(it.getDateTime().tm_min)));

        this->eventTableWidget->insertRow(r);
        this->eventTableWidget->setItem(r, 0, title);
        this->eventTableWidget->setItem(r, 1, date);
        this->eventTableWidget->setItem(r, 2, time);
        r++;
    }
    auto* serviceWidget = new QWidget{};
    auto* serviceLayout = new QVBoxLayout{serviceWidget};

    auto* informationWidget = new QWidget{};
    auto* informationLayout = new QFormLayout{informationWidget};

    this->eventTitleWidget = new QLineEdit{};

    informationLayout->addRow("Title: ", this->eventTitleWidget);

    this->eventDescriptionWidget = new QTextEdit{};
    informationLayout->addRow("Description: ", this->eventDescriptionWidget);

    this->eventDateWidget = new QCalendarWidget{};
    informationLayout->addRow("Date: ", this->eventDateWidget);

    this->eventTimeWidget = new QTimeEdit{};
    informationLayout->addRow("Time: ", this->eventTimeWidget);

    this->eventNrOfPeopleWidget = new QLineEdit{};
    informationLayout->addRow("Number of people taking part: ", this->eventNrOfPeopleWidget);

    this->eventLinkWidget = new QLineEdit{};
    informationLayout->addRow("Event link: ", this->eventLinkWidget);

    auto* buttonWidget = new QWidget{};
    auto* buttonLayout = new QHBoxLayout{buttonWidget};

    this->addEventButton = new QPushButton("Add Event");
    buttonLayout->addWidget(this->addEventButton);
    this->removeEventButton = new QPushButton("Remove Event");
    buttonLayout->addWidget(this->removeEventButton);
    this->updateEventButton = new QPushButton("Update Event");
    buttonLayout->addWidget(this->updateEventButton);

    serviceLayout->addWidget(informationWidget);
    serviceLayout->addWidget(buttonWidget);

    auto* undoredoWidget = new QWidget{};
    auto* undoredoLayout = new QHBoxLayout{undoredoWidget};

    this->undoButton = new QPushButton{"Undo"};
    this->redoButton = new QPushButton{"Redo"};

    undoredoLayout->addWidget(this->undoButton);
    undoredoLayout->addWidget(this->redoButton);

    serviceLayout->addWidget(undoredoWidget);

    centralLayout->addWidget(this->eventTableWidget);
    centralLayout->addWidget(serviceWidget);

    this->setCentralWidget(centralWidget);

    this->undoKeys = new QShortcut{QKeySequence("Ctrl+Z"), this};
    this->redoKeys = new QShortcut{QKeySequence("Ctrl+Y"), this};


}

int AdminGUI::getSelectedIndex() const {

    QModelIndexList selectedIndexes = this->eventTableWidget->selectionModel()->selectedIndexes();

    if (selectedIndexes.empty()) {

        this->eventTitleWidget->clear();
        this->eventDescriptionWidget->clear();
        this->eventDateWidget->setSelectedDate(QDate(2021, 1, 1));
        this->eventNrOfPeopleWidget->clear();
        this->eventTimeWidget->clear();

        return -1;
    }

    return selectedIndexes.at(0).row();
}

void AdminGUI::makeConnections() {

    QObject::connect(this->eventTableWidget, &QTableWidget::itemSelectionChanged, [this]() {

            int selectedIndex = this->getSelectedIndex();

            if (selectedIndex < 0)
                return;

            Event event = this->controller.admin_get_all_events()[selectedIndex];
            tm datetime = event.getDateTime();

            this->eventTitleWidget->setText(event.getTitle());
            this->eventDescriptionWidget->setText(event.getDescription());
            this->eventDateWidget->setSelectedDate(QDate(datetime.tm_year+1900, datetime.tm_mon+1, datetime.tm_mday));
            this->eventTimeWidget->setTime(QTime(datetime.tm_hour, datetime.tm_min));
            this->eventNrOfPeopleWidget->setText(QString::fromStdString(std::to_string(event.getNrOfPeople())));
            this->eventLinkWidget->setText(event.getLink());
        });

    QObject::connect(this->addEventButton, &QPushButton::clicked, this, &AdminGUI::addEvent);
    QObject::connect(this->removeEventButton, &QPushButton::clicked, this, &AdminGUI::removeEvent);
    QObject::connect(this->updateEventButton, &QPushButton::clicked, this, &AdminGUI::updateEvent);

    QObject::connect(this->undoKeys, &QShortcut::activated, this, &AdminGUI::undo);
    QObject::connect(this->redoKeys, &QShortcut::activated, this, &AdminGUI::redo);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &AdminGUI::undo);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &AdminGUI::redo);
}

void AdminGUI::addEvent() {

    char title[61], desc[251], link[151];
    strcpy(title, this->eventTitleWidget->text().toStdString().c_str());

    if (strlen(title) == 0 || strchr(title, '~'))
        QMessageBox::critical(this, "Error", "Invalid event title!");

    strcpy(desc, this->eventDescriptionWidget->toPlainText().toStdString().c_str());

    QDate raw_date = this->eventDateWidget->selectedDate();
    QTime raw_time = this->eventTimeWidget->time();

    int nr_of_people = this->eventNrOfPeopleWidget->text().toInt();
    strcpy(link, this->eventLinkWidget->text().toStdString().c_str());

    tm datetime{0, raw_time.minute(), raw_time.hour(), raw_date.day(), raw_date.month()-1, raw_date.year()-1900, 0, 0, 0};

    try {
        this->controller.admin_add_event(title, desc, datetime, nr_of_people, link);
        this->controller.admin_save_database();
    }
    catch (RepositoryError &re) {
        QMessageBox::critical(this, "Error", "Duplicate event addition attempted!");
        return;
    }

    this->eventTableWidget->setRowCount(0);

    std::vector<Event> event_list = this->controller.admin_get_all_events();

    int r = 0;
    for (auto it : event_list) {

        auto *title_ = new QTableWidgetItem(it.getTitle());
        auto *date = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_year+1900) + "-" + std::to_string(it.getDateTime().tm_mon+1) + "-" + std::to_string(it.getDateTime().tm_mday)));
        auto *time = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_hour) + ":" + std::to_string(it.getDateTime().tm_min)));

        this->eventTableWidget->insertRow(r);
        this->eventTableWidget->setItem(r, 0, title_);
        this->eventTableWidget->setItem(r, 1, date);
        this->eventTableWidget->setItem(r, 2, time);
        r++;
    }

    this->eventTableWidget->setCurrentCell(event_list.size()-1, 0);
}

void AdminGUI::removeEvent() {

    int selectedIndex = this->getSelectedIndex();

    if (selectedIndex < 0) {
        QMessageBox::critical(this, "Error", "No event selected!");
        return;
    }

    Event event = this->controller.admin_get_all_events()[selectedIndex];

    try {
        this->controller.admin_remove_event(event.getTitle(), event.getDateTime());
        this->controller.admin_save_database();
    }
    catch (RepositoryError &re) {
        QMessageBox::critical(this, "Error", re.getMessage());
    }

    this->eventTableWidget->setRowCount(0);

    std::vector<Event> event_list = this->controller.admin_get_all_events();

    int r = 0;
    for (auto it : event_list) {

        auto *title = new QTableWidgetItem(it.getTitle());
        auto *date = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_year+1900) + "-" + std::to_string(it.getDateTime().tm_mon+1) + "-" + std::to_string(it.getDateTime().tm_mday)));
        auto *time = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_hour) + ":" + std::to_string(it.getDateTime().tm_min)));

        this->eventTableWidget->insertRow(r);
        this->eventTableWidget->setItem(r, 0, title);
        this->eventTableWidget->setItem(r, 1, date);
        this->eventTableWidget->setItem(r, 2, time);
        r++;
    }
}

void AdminGUI::updateEvent() {

    int selectedIndex = this->getSelectedIndex();

    if (selectedIndex < 0) {
        QMessageBox::critical(this, "Error", "No event selected!");
        return;
    }

    char title[61], desc[251], link[151];
    strcpy(title, this->eventTitleWidget->text().toStdString().c_str());

    if (strlen(title) == 0 || strchr(title, '~'))
        QMessageBox::critical(this, "Error", "Invalid event title!");

    strcpy(desc, this->eventDescriptionWidget->toPlainText().toStdString().c_str());

    QDate raw_date = this->eventDateWidget->selectedDate();
    QTime raw_time = this->eventTimeWidget->time();

    int nr_of_people = this->eventNrOfPeopleWidget->text().toInt();
    strcpy(link, this->eventLinkWidget->text().toStdString().c_str());

    tm datetime{0, raw_time.minute(), raw_time.hour(), raw_date.day(), raw_date.month()-1, raw_date.year()-1900, 0, 0, 0};

    try {
        this->controller.admin_update_event(title, desc, datetime, nr_of_people, link);
        this->controller.admin_save_database();
    }
    catch (RepositoryError &re) {
        QMessageBox::critical(this, "Error", re.getMessage());
        return;
    }

    this->eventTableWidget->setRowCount(0);

    std::vector<Event> event_list = this->controller.admin_get_all_events();

    int r = 0;
    for (auto it : event_list) {

        auto *title_ = new QTableWidgetItem(it.getTitle());
        auto *date = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_year+1900) + "-" + std::to_string(it.getDateTime().tm_mon+1) + "-" + std::to_string(it.getDateTime().tm_mday)));
        auto *time = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_hour) + ":" + std::to_string(it.getDateTime().tm_min)));

        this->eventTableWidget->insertRow(r);
        this->eventTableWidget->setItem(r, 0, title_);
        this->eventTableWidget->setItem(r, 1, date);
        this->eventTableWidget->setItem(r, 2, time);
        r++;
    }

    this->eventTableWidget->setCurrentCell(selectedIndex, 0);
}

void AdminGUI::undo() {

    try {

        this->controller.undoLastOperation();
        this->controller.admin_save_database();
        this->eventTableWidget->setRowCount(0);

        std::vector<Event> event_list = this->controller.admin_get_all_events();

        int r = 0;
        for (auto it : event_list) {

            auto *title_ = new QTableWidgetItem(it.getTitle());
            auto *date = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_year+1900) + "-" + std::to_string(it.getDateTime().tm_mon+1) + "-" + std::to_string(it.getDateTime().tm_mday)));
            auto *time = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_hour) + ":" + std::to_string(it.getDateTime().tm_min)));

            this->eventTableWidget->insertRow(r);
            this->eventTableWidget->setItem(r, 0, title_);
            this->eventTableWidget->setItem(r, 1, date);
            this->eventTableWidget->setItem(r, 2, time);
            r++;
        }
    }
    catch (ControllerError &ce) {
        QMessageBox::information(this, "Undo", ce.get_msg().c_str());
    }

}

void AdminGUI::redo() {

    try {

        this->controller.redoLastOperation();
        this->controller.admin_save_database();
        this->eventTableWidget->setRowCount(0);

        std::vector<Event> event_list = this->controller.admin_get_all_events();

        int r = 0;
        for (auto it : event_list) {

            auto *title_ = new QTableWidgetItem(it.getTitle());
            auto *date = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_year+1900) + "-" + std::to_string(it.getDateTime().tm_mon+1) + "-" + std::to_string(it.getDateTime().tm_mday)));
            auto *time = new QTableWidgetItem(QString::fromStdString(std::to_string(it.getDateTime().tm_hour) + ":" + std::to_string(it.getDateTime().tm_min)));

            this->eventTableWidget->insertRow(r);
            this->eventTableWidget->setItem(r, 0, title_);
            this->eventTableWidget->setItem(r, 1, date);
            this->eventTableWidget->setItem(r, 2, time);
            r++;
        }
    }
    catch (ControllerError &ce) {
        QMessageBox::information(this, "Undo", ce.get_msg().c_str());
    }
}


