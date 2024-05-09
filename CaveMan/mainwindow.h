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
    QLabel *imageLabel = new QLabel(this);

};

#endif // MAINWINDOW_H
