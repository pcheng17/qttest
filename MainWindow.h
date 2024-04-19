#pragma once

#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void newDocument();
    void openFile();
    void saveFile();
    void saveFileAs();
    void about();

private:
    void createActions();
    void createMenus();
    void createStatusBar();
    void setupEditor();

    QTextEdit *textEdit;
    QString currentFile;

    // Actions
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *aboutAct;
};

