#pragma once
#include <QtWidgets/QFrame>
#include "tlp_card.h"
#include <list>
class QScrollBar;
namespace Ui
{
    class SequenceBrowser: public QFrame
    {
        Q_OBJECT

    public:
        explicit SequenceBrowser(QWidget* parent = nullptr);
        ~SequenceBrowser();
    private:
        void createSideBar();
        void createCardsSequence();
        void manageLayout();
    private:
        QScrollBar* sideBar_;
        std::list<TLPCard*> cards_;
    };

}
