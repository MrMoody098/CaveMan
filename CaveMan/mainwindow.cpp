#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Make the QTextEdit widget read-only
    ui->OutputBox->setReadOnly(true);
    // Initialize intro text and other variables
    introText = "Welcome to CaveMan's Descent!\n\n"
                "CaveMan, a fearless explorer of caves, finds himself plunging into darkness after slipping down a mineshaft during one of his usual adventures.\n\n"
                "Now trapped deep underground, he must fight his way past creatures using rock-paper-scissors combat, collect clues and items, and rely on his wits to escape.\n\n"
                "Armed with determination and a trusty rock, CaveMan faces the ultimate challenge: finding a way back to the surface before it's too late.\n";
    // Call the appendText function with the intro text
    appendText(introText,30);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::appendText(const QString &text, int delay) {
    // Create a QTimer object
    QTimer *timer = new QTimer(this);

    // Initialize currentIndex to keep track of the current character index
    currentIndex = 0;

    // Connect the timeout signal of the QTimer to a lambda function
    connect(timer, &QTimer::timeout, [=]() {
        // Check if currentIndex is within the text length
        if (currentIndex < text.length()) {
            // Append the current character to the OutputBox
            ui->OutputBox->insertPlainText(text.at(currentIndex));

            // Increment currentIndex for the next character
            currentIndex++;
        } else {
            // Stop the timer when the entire text has been appended
            timer->stop();

            // Delete the timer to clean up resources
            timer->deleteLater();
        }
    });

    // Start the QTimer with the specified delay
    timer->start(delay);
}
