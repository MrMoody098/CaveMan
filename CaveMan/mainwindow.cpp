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
    player.setHealth(10);
    appendText(introText,30);
    QString health = QString::number(player.getHealth());
    QString coins = QString::number(player.getCoins());
    ui->Health->setText(health);
    ui->Coins->setText(coins);


    // Set selection mode to allow only one item to be selected at a time
    ui->PlayerList->setSelectionMode(QAbstractItemView::SingleSelection);

    // Add items to the listWidget
    ui->PlayerList->addItem("Item 1");
    ui->PlayerList->addItem("Item 2");
    ui->PlayerList->addItem("Item 3");

    // Connect itemClicked signal to a slot for handling item selection changes
    connect(ui->PlayerList, &QListWidget::itemClicked, this, &MainWindow::handleSelectedItemChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleSelectedItemChanged(QListWidgetItem *item)
{
    // Handle item selection changes here
    qDebug() << "Selected item:" << item->text();
}

//This Method is used to append Text Character By Character
void MainWindow::appendText(const QString &text, int delay) {
    // Create a QTimer object
    QTimer *timer = new QTimer(this);

    // used to keep track of current character index
    currentIndex = 0;

    // Connect the timeout signal of the QTimer to a lambda function
    connect(timer, &QTimer::timeout, [=]() {
        // Check if currentIndex is within the text length
        if (currentIndex < text.length()) {
            // Append the current character to the OutputBox
            ui->OutputBox->insertPlainText(text.at(currentIndex));

            // Increment currentIndex
            currentIndex++;
        } else {
            // Stop the timer when text has been appended
            timer->stop();

            // Delete timer to clean up resources
            timer->deleteLater();
        }
    });

    // Start the QTimer with the specified delay
    timer->start(delay);
}
