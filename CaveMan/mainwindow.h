#ifndef MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QPushButton>  // Include QPushButton header
#include <QTimer>
#include "player.h"
#include "room.h"
#include "enemy.h"
#include "heartcrystal.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


// Forward declaration
class SkipStone;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


signals:
    void appended();
private slots:
    // Slot functions for button clicks
    void pickupButtonClicked();
    void useButtonClicked();
    void dropButtonClicked();
    void inspectButtonClicked();
    void fight();
    void flee();
    void onRockSelected();
    void onPaperSelected();
    void onScissorsSelected();

    // Slot functions for item selection changes
    void roomSelectedItemChanged(QListWidgetItem *item);
    void selectedItemChanged(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Player player;
    HeartCrystal heartCrystal;
    Room *currentRoom;
    Room *lastRoom;
    bool fighting = false;
    int currentIndex;

    // Helper functions
    void setupRooms();
    void setupConnections();
    void initializeGameState();
    void appendText(const QString &text);
    void appendText(const QString &text, int delay);
    void setButtonsEnabled(bool enabled);
    void updateRoomItemList();
    void updatePlayerItemList();
    void updateStats();
    void updateCurrentRoom();
    void updateDirectionButtons();
    void updateDirectionButton(QPushButton *button, Room *room);
    void updateButtonStyles(const QString &itemText, QPushButton *button, const QString &style);
    void resetButtonStyles();
    bool goDirection(QString direction);
    void challenge(bool condition);
    void handlePlayerChoice(int playerChoice);
    QString determineWinner(int playerChoice, int enemyChoice);
    void enemyDead();
    void gameOver();
    QString choiceToString(int choice);
    int getItemId(const QString &itemName);
    void transferItemFromRoomToPlayer(int itemId);
    void transferItemFromPlayerToRoom(int itemId);
    void setMovementButtonsEnabled(bool enabled);
    void setCombatButtonsEnabled(bool enabled);


};

#endif // MAINWINDOW_H

