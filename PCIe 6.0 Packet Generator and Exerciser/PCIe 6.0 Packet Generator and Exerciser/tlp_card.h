#pragma once

#include <QtWidgets/QFrame>

class QLabel;
namespace Ui
{
    class TLPCard: public QFrame
    {
        Q_OBJECT

    public:
        explicit TLPCard(QWidget* parent = nullptr, QString text = "");
        ~TLPCard();
    private:

        void manageLayout();
    private:
        QLabel* textLabel_;
    };
}