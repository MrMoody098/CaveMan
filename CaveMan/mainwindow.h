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

//define my soundsettings union
union SoundSettings {
    int intValue;
    float floatValue;
    SoundSettings() : intValue(50) {}  // Default constructor initializes intValue to 0
};

// Forward declaration
class SkipStone;

// Enable debuggin if debug mode is defined

#ifdef DEBUG_MODE
#include <QDebug> //
#define DEBUG_LOG(x) qDebug() << x // outputs debugs normally
#else
#define DEBUG_LOG(x)
#endif


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    friend class SkipStone;


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

    SoundSettings soundSettings;


    Ui::MainWindow *ui;
    Player player;
    HeartCrystal heartCrystal;
    Room *currentRoom;
    Room *lastRoom;
    bool fighting = false;
    int currentIndex;

    static const int numRooms = 14;
    Room* rooms[numRooms];



    // Helper functions
    void setupRooms();
    void setupConnections();
    void initialiseGameState();

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
    void gameOver();
    QString choiceToString(int choice);
    int getItemId(const QString &itemName);

    //implement these
    void transferItemFromRoomToPlayer(int itemId);
    void transferItemFromPlayerToRoom(int itemId);
    void setMovementButtonsEnabled(bool enabled);
    void setCombatButtonsEnabled(bool enabled);

protected:
    void enemyDead();
};


#endif // MAINWINDOW_H

