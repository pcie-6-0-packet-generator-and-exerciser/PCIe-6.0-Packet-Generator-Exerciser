#pragma once

#include <QtWidgets/QFrame>
#include "utils/tlp.h"

class QLabel;
namespace Ui
{
    class TLPCard: public QFrame
    {
        Q_OBJECT

    public:
        explicit TLPCard(TLPType type, QWidget* parent = nullptr);
        ~TLPCard();
    public:
        TLP tlp;
        //TLP* tlp;
    private:
        void mouseMoveEvent(QMouseEvent* event);
        //void  mousePressEvent(QMouseEvent* event);
        void manageLayout();
       
    private:
        QLabel* textLabel_;
        TLPType tlpType;
    };
}