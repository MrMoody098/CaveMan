#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(QString name, QString description);
    QString getName();
    QString getDescription();
    bool isAlive();
private:
    QString name;
    QString description;
    bool alive;

};

#endif // ENEMY_H
