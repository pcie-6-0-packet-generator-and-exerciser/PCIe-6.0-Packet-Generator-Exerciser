#pragma once
#include <QtWidgets/QFrame>
#include<QVBoxLayout>
#include <QPushButton>
#include <QString>
#include "custom_line_edit.h"
#include "utils/tlp.h"


namespace Ui
{
    class PacketDetails : public QFrame
    {
        Q_OBJECT

    public:
        explicit PacketDetails(QWidget* parent = nullptr);
        ~PacketDetails();
    private:
        void manageLayout();
        void clearView(QLayout* layout);
        void createHeader();
        void viewMemRead32();
        void viewMemRead64();



    private:
        QVBoxLayout* contentLayout_ ;
        QPushButton* saveButton;
        TLP* currentTLP;
        std::vector<CustomLineEdit*> currentLineEdits;

    public slots:
        void updateView(TLP* tlp);
        void saveValues();
    };
}