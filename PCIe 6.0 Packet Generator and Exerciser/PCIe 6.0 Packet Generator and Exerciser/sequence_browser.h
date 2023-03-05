#pragma once
#include <QtWidgets/QFrame>
#include "tlp_card.h"
#include <list>
namespace Ui
{
    class SequenceBrowser: public QFrame
    {
        Q_OBJECT

    public:
        explicit SequenceBrowser(QWidget* parent = nullptr);
        ~SequenceBrowser();
    private:
        void createCardsSequence();
        void manageLayout();
    private:
        std::list<TLPCard*> cards_;
    };

}
