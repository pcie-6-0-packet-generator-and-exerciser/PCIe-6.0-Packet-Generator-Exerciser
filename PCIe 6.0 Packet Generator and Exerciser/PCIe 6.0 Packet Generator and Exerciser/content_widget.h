#pragma once

#include <QtWidgets/QFrame>

class QPushButton;

namespace Ui
{
    class ContentWidget: public QFrame
    {
        Q_OBJECT

    public:
        explicit ContentWidget(QWidget* parent = nullptr);
        ~ContentWidget();
    private:
        void createHeader();
        void createBody();
        void createFooter();
        void createSubmitButton();
        void manageLayout();
    private:
        QFrame* header_;
        QFrame* body_;
        QFrame* footer_;
        QPushButton* submitButton_;
    };
}