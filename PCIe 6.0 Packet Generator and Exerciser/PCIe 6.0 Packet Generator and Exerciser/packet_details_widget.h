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
        void clearView();
        void createHeader();
        void createMem32bCommon();
        void createMem64bCommon();
        void createMemOHCvector(int row);



        void viewMemRead32();
        void viewMemRead64();
        void viewMemWrite32();
        void viewMemWrite64();
        void viewConfigRead0();
        void viewConfigWriteWrite();
        void viewVendorMsg();
       

            
        long long combineAddresses(std::string upperAddress, std::string lowerAddress);
        int binaryToInteger(const std::string& binary);



    private:
        QVBoxLayout* contentLayout_ ;
        QGridLayout* detailsLayout_;
        QPushButton* saveButton;
        TLP* currentTLP;
        std::vector<CustomLineEdit*> currentLineEdits;

    public slots:
        void updateView(TLP* tlp);
        void saveValues();
    };
}