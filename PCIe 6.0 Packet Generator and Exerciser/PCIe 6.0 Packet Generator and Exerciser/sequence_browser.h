#pragma once
#include <QtWidgets/QFrame>
#include "tlp_card.h"
#include "packet_details_widget.h"
#include <list>
#include <queue>
#include <QVBoxLayout>
namespace Ui
{
    class SequenceBrowser: public QFrame
    {
        Q_OBJECT

    public:
        explicit SequenceBrowser(QWidget* parent = nullptr);
        std::queue<TLP*> getTLPCards();
        void setCurrentTab(currentTab tab);
        ~SequenceBrowser();
    private:
        void createCardsSequence();
        void manageLayout();
        void dropEvent(QDropEvent* event);
        void dragEnterEvent(QDragEnterEvent* event);
        //void contextMenuEvent(QContextMenuEvent* event) override;
    public:
        PacketDetails* packetDetails;
    private:
        QVBoxLayout* cardLayout_;
        std::list<TLPCard*> cards_;
        currentTab currentTab_ = currentTab::sequenceExplorer;
    public slots: 
        void deleteTLP(TLPCard* card);
    };

}
