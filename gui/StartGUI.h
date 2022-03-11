#pragma once
#include <QWidget>
#include <QPushButton>
#include <QComboBox>

class StartGUI : public QWidget {

    Q_OBJECT

private:

    QPushButton* startAdminModeButton;
    QComboBox* filetypeSelector;
    QPushButton* startUserModeButton;

    void initGUI();

    void adminModeWindow();
    void userModeWindow();

public:

    StartGUI();
    ~StartGUI() override;
};
