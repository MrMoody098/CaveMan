#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTimer>
#include <room.h>
#include <player.h>
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

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QString introText;
    int currentIndex;
    Room currentRoom;
    Player player;
};

#endif // MAINWINDOW_H
