#include "MainWindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupEditor();
    createActions();
    createMenus();
    createStatusBar();
    setWindowTitle("Simple Text Editor");
    resize(600, 400);
}

void MainWindow::setupEditor() {
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);
}

void MainWindow::createActions() {
    newAct = new QAction("&New", this);
    connect(newAct, &QAction::triggered, this, &MainWindow::newDocument);

    openAct = new QAction("&Open...", this);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction("&Save", this);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    saveAsAct = new QAction("Save &As...", this);
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveFileAs);

    exitAct = new QAction("E&xit", this);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    aboutAct = new QAction("&About", this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus() {
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    QMenu *helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAct);
}

void MainWindow::createStatusBar() {
    statusBar()->showMessage("Ready");
}

void MainWindow::newDocument() {
    currentFile.clear();
    textEdit->setText(QString());
    statusBar()->showMessage("New file");
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    QTextStream in(&file);
    QString text = in.readAll();
    textEdit->setText(text);
    file.close();
    statusBar()->showMessage("File opened: " + fileName);
}

void MainWindow::saveFile() {
    if (currentFile.isEmpty()) {
        saveFileAs();
    } else {
        QFile file(currentFile);
        if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
            return;
        }
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
        statusBar()->showMessage("File saved: " + currentFile);
    }
}

void MainWindow::saveFileAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    if (fileName.isEmpty())
        return;
    currentFile = fileName;
    saveFile();
}

void MainWindow::about() {
    QMessageBox::about(this, "About Simple Text Editor",
                       "This is a simple text editor built using Qt.");
}


