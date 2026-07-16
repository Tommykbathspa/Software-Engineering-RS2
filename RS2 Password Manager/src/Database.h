#pragma once

#include <vector>
#include <string>
#include "sqlite3.h"
#include "PasswordEntry.h"

class Database
{
public:

    bool open(std::string filename);

    void close();

    bool addEntry(const PasswordEntry& entry);

    std::vector<PasswordEntry> getEntries();

private:

    sqlite3* db = nullptr;
};