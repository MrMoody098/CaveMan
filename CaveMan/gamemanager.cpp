#include "GameManager.h"
#include "mainwindow.h" // Include mainwindow.h to provide the full definition of Ui::MainWindow

GameManager::GameManager(Ui::MainWindow &ui, QObject *parent) : QObject(parent), ui(ui), currentRoom(nullptr) {}

GameManager::~GameManager() {}

void GameManager::initializeGame() {
    // Load the map image
    QPixmap image("C:/Users/ticta/OneDrive/Desktop/CaveManMap.png");
    ui.Map_2->setPixmap(image.scaled(ui.Map_2->size(), Qt::KeepAspectRatio));

    // Make the QTextEdit widget read-only
    ui.OutputBox->setReadOnly(true);

    // Initialize intro text and other variables
    introText = "Welcome to CaveMan's Descent!\n\n"
                "CaveMan, a fearless explorer of caves, finds himself plunging into darkness after slipping down a mineshaft during one of his usual adventures.\n\n"
                "Now trapped deep underground, he must fight his way past creatures using rock-paper-scissors combat, collect clues and items, and rely on his wits to escape.\n\n"
                "Armed with determination and a trusty rock, CaveMan faces the ultimate challenge: finding a way back to the surface before it's too late.\n";

    // Create rooms dynamically
    Room* roomA = new Room("A");
    Room* roomB = new Room("B");
    roomB->setDescription("A dusty hallway");
    roomB->addItem(new SkipStone(player));
    Room* roomC = new Room("C");
    roomC->setDescription("A large mineshaft at the end of the room there is a Chest.");
    Room* roomD = new Room("D");
    roomD->setDescription("A smelly cubbord there is a little spider in the corner.");
    roomD->addItem(new SkipStone(player));
    // Other room creations...

    currentRoom = roomA;
    // Set exits for each room
    // ...

    // Connect signals and slots
    connectSignalsAndSlots();

    // Initialize player stats and items
    player.setHealth(10);
    player.addCoins(1);
    HeartCrystal* hc = &heartCrystal;
    hc->setValues(1, 8, 8);
    player.addItem(hc);
    currentRoom->addItem(new HeartCrystal(player));
    currentRoom->addItem(new HeartCrystal(player));

    // Update UI
    appendText(introText, 10);
    updateStats();
    updatePlayerItemList();
    updateRoomItemList();
    ui->PlayerList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->RoomList->setSelectionMode(QAbstractItemView::SingleSelection);
}
