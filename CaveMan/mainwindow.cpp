#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "heartcrystal.h"
#include <QLabel>
#include <QPixmap>
#include "skipstone.h"
#include <QScrollBar>
#include <QRandomGenerator>
using namespace std;
int APPEND_TIME =10;
bool fto = true;
bool &fightOver = fto;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(),
    heartCrystal(player),
    currentRoom(nullptr),
    lastRoom(nullptr){

    ui->setupUi(this);

    ui->OutputBox->setReadOnly(true);
    ui->OutputBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    setupRooms();
    setupConnections();
    initialiseGameState();

    QString introText = "Welcome to CaveMan's Descent!\n\n"
                        "CaveMan, a fearless explorer of caves, finds himself plunging into darkness after slipping down a mineshaft during one of his usual adventures.\n\n"
                        "Now trapped deep underground, he must fight his way past creatures using rock-paper-scissors combat, collect clues and items, and rely on his wits to escape.\n\n"
                        "Armed with determination and a trusty rock, CaveMan faces the ultimate challenge: finding a way back to the surface before it's too late.\n";

    appendText(introText, APPEND_TIME);


}
void MainWindow::initialiseGameState(){
    // Call the appendText function with the intro text
    player.setHealth(10);
    player.addCoins(1);
    updateStats();
    HeartCrystal* hc = &heartCrystal;
    hc->setValues(1, 8, 8);
    player+hc;
    updatePlayerItemList();
    currentRoom->addItem(new HeartCrystal(player));
    currentRoom->addItem(new HeartCrystal(player));
    currentRoom->addItem(new SkipStone(fightOver,this));
    updateRoomItemList();
    // Set selection mode to allow only one item to be selected at a time
    ui->PlayerList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->RoomList->setSelectionMode(QAbstractItemView::SingleSelection);
    updateDirectionButtons();

    DEBUG_LOG("game initialised.");

}
void MainWindow::setupConnections(){
    // Connect signals and slots

    connect(ui->PickupButton, &QPushButton::clicked, this, &MainWindow::pickupButtonClicked);
    connect(ui->RoomList, &QListWidget::itemClicked, this, &MainWindow::roomSelectedItemChanged);

    connect(ui->PlayerList, &QListWidget::itemClicked, this, &MainWindow::selectedItemChanged);

    connect(ui->UseButton, &QPushButton::clicked, this, &MainWindow::useButtonClicked);

    connect(ui->DropButton, &QPushButton::clicked, this, &MainWindow::dropButtonClicked);

    connect(ui->InspectButton, &QPushButton::clicked, this, &MainWindow::inspectButtonClicked);

    connect(ui->FightButton, &QPushButton::clicked, this, &MainWindow::fight);
    connect(ui->FleeButton, &QPushButton::clicked, this, &MainWindow::flee);
    // Connect the clicked signals of radio buttons to slots
    connect(ui->RockButton, &QPushButton::clicked, this, &MainWindow::onRockSelected);
    connect(ui->PaperButton_3, &QPushButton::clicked, this, &MainWindow::onPaperSelected);
    connect(ui->ScissorsButton, &QPushButton::clicked, this, &MainWindow::onScissorsSelected);

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
    DEBUG_LOG("Connections setup complete.");

}
void MainWindow::setupRooms(){
    // Create rooms dynamically and store them in the array
    rooms[0] = new Room("A");
    rooms[1] = new Room("B");
    rooms[2] = new Room("C");
    rooms[3] = new Room("D");
    rooms[4] = new Room("E");
    rooms[5] = new Room("F");
    rooms[6] = new Room("G");
    rooms[7] = new Room("H");
    rooms[8] = new Room("I");
    rooms[9] = new Room("J");
    rooms[10] = new Room("K");
    rooms[11] = new Room("L");
    rooms[12] = new Room("M");
    rooms[13] = new Room("N");

    rooms[1]->setDescription("A dusty hallway");
    rooms[1]->addItem(new SkipStone(fightOver, this));

    rooms[2]->setDescription("A large mineshaft.");
    Enemy* roomCEnemy = new Enemy("Chris the cryptid", "\n a legendary creature rumored to lurk in the depths of dark forests and misty swamps.");
    roomCEnemy->addItem(new HeartCrystal(player));
    roomCEnemy->addItem(new HeartCrystal(player));
    roomCEnemy->setHealth(2);
    rooms[2]->setEnemy(roomCEnemy);
    qDebug() << rooms[2]->enemyInRoom();

    rooms[3]->setDescription("A smelly cupboard with a little spider in the corner.");
    rooms[3]->addItem(new SkipStone(fightOver, this));

    currentRoom = rooms[0];

    // Set exits for each room
    rooms[0]->setExits(nullptr, nullptr, rooms[1], nullptr);
    rooms[1]->setExits(rooms[0], nullptr, rooms[2], nullptr);
    rooms[2]->setExits(rooms[1], rooms[5], rooms[4], rooms[3]);
    rooms[3]->setExits(nullptr, rooms[2], nullptr, nullptr);
    rooms[4]->setExits(rooms[2], rooms[11], nullptr, nullptr);
    rooms[5]->setExits(nullptr, nullptr, rooms[6], rooms[2]);
    rooms[6]->setExits(rooms[5], rooms[7], nullptr, nullptr);
    rooms[7]->setExits(rooms[8], rooms[9], rooms[6], nullptr);
    rooms[8]->setExits(nullptr, nullptr, rooms[7], nullptr);
    rooms[9]->setExits(nullptr, rooms[12], rooms[10], rooms[7]);
    rooms[10]->setExits(rooms[9], nullptr, rooms[11], nullptr);
    rooms[11]->setExits(rooms[10], nullptr, nullptr, rooms[4]);
    rooms[12]->setExits(rooms[9], nullptr, rooms[13], nullptr);
    rooms[13]->setExits(rooms[12], nullptr, nullptr, nullptr);

    DEBUG_LOG("Setup rooms complete.");

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::roomSelectedItemChanged(QListWidgetItem *item){
    if(item->text().contains("HeartCrystal") )
    {
        ui->PickupButton->setStyleSheet("background-color: red; color: white;");
        qDebug() << item->text() ;
        // Reset the color of the UseButton to its default
        ui->UseButton->setStyleSheet("");
        ui->DropButton->setStyleSheet("");
        ui->InspectButton->setStyleSheet("");


    }

    else if(item->text().contains("SkipStone") )
    {
        ui->PickupButton->setStyleSheet("background-color: red; color: white;");
        qDebug() << item->text() ;

        // Reset the color of the UseButton to its default
        ui->UseButton->setStyleSheet("");
        ui->DropButton->setStyleSheet("");
        ui->InspectButton->setStyleSheet("");


    }

    else
    {
        ui->InspectButton->setStyleSheet("");
        // Reset the color of both buttons to their default
        ui->PickupButton->setStyleSheet("");
        ui->UseButton->setStyleSheet("");
        ui->DropButton->setStyleSheet("");

    };
}

void MainWindow::selectedItemChanged(QListWidgetItem *item)
{
    if(item->text().contains("HeartCrystal") )
    {
        ui->InspectButton->setStyleSheet("background-color: red; color: white;");

        ui->UseButton->setStyleSheet("background-color: red; color: white;");
        ui->DropButton->setStyleSheet("background-color: red; color: white;");

        // Reset the color of the PickupButton to its default
        ui->PickupButton->setStyleSheet("");
    }

    else if(item->text().contains("SkipStone") )
    {
        ui->InspectButton->setStyleSheet("background-color: red; color: white;");
        if(!fightOver)ui->UseButton->setStyleSheet("background-color: red; color: white;");

        ui->DropButton->setStyleSheet("background-color: red; color: white;");

        // Reset the color of the PickupButton to its default
        ui->PickupButton->setStyleSheet("");
    }

    else
    {
        ui->InspectButton->setStyleSheet("");
        ui->DropButton->setStyleSheet("");
        // Reset the color of both buttons to their default
        ui->UseButton->setStyleSheet("");
        ui->PickupButton->setStyleSheet("");
    };
}

void MainWindow::appendText(const QString &text) {
    // Disable buttons while displaying text
    setButtonsEnabled(false);

    // Create a QTimer object
    QTimer *timer = new QTimer(this);

    // Connect the timeout signal of the QTimer to a lambda function
    connect(timer, &QTimer::timeout, [=]() {
        // Append the entire text to the OutputBox
        ui->OutputBox->insertPlainText("\n" + text);

        // Scroll to the bottom
        QScrollBar *vScrollBar = ui->OutputBox->verticalScrollBar(); // Get the vertical scroll bar
        vScrollBar->setValue(vScrollBar->maximum()); // Scroll to the bottom

        // Stop the timer
        timer->stop();

        // Delete timer to clean up resources
        timer->deleteLater();

        // Re-enable buttons after text display
        setButtonsEnabled(true);
    });

    // Start the QTimer with a 1-second delay
    timer->start(1000);
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
            //scroll every 35 characters
            if (currentIndex % 35 == 0) {
                QScrollBar *vScrollBar = ui->OutputBox->verticalScrollBar(); // Get the vertical scroll bar
                vScrollBar->setValue(vScrollBar->maximum()); // Scroll to the bottom
            }
            // Increment currentIndex
            currentIndex++;
        } else {
            // Stop the timer when text has been appended
            timer->stop();

            // Delete timer to clean up resources
            timer->deleteLater();

            // Re-enable buttons after text display
            setButtonsEnabled(true);

            QScrollBar *vScrollBar = ui->OutputBox->verticalScrollBar(); // Get the vertical scroll bar
            vScrollBar->setValue(vScrollBar->maximum()); // Scroll to the bottom
        }
    });

    // Start the QTimer with the specified delay
    timer->start(delay);

}

void MainWindow::setButtonsEnabled(bool enabled) {
    if(fighting){
    ui->NorthButton->setEnabled(enabled);

    ui->SouthButton->setEnabled(enabled);

    ui->EastButton->setEnabled(enabled);

    ui->WestButton->setEnabled(enabled);
}
    ui->RockButton->setEnabled(enabled);

    ui->ScissorsButton->setEnabled(enabled);

    ui->PaperButton_3->setEnabled(enabled);

    ui->PickupButton->setEnabled(enabled);
    ui->PickupButton->setStyleSheet(enabled ? "" : "background-color: grey;");

    ui->UseButton->setEnabled(enabled);
    ui->UseButton->setStyleSheet(enabled ? "" : "background-color: grey;");

    ui->InspectButton->setEnabled(enabled);
    ui->InspectButton->setStyleSheet(enabled ? "" : "background-color: grey;");

    ui->DropButton->setEnabled(enabled);
    ui->DropButton->setStyleSheet(enabled ? "" : "background-color: grey;");
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
    if(!fightOver) ui->EnemyHealth->setText(QString::number(currentRoom->getEnemy()->getHealth()));
}

void MainWindow::updateCurrentRoom() {
    if (currentRoom != nullptr) {
        ui->CurrentRoom->setText(currentRoom->getName());

    } else {
        qDebug() << "Current room is null!";
    }
}

void MainWindow::updateDirectionButtons(){
    //NORTH
    if(currentRoom->getNorth()!=nullptr){
        ui->NorthButton->setStyleSheet("background-color: #FFCCCC; border-radius: 10px;");
    }
    else if(currentRoom->getNorth()==nullptr){
        ui->NorthButton->setStyleSheet("");
    };
    //SOUTH
    if(currentRoom->getSouth()!=nullptr){
        ui->SouthButton->setStyleSheet("background-color: #FFCCCC; border-radius: 10px");
    }
    else if(currentRoom->getSouth()==nullptr){
        ui->SouthButton->setStyleSheet("");
    };
    //EAST
    if(currentRoom->getEast()!=nullptr){
        ui->EastButton->setStyleSheet("background-color: #FFCCCC; border-radius: 10px");
    }
    else if(currentRoom->getEast()==nullptr){
        ui->EastButton->setStyleSheet("");
    };
    //WEST
    if(currentRoom->getWest()!=nullptr){
        ui->SouthButton->setStyleSheet("background-color: #FFCCCC; border-radius: 10px");
    }
    else if(currentRoom->getWest()==nullptr){
        ui->SouthButton->setStyleSheet("");
    };

}

bool MainWindow::goDirection(QString direction) {
    qDebug() << "Direction: " << direction;
    if (currentRoom == nullptr) {
        qDebug() << "Current room is null!";
        return false;
    }

    Room* nextRoom = nullptr;
    lastRoom = currentRoom;
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
        if(currentRoom->enemyInRoom()){
            qDebug() <<"enemy found";
            Enemy *Enemy = currentRoom->getEnemy();
            appendText(currentRoom->getDescription() + currentRoom->itemListToQString()+"\n"+Enemy->getName()+" "+Enemy->getDescription()+"\n",APPEND_TIME);
            challenge(true);
        }
        else{
            appendText(currentRoom->getDescription() + currentRoom->itemListToQString(),10);
        }
        return true; // Return true to indicate successful direction change
    } else {
        qDebug() << "Cannot move in the specified direction.";
    }

    return false; // Return false if the direction change was unsuccessful
}


void MainWindow::useButtonClicked()
{

    // Check if the UseButton is red
    QString buttonColor = ui->UseButton->styleSheet();
    if(buttonColor.contains("background-color: red"))
    {
        int itemId =0;
        // Check if the HeartCrystal is selected in the list
        QListWidgetItem *selectedItem = ui->PlayerList->currentItem();
        if(selectedItem && selectedItem->text().contains("HeartCrystal")){ itemId =1;}
        else if(selectedItem && selectedItem->text().contains("SkipStone")){ itemId =2;}
        if(itemId)
        {
            // Use the Item
            player.getItem(itemId)->use();
            updateStats();
            // Handle item selection changes
            qDebug() << "Selected item:" << selectedItem->text();
            updatePlayerItemList();
        }
    }
}


void MainWindow::dropButtonClicked()
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
                        if(itemId==1){currentRoom->addItem(new HeartCrystal(player));};
                        if(itemId==2){currentRoom->addItem(new SkipStone(fightOver,this));};

                }
            }
        }

    }
    // Update the item lists
    updatePlayerItemList();
    updateRoomItemList();
}


void MainWindow::inspectButtonClicked() {
    // Check if the InspectButton is red
    QString buttonColor = ui->InspectButton->styleSheet();
    if (buttonColor.contains("background-color: red")) {
        QListWidgetItem *selectedItem = ui->PlayerList->currentItem();
        if (selectedItem) {
            // Retrieve the item's name
            QString itemName = selectedItem->text();
            int itemId = 0;
            if (itemName.contains("HeartCrystal")) { itemId = 1; }
            else if (itemName.contains("SkipStone")) { itemId = 2; }

            // Check if the selected item is valid
            if (itemId != 0) {
                QString description;
                    // Try to get the item from the player's inventory
                    Item* item = player.getItem(itemId);
                    if (item)
                    {
                        description = item->getDescription();
                    }
                    else
                    {
                        description = "Item not found in the player's inventory.";
                    }
            appendText(description, APPEND_TIME);

                }
            }
        }
}


void MainWindow::flee(){
    // Check if the InspectButton is red
    QString buttonColor = ui->FleeButton->styleSheet();
    if (buttonColor.contains("background-color: red")) {
        currentRoom = lastRoom;
        updateCurrentRoom();        // Update the UI to display the new current room
        updateRoomItemList();
        appendText(currentRoom->getDescription() + currentRoom->itemListToQString(),10);
        fighting = false;
        challenge(false);

        ui->stackedWidget->setCurrentIndex(0);
    }
}


void MainWindow::fight(){
    fightOver = false;
    fighting = true;
    Enemy* enemy = currentRoom->getEnemy();
    QString output ="\n\n------------------\n\n"+enemy->getName()+": \"On the Count of Three Shoot\"";
    appendText(output,APPEND_TIME);
    qDebug()<<"fighting";
    ui->stackedWidget->setCurrentIndex(1);
    ui->FightButton->setEnabled(false);
    ui->FightButton->setStyleSheet("background-color: grey;");
    updateStats();
}
void MainWindow::challenge(bool condition) {
    // Check the condition
    if (condition) {
        // Disable movement buttons
        ui->NorthButton->setEnabled(false);
        ui->SouthButton->setEnabled(false);
        ui->EastButton->setEnabled(false);
        ui->WestButton->setEnabled(false);

        // Enable and change color of flee and fight buttons
        ui->FleeButton->setEnabled(true);
        ui->FleeButton->setStyleSheet("background-color: red;");

        ui->FightButton->setEnabled(true);
        ui->FightButton->setStyleSheet("background-color: red;");
    } else {
        // Enable movement buttons
        ui->NorthButton->setEnabled(true);
        ui->SouthButton->setEnabled(true);
        ui->EastButton->setEnabled(true);
        ui->WestButton->setEnabled(true);

        // Disable and reset color of flee and fight buttons
        ui->FleeButton->setEnabled(false);
        ui->FleeButton->setStyleSheet("background-color: grey;");

        ui->FightButton->setEnabled(false);
        ui->FightButton->setStyleSheet("background-color: grey;");
    }
}

void MainWindow::pickupButtonClicked()
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
                    player.addItem(new SkipStone(fightOver,this));
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

void MainWindow::onRockSelected() {
    int playerChoice = 1;
    handlePlayerChoice(playerChoice);
}

void MainWindow::onPaperSelected() {
    int playerChoice = 0;
    handlePlayerChoice(playerChoice);
}

void MainWindow::onScissorsSelected() {
    int playerChoice = 2;
    handlePlayerChoice(playerChoice);
}

QString MainWindow::determineWinner(int playerChoice, int enemyChoice) {
    int result = (playerChoice - enemyChoice + 3) % 3;
    if (result == 0) {
        return "It's a tie!";
    } else if (result == 1) {
        return "Player wins!";
    } else {
        return "Enemy wins!";
    }
}

void MainWindow::handlePlayerChoice(int playerChoice) {
    int enemyChoice = QRandomGenerator::global()->bounded(3);
    QString result = determineWinner(playerChoice, enemyChoice);

    appendText("-----------\nPlayer chose: " + choiceToString(playerChoice) + "\n"+"Enemy chose: " + choiceToString(enemyChoice) + "\n"+result + "\n----------\n",APPEND_TIME);

    if (result == "Player wins!") {
        currentRoom->getEnemy()->subtractHealth(1); //
        updateStats();
        if (currentRoom->getEnemy()->getHealth() <= 0) {
            enemyDead();
        }
    } else if (result == "Enemy wins!") {
        player.subtractHealth(1);
        updateStats();
        if (player.getHealth() <= 0) {
            appendText("You have been defeated this round!\n");
            gameOver();
        }
    }
}

void MainWindow::enemyDead(){

    Enemy* enemy =currentRoom->getEnemy();
    //print you have defeated {enemy} they have dropped {itmes}
    std::vector<Item*> itemsToDrop = enemy->getItems(); // Collect items before modifying the enemy
    QString output = "You have Defeated" + enemy->getName()+ "\nThe enemy Dropped these items:\n";

    for (Item* i : itemsToDrop) {
        output += i->getName() + " x" + QString::number(i->getQuantity()) + "\n";
        Item* copiedItem = new Item(*i); // Create a copy using the copy constructor
        currentRoom->addItem(copiedItem);
    }
    delete enemy;
    fightOver=true;
    currentRoom->setEnemy(nullptr);
    challenge(false);
    ui->stackedWidget->setCurrentIndex(0);
    updateStats();
    updateRoomItemList();
    setButtonsEnabled(true);
    appendText(output);
}

QString MainWindow::choiceToString(int choice) {
    switch (choice) {
    case 0: return "Paper";
    case 1: return "Rock";
    case 2: return "Scissors";
    default: return "";
    }
}

void MainWindow::gameOver(){
    appendText("you DIED!!! game OVER!");
    fightOver=true;
}

