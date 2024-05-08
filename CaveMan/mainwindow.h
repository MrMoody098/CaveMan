#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTimer>
#include <room.h>
#include <player.h>
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
    void appendText(const QString &text, int delay);
    void handleSelectedItemChanged(QListWidgetItem *item);
    void updateList();
    void handleUseButtonClicked();
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QString introText;
    int currentIndex;
    Room currentRoom;
    Player player;
    HeartCrystal heartCrystal;
};

#endif // MAINWINDOW_H
