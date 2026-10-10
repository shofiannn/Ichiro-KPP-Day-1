#ifndef INVALID_ACTION_EXCEPTION_H
#define INVALID_ACTION_EXCEPTION_H

#include <stdexcept>
#include <string>

//membuat exception khusus untuk aksi yang melanggar aturan simulasi
class InvalidActionException : public std::runtime_error {
public:
    //membuat exception dengan menerima pesan kesalahan
    explicit InvalidActionException(const std::string& pesan)
        : std::runtime_error(pesan) {} //meneruskan pesan kesalahan ke konstruktor runtime_error
};

#endif