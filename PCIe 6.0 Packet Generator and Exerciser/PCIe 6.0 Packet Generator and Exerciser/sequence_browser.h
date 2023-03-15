#pragma once
#include <QtWidgets/QFrame>
#include "tlp_card.h"
#include "packet_details_widget.h"
#include <list>
#include <QVBoxLayout>
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
        void dropEvent(QDropEvent* event);
        void dragEnterEvent(QDragEnterEvent* event);
    public:
        PacketDetails* packetDetails;
    private:
        QVBoxLayout* cardLayout_;
        std::list<TLPCard*> cards_;
    };

}
