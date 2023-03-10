#pragma once
#include <QtWidgets/QFrame>
#include "tlp_card.h"
#include <list>
namespace Ui
{
    class TypeBrowser : public QFrame
    {
        Q_OBJECT

    public:
        explicit TypeBrowser(QWidget* parent = nullptr);
        ~TypeBrowser();
    private:
        void dragEnterEvent(QDragEnterEvent* event);
        //void dropEvent(QDropEvent* event);
        void createCardsSequence();
        void manageLayout();
        
    private:
        std::list<TLPCard*> cards_;
    };

}