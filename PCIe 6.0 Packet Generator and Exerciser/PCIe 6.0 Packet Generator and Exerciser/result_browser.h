#pragma once
#include <QtWidgets/QFrame>
#include "tlp_card.h"
#include <list>
#include <QVBoxLayout>
namespace Ui
{
    class ResultBrowser : public QFrame
    {
        Q_OBJECT

    public:
        explicit ResultBrowser(QWidget* parent = nullptr);
        ~ResultBrowser();
    private:
        void createCardsSequence();
        void manageLayout();
        
    private:
        QVBoxLayout* cardLayout_;
        std::list<TLPCard*> cards_;
    };

}