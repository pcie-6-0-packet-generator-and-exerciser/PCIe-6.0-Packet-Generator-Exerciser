#pragma once
#include <QtCharts>
#include "utils/tlp.h"


namespace Ui
{
    class StatsWidget : public QFrame
    {
        Q_OBJECT

    public:
        explicit StatsWidget(QWidget* parent = nullptr);
        ~StatsWidget();
       void incStats(TLPType type);
       void decStats(TLPType type);
        //static void initializeStats();
     public slots:
       void viewStats();

    private:
       int memRead32;
       int memWrite32;
       int memRead64;
       int memWrite64;
       int configRead0;
       int configWrite0;
       int configRead1;
       int configWrite1;


    };
}
