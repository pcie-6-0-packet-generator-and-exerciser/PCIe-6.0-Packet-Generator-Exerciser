#pragma once

#include <QtWidgets/QFrame>

class QPushButton;
namespace Ui
{
    class ContentWidget: public QFrame
    {
        Q_OBJECT

    public:
        ContentWidget(QWidget* parent = nullptr);
        ~ContentWidget();
    private:
        void createHeader();
        void createBody();
        void manageLayout();
    private:
        QFrame* header_;
        QFrame* body_;
    };
}