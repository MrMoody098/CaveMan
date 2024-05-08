#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"heartcrystal.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(),
    heartCrystal(player) {
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
    appendText(introText,10);
    QString health = QString::number(player.getHealth());
    QString coins = QString::number(player.getCoins());
    ui->Health->setText(health);
    ui->Coins->setText(coins);
    HeartCrystal* hc = &heartCrystal;
    hc->setValues(1,8,8);
    player.addItem(hc);
    // Set selection mode to allow only one item to be selected at a time
    ui->PlayerList->setSelectionMode(QAbstractItemView::SingleSelection);

    // Add items to the listWidget
    ui->PlayerList->addItem("HeartCrystal x"+QString::number(hc->getQuantity()));
    ui->PlayerList->addItem("Coins");
    ui->PlayerList->addItem("SkipStones");
    heartCrystal.use();
    ui->Health->setText(health);

    // Connect itemClicked signal to a slot for handling item selection changes
    connect(ui->PlayerList, &QListWidget::itemClicked, this, &MainWindow::handleSelectedItemChanged);
    connect(ui->UseButton, &QPushButton::clicked, this, &MainWindow::handleUseButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleSelectedItemChanged(QListWidgetItem *item)
 {
    if(item->text().contains("HeartCrystal"))
    {
        ui->UseButton->setStyleSheet("background-color: red; color: white;");
    }

    else
    {
        // Reset the color of the UseButton to its default
        ui->UseButton->setStyleSheet("");
        // Other actions you want to perform when another item is selected
    };

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

void MainWindow::updateList(){
    ui->PlayerList->clear();
    HeartCrystal* hc = &heartCrystal;
    // Add items to the listWidget
    ui->PlayerList->addItem("HeartCrystal x"+QString::number(hc->getQuantity()));
    ui->PlayerList->addItem("Coins");
    ui->PlayerList->addItem("SkipStones");
}

void MainWindow::handleUseButtonClicked()
{
    // Check if the HeartCrystal is selected in the list
    QListWidgetItem *selectedItem = ui->PlayerList->currentItem();
    if(selectedItem && selectedItem->text().contains("HeartCrystal"))
    {
        // Use the HeartCrystal
        heartCrystal.use();

        // Update the player's health displayed in the UI
        QString health = QString::number(player.getHealth());
        ui->Health->setText(health);

        // Handle item selection changes
        qDebug() << "Selected item:" << selectedItem->text();
        updateList();
    }
}

