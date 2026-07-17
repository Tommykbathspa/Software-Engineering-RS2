#pragma once

#include <vector>
#include <string>
#include "sqlite3.h"
#include "PasswordEntry.h"

class Database
{
public:
    int getCurrentUserID() const;

    bool registerUser(std::string email, std::string password);

    bool loginUser(std::string email, std::string password);

    bool userExists(std::string email);

    bool open(std::string filename);

    void close();

    bool addEntry(int userID, const PasswordEntry& entry);

    std::vector<PasswordEntry> getEntries(int userID);

private:

    sqlite3* db = nullptr;
    int currentUserID = -1;
};