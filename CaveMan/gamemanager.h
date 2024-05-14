// // GameManager.h
// #pragma once

// #include <QObject>
// #include <QListWidgetItem>
// #include <QTimer>
// #include "room.h"
// #include "player.h"
// #include "heartcrystal.h"

// class GameManager : public QObject {
//     Q_OBJECT
// public:
//     GameManager(QObject* parent = nullptr);
//     ~GameManager();

//     void startGame();

// private slots:
//     void goDirection(QString direction);
//     void useButtonClicked();
//     void pickupButtonClicked();
//     void roomSelectedItemChanged(QListWidgetItem *item);
//     void selectedItemChanged(QListWidgetItem *item);

// signals:
//     void appendText(const QString &text, int delay);

// private:
//     void initializeGame();
//     void updatePlayerItemList();
//     void updateRoomItemList();
//     void updateStats();
//     void updateCurrentRoom();

//     Room* currentRoom;
//     Player player;
//     HeartCrystal heartCrystal;
//     int currentIndex;
// };
