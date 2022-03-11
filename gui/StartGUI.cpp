#include "StartGUI.h"
#include "AdminGUI.h"
#include "UserGUI.h"
#include <QVBoxLayout>

StartGUI::StartGUI() {

    this->initGUI();
    QObject::connect(this->startAdminModeButton, &QPushButton::clicked, this, &StartGUI::adminModeWindow);
    QObject::connect(this->startUserModeButton, &QPushButton::clicked, this, &StartGUI::userModeWindow);
}

StartGUI::~StartGUI() = default;

void StartGUI::initGUI() {

    this->setWindowTitle("Life After School");
    this->resize(300, 200);
    auto* layout1 = new QVBoxLayout{this};

    this->startAdminModeButton = new QPushButton("Admin Mode");

    layout1->addWidget(this->startAdminModeButton);

    auto* userModeWidget = new QWidget{};
    auto* layout2 = new QHBoxLayout(userModeWidget);

    this->filetypeSelector = new QComboBox();
    this->filetypeSelector->addItem("CSV");
    this->filetypeSelector->addItem("HTML");

    layout2->addWidget(this->filetypeSelector);

    this->startUserModeButton = new QPushButton("User Mode");

    layout2->addWidget(this->startUserModeButton);

    layout1->addWidget(userModeWidget);

}

void StartGUI::adminModeWindow() {

    auto *admin_repo_ = new EventRepository{"admin_db.txt"};
    auto* user_repo_ = new EventRepository{"user_db.txt"};

    Controller controller_{admin_repo_, user_repo_};

    auto* adminWindow = new AdminGUI{controller_};

    adminWindow->show();

    this->close();
}

void StartGUI::userModeWindow() {

    auto *admin_repo_ = new EventRepository{"admin_db.txt"};

    EventRepository *user_repo_;

    if (this->filetypeSelector->currentText() == "CSV")
        user_repo_ = new CSVEventRepository{"user_db.txt", "user_events.csv"};
    else
        user_repo_ = new HTMLEventRepository{"user_db.txt", "user_events.html"};

    Controller controller_{admin_repo_, user_repo_};

    auto* userWindow = new UserGUI{controller_};

    userWindow->show();

    this->close();
}
