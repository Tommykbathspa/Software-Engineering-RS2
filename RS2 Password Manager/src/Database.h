#pragma once
using namespace std;

#include <vector>
#include <string>
#include "sqlite3.h"
#include "PasswordEntry.h"

class Database
{
public:
    int getCurrentUserID() const;

    bool registerUser(string email, string password);

    bool loginUser(string email, string password);

    bool userExists(string email);

    bool open(string filename);

    void close();

    bool addEntry(int userID, const PasswordEntry& entry);

    bool deleteEntry(int entryID, int userID);

    vector<PasswordEntry> getEntries(int userID);

private:

    sqlite3* db = nullptr;
    int currentUserID = -1;

private:
    string xorEncrypt(const string& text);
    string xorDecrypt(const string& text);


};