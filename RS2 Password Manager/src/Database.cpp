#include "Database.h"

bool Database::open(std::string filename)
{
    if (sqlite3_open(filename.c_str(), &db) != SQLITE_OK)
        return false;

    const char* sql =
        "CREATE TABLE IF NOT EXISTS passwords("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "appName TEXT,"
        "username TEXT,"
        "password TEXT);";

    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);

    return true;
}

void Database::close()
{
    sqlite3_close(db);
}

bool Database::addEntry(const PasswordEntry& entry)
{
    sqlite3_stmt* stmt;

    const char* sql =
        "INSERT INTO passwords(appName,username,password)"
        "VALUES(?,?,?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, entry.appName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, entry.username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, entry.password.c_str(), -1, SQLITE_TRANSIENT);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);

    return success;
}

std::vector<PasswordEntry> Database::getEntries()
{
    std::vector<PasswordEntry> list;

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db,
        "SELECT appName,username,password FROM passwords;",
        -1,
        &stmt,
        nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        PasswordEntry e;

        e.appName = (const char*)sqlite3_column_text(stmt, 0);
        e.username = (const char*)sqlite3_column_text(stmt, 1);
        e.password = (const char*)sqlite3_column_text(stmt, 2);

        list.push_back(e);
    }

    sqlite3_finalize(stmt);

    return list;
}