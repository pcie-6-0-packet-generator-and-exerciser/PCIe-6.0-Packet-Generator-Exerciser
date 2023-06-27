#pragma once
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <Qtwidgets/QPlainTextEdit>

class QLabel;
class QPlainTextEdit;
namespace Ui
{
    class CustomLineEdit : public QFrame
    {
        Q_OBJECT

    public:
        explicit CustomLineEdit(const QString &labelText, int width, int height, const QString &content, QWidget* parent , bool readOnly = true);
        ~CustomLineEdit();
        void setScrollBarEnabled(bool enabled);
    public:
        //QLineEdit* lineEdit;
        QPlainTextEdit* lineEdit;
        QLabel* label;
        QVBoxLayout* layout;
    
    };
}