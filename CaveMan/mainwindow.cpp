#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "heartcrystal.h"
#include <QLabel>
#include <QPixmap>
#include "skipstone.h"
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
    roomB->setDescription("A dusty hallway");
    roomB->addItem(new SkipStone(player));
    Room* roomC = new Room("C");
    roomC->setDescription("A large mineshaft at the end of the room there is a Chest.");
    Room* roomD = new Room("D");
    roomD->setDescription("A smelly cubbord there is a little spider in the corner.");
    roomD->addItem(new SkipStone(player));


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

    connect(ui->PickupButton, &QPushButton::clicked, this, &MainWindow::PickupButtonClicked);
    connect(ui->RoomList, &QListWidget::itemClicked, this, &MainWindow::RoomSelectedItemChanged);

    connect(ui->PlayerList, &QListWidget::itemClicked, this, &MainWindow::SelectedItemChanged);

    connect(ui->UseButton, &QPushButton::clicked, this, &MainWindow::UseButtonClicked);

    connect(ui->DropButton, &QPushButton::clicked, this, &MainWindow::DropButtonClicked);

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
    currentRoom->addItem(new HeartCrystal(player));
    updateRoomItemList();
    // Set selection mode to allow only one item to be selected at a time
    ui->PlayerList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->RoomList->setSelectionMode(QAbstractItemView::SingleSelection);


}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::RoomSelectedItemChanged(QListWidgetItem *item){
    if(item->text().contains("HeartCrystal") )
    {
        ui->PickupButton->setStyleSheet("background-color: red; color: white;");
        qDebug() << item->text() ;
        // Reset the color of the UseButton to its default
        ui->UseButton->setStyleSheet("");
        ui->DropButton->setStyleSheet("");

    }

    else if(item->text().contains("SkipStone") )
    {
        ui->PickupButton->setStyleSheet("background-color: red; color: white;");
        qDebug() << item->text() ;

        // Reset the color of the UseButton to its default
        ui->UseButton->setStyleSheet("");
        ui->DropButton->setStyleSheet("");

    }

    else
    {
        // Reset the color of both buttons to their default
        ui->PickupButton->setStyleSheet("");
        ui->UseButton->setStyleSheet("");
        ui->DropButton->setStyleSheet("");

    };
}

void MainWindow::SelectedItemChanged(QListWidgetItem *item)
{
    if(item->text().contains("HeartCrystal") )
    {
        ui->UseButton->setStyleSheet("background-color: red; color: white;");
        ui->DropButton->setStyleSheet("background-color: red; color: white;");

        // Reset the color of the PickupButton to its default
        ui->PickupButton->setStyleSheet("");
    }

    else if(item->text().contains("SkipStone") )
    {
        ui->UseButton->setStyleSheet("background-color: red; color: white;");
        ui->DropButton->setStyleSheet("background-color: red; color: white;");

        // Reset the color of the PickupButton to its default
        ui->PickupButton->setStyleSheet("");
    }

    else
    {
        // Reset the color of both buttons to their default
        ui->UseButton->setStyleSheet("");
        ui->PickupButton->setStyleSheet("");
    };
}


void MainWindow::appendText(const QString &text, int delay) {
    // Disable buttons while displaying intro text
    setButtonsEnabled(false);

    // Create a QTimer object
    QTimer *timer = new QTimer(this);

    // used to keep track of current character index
    currentIndex = 0;
    ui->OutputBox->insertPlainText("\n");
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

            // Re-enable buttons after text display
            setButtonsEnabled(true);
        }
    });

    // Start the QTimer with the specified delay
    timer->start(delay);
}

void MainWindow::setButtonsEnabled(bool enabled) {
    ui->NorthButton->setEnabled(enabled);
    ui->SouthButton->setEnabled(enabled);
    ui->EastButton->setEnabled(enabled);
    ui->WestButton->setEnabled(enabled);
    ui->PickupButton->setEnabled(enabled);
    ui->UseButton->setEnabled(enabled);
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
        appendText(currentRoom->getDescription() + currentRoom->itemListToQString(),10);
        return true; // Return true to indicate successful direction change
    } else {
        qDebug() << "Cannot move in the specified direction.";
    }

    return false; // Return false if the direction change was unsuccessful
}


void MainWindow::UseButtonClicked()
{
    // Check if the UseButton is red
    QString buttonColor = ui->UseButton->styleSheet();
    if(buttonColor.contains("background-color: red"))
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
}


void MainWindow::DropButtonClicked()
{
    // Check if the DropButton is red
    QString buttonColor = ui->DropButton->styleSheet();
    if(buttonColor.contains("background-color: red")){
    QListWidgetItem *selectedItem = ui->PlayerList->currentItem();
    if(selectedItem)
        {
            // Retrieve the item's name
            QString itemName = selectedItem->text();
            int itemId=0;
            if(itemName.contains("HeartCrystal")){itemId=1;};
            if(itemName.contains("SkipStone")){itemId=2;};

            // Check if the selected item is a HeartCrystal
            if(itemId!=0)
            {
                //if room has a heartCrystal inc room heart crystal and dec player heartCrystal
                if(currentRoom->getItem(itemId)){
                    if(player.getItem(itemId)->getQuantity()==0){return;}
                    currentRoom->getItem(itemId)->incQuantity();
                    player.getItem(itemId)->decQuantity();
                }
                //else dec player heartCrystal by one and add a new heartCrystal object into the room
                else{
                    if(player.getItem(itemId)->getQuantity()==0){return;}

                        player.getItem(itemId)->decQuantity();
                        if(itemId=1){currentRoom->addItem(new HeartCrystal(player));};
                        if(itemId=2){currentRoom->addItem(new SkipStone(player));};

                }
            }
        }

    }
    // Update the item lists
    updatePlayerItemList();
    updateRoomItemList();
}



void MainWindow::PickupButtonClicked()
{
    // Check if the PickupButton is red
    QString buttonColor = ui->PickupButton->styleSheet();
    if(buttonColor.contains("background-color: red"))
    {
        // Check if an item is selected in the room list
        QListWidgetItem *selectedItem = ui->RoomList->currentItem();
        if(selectedItem)
        {
            // Retrieve the item's name
            QString itemName = selectedItem->text();
            // Check if the selected item is a HeartCrystal
            if(itemName.contains("HeartCrystal"))
            {
                // Find the HeartCrystal in the room and add it to the player's inventory
                Item* heartCrystal = currentRoom->getItem(1);
                if(heartCrystal)
                {
                    if(player.getItem(1)->getQuantity()==0){player.addItem(heartCrystal);currentRoom->removeItem(heartCrystal->getId());}
                    else{
                    {
                        heartCrystal->decQuantity();
                        player.getItem(1)->incQuantity();
                    }
                    if(heartCrystal->getQuantity()==0){currentRoom->removeItem(heartCrystal->getId());};
                    }
                    // Update the item lists
                    updateStats();
                    updatePlayerItemList();
                    updateRoomItemList();
                }
            }
            else if(itemName.contains("SkipStone"))
            {
                // Find the SkipStone in the room
                Item* skipStone = currentRoom->getItem(2);
                if(skipStone)
                {
                    // Add the SkipStone to the player's inventory
                    player.addItem(new SkipStone(player));
                    updateStats();
                    // Decrement the SkipStone's quantity in the room if it's greater than 0
                    if(skipStone->getQuantity() > 0)
                    {
                        skipStone->decQuantity();
                    }
                    if(skipStone->getQuantity()==0){currentRoom->removeItem(skipStone->getId());};
                    // Update the item lists
                    updatePlayerItemList();
                    updateRoomItemList();
                }
            }
        }
    }
}

