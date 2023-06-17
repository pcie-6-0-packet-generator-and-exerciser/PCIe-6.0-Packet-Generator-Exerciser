#pragma once
#include <QtWidgets/QFrame>
#include "tlp_card.h"
#include <list>
#include <QVBoxLayout>
#include <queue>

namespace Ui
{
    class ResultBrowser : public QFrame
    {
        Q_OBJECT

    public:
        explicit ResultBrowser(QWidget* parent = nullptr);
        ~ResultBrowser();
        void createCardsSequence(std::queue<TLP*> incomingPackets);
    private:
        void manageLayout();
        
    private:
        QVBoxLayout* cardLayout_;
        std::list<TLPCard*> cards_;
    };

}