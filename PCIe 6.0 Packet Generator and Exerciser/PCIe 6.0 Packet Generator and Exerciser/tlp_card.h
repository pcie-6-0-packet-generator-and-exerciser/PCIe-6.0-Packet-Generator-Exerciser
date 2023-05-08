#pragma once

#include <QtWidgets/QFrame>
#include "utils/tlp.h"

QString TLPenumToString(TLPType value);

enum currentTab {
    sequenceExplorer,
    resultExplorer
};
class QLabel;
namespace Ui
{
    class TLPCard: public QFrame
    {
        Q_OBJECT
    public:
        explicit TLPCard(QWidget* parent = nullptr);
        explicit TLPCard(TLPType type, QWidget* parent = nullptr);
        explicit TLPCard(TLP* tlp, QWidget* parent = nullptr);
        void setCurrentTab(currentTab tab);
        ~TLPCard();
    public:
        TLP* tlp;
    private:
        void mouseMoveEvent(QMouseEvent* event);
        //void  mousePressEvent(QMouseEvent* event);
        void manageLayout();
       
    private:
        QLabel* textLabel_;
        TLPType tlpType;
        currentTab currentTab_ = currentTab::sequenceExplorer;
    };
}