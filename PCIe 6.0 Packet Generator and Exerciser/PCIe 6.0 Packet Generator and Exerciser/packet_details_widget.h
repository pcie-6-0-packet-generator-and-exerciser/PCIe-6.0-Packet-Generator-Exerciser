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
        void createConfigCommon();
        void createConfigOHCvector();
        void createMemOHCvector(int row);
        void createDataPayload(int row, bool readOnly = false);
        void createCplCommon();



        void viewMemRead32();
        void viewMemRead64();
        void viewMemWrite32();
        void viewMemWrite64();
        void viewConfigRead();
        void viewConfigWrite();
        void viewCpl();
        void viewCpld();

        //void viewVendorMsg();
       
        void saveMemCommon32();
        void saveMemCommon64();
        void saveLengthMemRead();
        void saveDataPayload();
        void saveConfigCommon();
        
            
        long long combineAddresses(std::string upperAddress, std::string lowerAddress);
        int binaryToInteger(const std::string& binary);



    private:
        QVBoxLayout* contentLayout_ ;
        QGridLayout* detailsLayout_;
        QPushButton* saveButton;
        TLP* currentTLP;
        int height = 50,width = 25;
        std::unordered_map<std::string, CustomLineEdit*> lineEditsMap;


    public slots:
        void updateView(TLP* tlp);
        void saveValues();
    };
}