#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTimer>
#include <room.h>
#include <player.h>
#include <QLabel>
#include <QPixmap>
#include <heartcrystal.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void appendText(const QString &text);

    void appendText(const QString &text, int delay);

    //update Ui methods
    void updatePlayerItemList();
    void updateRoomItemList();
    void updateStats();
    void updateCurrentRoom();
    void roomSelectedItemChanged(QListWidgetItem *item);
    //button handlers
    void selectedItemChanged(QListWidgetItem *item);
    void useButtonClicked();
    void pickupButtonClicked();
    void setButtonsEnabled(bool enabled);
    void dropButtonClicked();
    void inspectButtonClicked();
    void fight();
    void flee();

    void onRockSelected();
    void onPaperSelected();
    void onScissorsSelected();

private:
    void enemyDead();
    void gameOver();
    bool goDirection(QString direction);
    Ui::MainWindow *ui;
    QString introText;
    int currentIndex;
    Room* currentRoom;
    Room* lastRoom;
    Player player;
    HeartCrystal heartCrystal;
    QLabel *imageLabel = new QLabel(this);
    void challenge(bool condition);
    QScrollBar *vScrollBar;
    bool fighting;
    void updateDirectionButtons();
    QString choiceToString(int choice);
    QString determineWinner(int playerChoice, int enemyChoice);
    void handlePlayerChoice(int playerChoice);


};

#endif // MAINWINDOW_H

