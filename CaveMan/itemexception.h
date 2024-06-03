// ItemException.h
#ifndef ITEMEXCEPTION_H
#define ITEMEXCEPTION_H

#include <exception>
#include <QString>

class ItemException : public std::exception {
public:
    ItemException(const QString& message) : msg(message) {}
    const char* what() const noexcept override { // overides the what method in the base exception library
        return msg.toStdString().c_str(); //convert to std String then to a c_str which is a c style string as the return is char*
    }
private:
    QString msg;
};

class InvalidValueException : public ItemException {
public:
    InvalidValueException(const QString& message) : ItemException(message) {}
};

class InvalidQuantityException : public ItemException {
public:
    InvalidQuantityException(const QString& message) : ItemException(message) {}
};

#endif // ITEMEXCEPTION_H
