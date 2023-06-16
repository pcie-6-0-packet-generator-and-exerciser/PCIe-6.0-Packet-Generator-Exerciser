#pragma once

#include <QtWidgets/QFrame>
#include "utils/queue_wrapper.h"
class TLP;
class Type1Config;
class QPushButton;
class QVBoxLayout;

namespace Ui
{
    class ConfigSpaceWidget;
    class SequenceBrowser;
    class ResultBrowser;
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
        void createConfigSpaceButton();
    public Q_SLOTS:
        void onSubmitButtonClick();
        void onSequenceExplorerTabClick();
        void onResultExplorerTabClick();
        void onConfigSpaceButtonClick();
    private:
        QueueWrapper<TLP*>* rootComplexToLayers_;
        QueueWrapper<TLP*>* layersToRootComplex_;
        QFrame* header_;
        QFrame* body_;
        QFrame* footer_;
        QFrame* typeFrame_;
        QFrame* resultFrame_;
        SequenceBrowser* sequenceBrowser_;
        ResultBrowser* resultBrowser_;
        QPushButton* submitButton_;
        QPushButton* sequenceExplorerTab_;
        QPushButton* resultExplorerTab_;
        QPushButton* configSpaceButton_;
        Type1Config* type1Config_;
        ConfigSpaceWidget* configSpaceWidget_ = nullptr;
    };
}