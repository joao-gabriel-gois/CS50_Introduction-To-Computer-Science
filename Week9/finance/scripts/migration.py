from sys import argv
from cs50 import SQL

# def table_has_column(db, table, column):
#     try:
#         db.execute(f'SELECT {column} FROM {table} LIMIT 1')
#         return True
#     except Exception:
#         return False

def get_tables_list(db):
    return [row["name"] for row in db.execute("SELECT name FROM sqlite_master WHERE type='table'")]

def main(db):
    try:
        current_tables = get_tables_list(db)
        if 'users' not in current_tables:
            db.execute(
                """
                CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
                    username TEXT NOT NULL,
                    hash TEXT NOT NULL,
                    cash NUMERIC NOT NULL DEFAULT 10000.00
                )
                """
            )
            print("(USERS): 'users' table has been created.")
        else:
            print("(USERS): 'users' table ALREADY EXISTS.")

        db.execute("CREATE UNIQUE INDEX IF NOT EXISTS username ON users (username)")
        print("(USERS): 'users' unique index for username has been created if it doesn't exists.")

        if 'stocks' not in current_tables:
            db.execute(
                """
                CREATE TABLE IF NOT EXISTS stocks (
                    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
                    owner_id INTEGER NOT NULL,
                    symbol TEXT NOT NULL,
                    shares INTEGER NOT NULL,
                    FOREIGN KEY(owner_id) REFERENCES users(id),
                    UNIQUE(owner_id, symbol)
                )
                """
            )
            print("(STOCKS): 'stocks' table has been created.")
        else:
            print("(STOCKS): 'stocks' table ALREADY EXISTS.")

        db.execute("CREATE INDEX IF NOT EXISTS owner_id ON stocks (owner_id);")
        print("(STOCKS_INDEX): 'owner_id' index on 'stocks' table has been created if it doesn't exists.")

        db.execute("CREATE INDEX IF NOT EXISTS symbol ON stocks (symbol);")
        print("(STOCKS_INDEX): 'symbol' index on 'stocks' table has been created if it doesn't exists.")

        if 'transactions' not in current_tables:
            db.execute(
                """
                CREATE TABLE IF NOT EXISTS transactions (
                    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
                    owner_id INTEGER NOT NULL,
                    symbol TEXT NOT NULL,
                    shares INTEGER NOT NULL,
                    type TEXT NOT NULL,
                    price NUMERIC NOT NULL,
                    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
                    FOREIGN KEY(owner_id) REFERENCES users(id)
                )
                """
            )
            print("(TRANSACTIONS): 'transactions' table has been created.")
        else:
            print("(TRANSACTIONS): 'transactions' table ALREADY EXISTS.")

        db.execute("CREATE INDEX IF NOT EXISTS owner_id ON transactions (owner_id);")
        print("(TRANSACTIONS_INDEX): 'owner_id' index on 'transactions' table has been created if it doesn't exists.")


    except Exception as e:
        print("Transaction failed:", e)



if __name__ == "__main__":
    db_name = "finance"
    if len(argv[1]) != 0:
        db_name = argv[1]
    database = SQL(f"sqlite:///{db_name}")
    main(database)
