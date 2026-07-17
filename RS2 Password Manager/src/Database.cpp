#include "Database.h"
#include <iostream>
using namespace std;

bool Database::open(std::string filename)
{
    if (sqlite3_open(filename.c_str(), &db) != SQLITE_OK)
        return false;

    const char* passwordTable =
        "CREATE TABLE IF NOT EXISTS passwords ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "user_id INTEGER,"
        "appName TEXT,"
        "username TEXT,"
        "password TEXT"
        ");";

    sqlite3_exec(db, passwordTable, nullptr, nullptr, nullptr);

    const char* userTable =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "email TEXT UNIQUE NOT NULL,"
        "password TEXT NOT NULL"
        ");";

    sqlite3_exec(db, userTable, nullptr, nullptr, nullptr);

    return true;
}

void Database::close()
{
    sqlite3_close(db);
}

bool Database::addEntry(int userID, const PasswordEntry& entry)
{
    sqlite3_stmt* stmt;

    const char* sql =
        "INSERT INTO passwords(user_id, appName, username, password) "
        "VALUES(?, ?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cout << "Add prepare failed: "
            << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, userID);
    sqlite3_bind_text(stmt, 2, entry.appName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, entry.username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, entry.password.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

vector<PasswordEntry> Database::getEntries(int userID)
{
    vector<PasswordEntry> entries;

    sqlite3_stmt* stmt;

    const char* sql =
        "SELECT appName, username, password "
        "FROM passwords "
        "WHERE user_id = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cout << "Get entries prepare failed: "
            << sqlite3_errmsg(db) << std::endl;
        return entries;
    }

    sqlite3_bind_int(stmt, 1, userID);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        PasswordEntry entry;

        entry.appName =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        entry.username =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        entry.password =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        entries.push_back(entry);
    }

    sqlite3_finalize(stmt);

    return entries;
}

bool Database::loginUser(std::string email, std::string password)
{
    sqlite3_stmt* stmt;

    const char* sql =
        "SELECT id FROM users "
        "WHERE email = ? "
        "AND password = ?;";

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

    bool found = false;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        currentUserID = sqlite3_column_int(stmt, 0);
        found = true;
    }
    else
    {
        currentUserID = -1;
    }

    sqlite3_finalize(stmt);

    return found;
}
bool Database::userExists(std::string email)
{
    sqlite3_stmt* stmt;

    const char* sql =
        "SELECT id FROM users WHERE email=?;";

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);

    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);

    return exists;
}
bool Database::registerUser(std::string email, std::string password)
{
    if (userExists(email))
        return false;

    sqlite3_stmt* stmt;

    const char* sql =
        "INSERT INTO users(email, password) VALUES(?, ?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}
int Database::getCurrentUserID() const
{
    return currentUserID;
}