#pragma once
#include <QtWidgets/QFrame>

class QLabel;
namespace Ui
{
    class CustomLineEdit : public QFrame
    {
        Q_OBJECT

    public:
        explicit CustomLineEdit(QWidget* parent, QString text, int width, int height);
        ~CustomLineEdit();
    public: 
        QLineEdit* lineEdit;

    };
}