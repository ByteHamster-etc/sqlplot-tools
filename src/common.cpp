/******************************************************************************
 * src/common.cpp
 *
 * Common global variables across all programs.
 *
 ******************************************************************************
 * Copyright (C) 2013-2016 Timo Bingmann <tb@panthema.net>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#include "common.h"
#include "strtools.h"

//! verbosity, common global option.
int gopt_verbose = 0;

//! check processed output matches the output file
bool gopt_check_output = false;

//! global command line parameter: named RANGEs to process
std::vector<std::string> gopt_ranges;

//! global SQL datbase connection handle
SqlDatabase* g_db = NULL;

#include "pgsql.h"
#include "mysql.h"
#include "sqlite.h"

//! initialize global SQL database connection
bool g_db_connect(const std::string& db_conninfo)
{
    g_db_free();

    if (db_conninfo.size() == 0)
    {
#if HAVE_POSTGRESQL
        //! first try to connect to a PostgreSQL database

        g_db = new PgSqlDatabase;
        if (g_db->initialize(""))
            return true;
        delete g_db;
#endif
#if HAVE_MYSQL
        //! then try to connect to a MySQL database called "test"

        g_db = new MySqlDatabase();
        if (g_db->initialize("test"))
            return true;
        delete g_db;
#endif
#if HAVE_SQLITE3
        //! then try to connect to an in-memory SQLite database

        g_db = new SQLiteDatabase();
        if (g_db->initialize(":memory:"))
            return true;
        delete g_db;
#endif
    }
    else
    {
        std::string sqlname = db_conninfo;
        std::string dbname;

        std::string::size_type colonpos = sqlname.find(':');
        if (colonpos != std::string::npos) {
            dbname = sqlname.substr(colonpos+1);
            sqlname = sqlname.substr(0, colonpos);
        }

        sqlname = str_tolower(sqlname);

        if (0)
        {
        }
#if HAVE_POSTGRESQL
        else if (sqlname == "postgresql" || sqlname == "postgres" ||
                 sqlname == "pgsql" || sqlname == "pg")
        {
            g_db = new PgSqlDatabase;
            if (g_db->initialize(dbname))
                return true;
            delete g_db;
        }
#endif
#if HAVE_MYSQL
        else if (sqlname == "mysql" || sqlname == "my")
        {
            if (dbname.size() == 0) dbname = "test";

            g_db = new MySqlDatabase;
            if (g_db->initialize(dbname))
                return true;
            delete g_db;
        }
#endif
#if HAVE_SQLITE3
        else if (sqlname == "sqlite" || sqlname == "lite")
        {
            if (dbname.size() == 0) dbname = ":memory:";

            g_db = new SQLiteDatabase;
            if (g_db->initialize(dbname))
                return true;
            delete g_db;
        }
#endif
        else
        {
            OUT("ERROR: unknown (or not compiled) SQL database type \"" <<
                sqlname << "\"!");
        }
    }

    return false;
}

//! free global SQL database connection
void g_db_free()
{
    if (g_db) {
        delete g_db;
        g_db = NULL;
    }
}
