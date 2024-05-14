#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include "Room.h"
#include "Player.h"
#include "HeartCrystal.h"
#include "SkipStone.h"
#include "mainwindow.h"

class GameManager : public QObject {
    Q_OBJECT
public:
    explicit GameManager(Ui::MainWindow &ui, QObject *parent = nullptr);
    ~GameManager();

    void initializeGame();

private:
    Ui::MainWindow &ui; // Use a reference to Ui::MainWindow
    Player player;
    HeartCrystal heartCrystal;
    Room* currentRoom;
    QString introText;
    int currentIndex;

    void connectSignalsAndSlots();
    void updatePlayerItemList();
    void updateRoomItemList();
    void updateStats();
    void updateCurrentRoom();
    bool goDirection(const QString &direction);
    void useButtonClicked();
    void pickupButtonClicked();
    void roomSelectedItemChanged(QListWidgetItem *item);
    void selectedItemChanged(QListWidgetItem *item);
    void appendText(const QString &text, int delay);
};

#endif // GAMEMANAGER_H
