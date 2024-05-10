#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "heartcrystal.h"
#include <QLabel>
#include <QPixmap>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(),
    heartCrystal(player),
    currentRoom(nullptr) { // Initialize currentRoom pointer to nullptr
    ui->setupUi(this);
    //add a pointer to the heartCrystal

    // Load the map image
    QPixmap image("C:/Users/ticta/OneDrive/Desktop/CaveManMap.png");

    // Set the scaled image to the QLabel
    ui->Map_2->setPixmap(image.scaled(ui->Map_2->size(), Qt::KeepAspectRatio));

    // Make the QTextEdit widget read-only
    ui->OutputBox->setReadOnly(true);

    // Initialize intro text and other variables
    introText = "Welcome to CaveMan's Descent!\n\n"
                "CaveMan, a fearless explorer of caves, finds himself plunging into darkness after slipping down a mineshaft during one of his usual adventures.\n\n"
                "Now trapped deep underground, he must fight his way past creatures using rock-paper-scissors combat, collect clues and items, and rely on his wits to escape.\n\n"
                "Armed with determination and a trusty rock, CaveMan faces the ultimate challenge: finding a way back to the surface before it's too late.\n";

    // Initialize current room to point to roomA

    // Create rooms dynamically
    Room* roomA = new Room("A");
    Room* roomB = new Room("B");
    Room* roomC = new Room("C");
    Room* roomD = new Room("D");
    Room* roomE = new Room("E");
    Room* roomF = new Room("F");
    Room* roomG = new Room("G");
    Room* roomH = new Room("H");
    Room* roomI = new Room("I");
    Room* roomJ = new Room("J");
    Room* roomK = new Room("K");
    Room* roomL = new Room("L");
    Room* roomM = new Room("M");
    Room* roomN = new Room("N");







    currentRoom = roomA;
    // Set exits for each room
    roomA->setExits(nullptr, nullptr, roomB, nullptr);
    roomB->setExits(roomA, nullptr, roomC, nullptr);
    roomC->setExits(roomB, roomF, roomE, roomD);
    roomD->setExits(nullptr, roomC, nullptr, nullptr);
    roomE->setExits(roomC, roomL, nullptr, nullptr);
    roomF->setExits(nullptr, nullptr, roomG, roomC);
    roomG->setExits(roomF, roomH, nullptr, nullptr);
    roomH->setExits(roomI, roomJ, roomG, nullptr);
    roomI->setExits(nullptr, nullptr, roomH, nullptr);
    roomJ->setExits(nullptr, roomM, roomK, roomH);
    roomK->setExits(roomJ,nullptr,roomL,nullptr);
    roomL->setExits(roomK,nullptr,nullptr,roomE);
    roomM->setExits(roomJ,nullptr,roomN,nullptr);
    roomN->setExits(roomM,nullptr,nullptr,nullptr);



    // Connect signals and slots
    connect(ui->NorthButton, &QPushButton::clicked, this, [this]() {
        if (goDirection("NORTH")) {
            updateCurrentRoom();
        }
    });

    connect(ui->SouthButton, &QPushButton::clicked, this, [this]() {
        if (goDirection("SOUTH")) {
            updateCurrentRoom();
        }
    });

    connect(ui->EastButton, &QPushButton::clicked, this, [this]() {
        if (goDirection("EAST")) {
            updateCurrentRoom();
        }
    });

    connect(ui->WestButton, &QPushButton::clicked, this, [this]() {
        if (goDirection("WEST")) {
            updateCurrentRoom();
        }
    });

    // Call the appendText function with the intro text
    player.setHealth(10);
    player.addCoins(1);
    appendText(introText, 10);
    updateStats();
    HeartCrystal* hc = &heartCrystal;
    hc->setValues(1, 8, 8);
    player.addItem(hc);
    updatePlayerItemList();
    currentRoom->addItem(new HeartCrystal(player));
    updateRoomItemList();
    // Set selection mode to allow only one item to be selected at a time
    ui->PlayerList->setSelectionMode(QAbstractItemView::SingleSelection);


    // Connect itemClicked signal to a slot for handling item selection changes
    connect(ui->PlayerList, &QListWidget::itemClicked, this, &MainWindow::SelectedItemChanged);
    connect(ui->UseButton, &QPushButton::clicked, this, &MainWindow::UseButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SelectedItemChanged(QListWidgetItem *item)
{
    if(item->text().contains("HeartCrystal") )
    {
        ui->UseButton->setStyleSheet("background-color: red; color: white;");
    }

    else if(item->text().contains("SkipStone") )
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

void MainWindow::updateRoomItemList(){
    ui->RoomList->clear();
    for(Item* i:currentRoom->getItems()){
        QString name = i->getName();
        QString quantity = QString::number(i->getQuantity());
        ui->RoomList->addItem(name+" x"+quantity);
    }
}

void MainWindow::updatePlayerItemList(){
    ui->PlayerList->clear();
    for(Item* i:player.getItems()){
        QString name = i->getName();
        QString quantity = QString::number(i->getQuantity());
        ui->PlayerList->addItem(name+" x"+quantity);
    }
}

void MainWindow::updateStats(){
    QString health = QString::number(player.getHealth());
    QString coins = QString::number(player.getCoins());
    ui->Health->setText(health);
    ui->Coins->setText(coins);

}

void MainWindow::updateCurrentRoom() {
    if (currentRoom != nullptr) {
        ui->CurrentRoom->setText(currentRoom->getName());
    } else {
        qDebug() << "Current room is null!";
    }
}

bool MainWindow::goDirection(QString direction) {
    qDebug() << "Direction: " << direction;
    if (currentRoom == nullptr) {
        qDebug() << "Current room is null!";
        return false;
    }

    Room* nextRoom = nullptr;

    if (direction == "NORTH" && currentRoom->getNorth() != nullptr) {
        nextRoom = currentRoom->getNorth();
        qDebug() << "Next room to the NORTH exists.";
    } else if (direction == "SOUTH" && currentRoom->getSouth() != nullptr) {
        nextRoom = currentRoom->getSouth();
        qDebug() << "Next room to the SOUTH exists.";
    } else if (direction == "EAST" && currentRoom->getEast() != nullptr) {
        nextRoom = currentRoom->getEast();
        qDebug() << "Next room to the EAST exists.";
    } else if (direction == "WEST" && currentRoom->getWest() != nullptr) {
        nextRoom = currentRoom->getWest();
        qDebug() << "Next room to the WEST exists.";
    } else {
        qDebug() << "No valid exit in the specified direction or current room is null.";
    }

    if (nextRoom != nullptr) {
        currentRoom = nextRoom;
        updateCurrentRoom();        // Update the UI to display the new current room
        updateRoomItemList();
        return true; // Return true to indicate successful direction change
    } else {
        qDebug() << "Cannot move in the specified direction.";
    }

    return false; // Return false if the direction change was unsuccessful
}




void MainWindow::UseButtonClicked()
{
    // Check if the HeartCrystal is selected in the list
    QListWidgetItem *selectedItem = ui->PlayerList->currentItem();
    if(selectedItem && selectedItem->text().contains("HeartCrystal"))
    {
        // Use the HeartCrystal
        player.getItem(1)->use();
        updateStats();
        // Handle item selection changes
        qDebug() << "Selected item:" << selectedItem->text();
        updatePlayerItemList();
    }
}
