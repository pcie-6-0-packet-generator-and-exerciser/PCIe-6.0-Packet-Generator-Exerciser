#pragma once

#include <QtWidgets/QFrame>
#include "utils/queue_wrapper.h"
#include "utils/queue_wrapper.cpp"
class TLP;
class QPushButton;
class QVBoxLayout;

namespace Ui
{
    class SequenceBrowser;
    class ContentWidget: public QFrame
    {
        Q_OBJECT

    public:
        explicit ContentWidget(QWidget* parent, 
            QueueWrapper<TLP*>* rootComplexToLayers,
            QueueWrapper<TLP*>* layersToRootComplex);
        ~ContentWidget();
    private:
        void createHeader();
        void createBody();
        void createFooter();
        void createSequenceExplorerTab();
        void createResultExplorerTab();
        void createSubmitButton();
        void manageLayout();
    public Q_SLOTS:
        void onSubmitButtonClick();
        void onSequenceExplorerTabClick();
        void onResultExplorerTabClick();
    private:
        QueueWrapper<TLP*>* rootComplexToLayers_;
        QueueWrapper<TLP*>* layersToRootComplex_;
        QFrame* header_;
        QFrame* body_;
        QFrame* footer_;
        QFrame* typeFrame_;
        QFrame* resultFrame_;
        SequenceBrowser* sequenceBrowser_;
        QPushButton* submitButton_;
        QPushButton* sequenceExplorerTab_;
        QPushButton* resultExplorerTab_;
    };
}