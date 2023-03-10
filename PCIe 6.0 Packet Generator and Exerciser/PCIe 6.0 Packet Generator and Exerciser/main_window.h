#pragma once
#include <QtWidgets/QMainWindow>

class QToolBar;

namespace Ui
{
    class ContentWidget;
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();
    private:
        void createContentWidget();
        void createToolBar();
        void manageLayout();

    private:
        QToolBar* toolBar_;
        ContentWidget* contentWidget_;
    };

}
