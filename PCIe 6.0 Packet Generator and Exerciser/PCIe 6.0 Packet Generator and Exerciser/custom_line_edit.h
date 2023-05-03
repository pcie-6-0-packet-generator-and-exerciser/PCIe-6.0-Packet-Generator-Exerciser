#pragma once
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <Qtwidgets/QLineEdit>

class QLabel;
namespace Ui
{
    class CustomLineEdit : public QFrame
    {
        Q_OBJECT

    public:
        explicit CustomLineEdit(const QString &labelText, int width, int height, const QString &content, QWidget* parent );
        ~CustomLineEdit();
    public:
        QLineEdit* lineEdit;
        QLabel* label;
        QVBoxLayout* layout;

    };
}