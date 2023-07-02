#pragma once
#include <QtWidgets/QFrame>
#include "tlp_card.h"
#include "packet_details_widget.h"
#include <list>
#include <queue>
#include <QVBoxLayout>
#include "generate_sequece_dialog.h"
#include "stats_widget.h"
namespace Ui
{
    class SequenceBrowser: public QFrame
    {
        Q_OBJECT

    public:
        explicit SequenceBrowser(QWidget* parent = nullptr);
        std::queue<TLP*> getTLPCards();
        void setCurrentTab(currentTab tab);
        void setEditable(bool editable);
        bool isEditable() const { return editable_; }
        ~SequenceBrowser();
        void addTLPCard(TLP* tlp);
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
        bool editable_ = true;
        GenerateSequenceDialog* dialog_;
        StatsWidget* statsWidget_;
    public slots: 
        void deleteTLP(TLPCard* card);
        void onGenerateSequenceClick();
        void onGenerateSequenceDialogAccepted();
    };

}
