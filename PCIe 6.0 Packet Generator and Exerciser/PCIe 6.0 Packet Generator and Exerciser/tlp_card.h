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
        explicit TLPCard(QWidget* parent = nullptr, QString text = "");
        ~TLPCard();
    public:
        TLP* tlp;
    private:
        void mouseMoveEvent(QMouseEvent* event);
        void manageLayout();
       
    private:
        QLabel* textLabel_;
    };
}