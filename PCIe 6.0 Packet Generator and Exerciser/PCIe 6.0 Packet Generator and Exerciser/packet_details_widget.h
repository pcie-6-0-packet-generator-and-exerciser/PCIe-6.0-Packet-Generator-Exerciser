#pragma once
#include <QtWidgets/QFrame>
#include<QVBoxLayout>
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


    private:

        QVBoxLayout* contentLayout_ ;

    public slots:
        void updateDetails();
    };
}