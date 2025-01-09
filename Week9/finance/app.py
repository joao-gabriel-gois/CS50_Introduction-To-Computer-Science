from cs50 import SQL
from flask import Flask, jsonify, redirect, render_template, request, session, url_for
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Using default path before submitting
db = SQL("sqlite:///finance.db")
# test_db_name = "test" # file is not currently there. To create it run `./run_migration test`.
# db = SQL(f"sqlite:///db/test/{test_db_name}.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    result = db.execute("""
        SELECT users.cash, stocks.symbol, stocks.shares
        FROM users
        JOIN stocks ON users.id = stocks.owner_id
        WHERE users.id = ?
    """, session["user_id"])

    lookups = []
    type = request.args.get("type")

    if len(result) == 0:
        cash_row = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        if len(cash_row) != 1:
            return redirect("/logout")

        cash = cash_row[0]["cash"]
        total = {
            "grand_total": usd(cash),
            "cash": usd(cash)
        }
        return render_template("index.html", stocks=result, lookups=lookups, total=total, type=type)

    grand_total = float(result[0]["cash"])
    for i, stock in enumerate(result):
        price = lookup(stock["symbol"])
        price.update({"stock_index": i})
        lookups.append(price)
        grand_total += price["price"] * stock["shares"]

    total = {
        "grand_total": usd(grand_total),
        "cash": usd(result[0]["cash"])
    }

    return render_template("index.html", stocks=result, lookups=lookups, total=total, type=type)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        stock_symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if stock_symbol == "":
            return apology("Please provide the Stock Symbol!", 400)

        int_shares = -1
        try:
            int_shares = int(shares)
        except ValueError as int_conversion_failure:
            print("Not able to convers shares to int!", int_conversion_failure)
            return apology("Shares values must be integers.")

        if shares == "" or int_shares <= 0:
            return apology("Please provide a positive number for Shares!", 400)

        response = lookup(stock_symbol)
        if response == None:
            return apology("Stock Symbol Not Found", 400)

        user_row = db.execute('SELECT * FROM users WHERE id = ?', session["user_id"])
        if len(user_row) != 1:
            return redirect("/logout")

        user = user_row[0]
        purchase_total = response["price"] * int_shares
        if purchase_total > float(user["cash"]):
            return apology("You have not enough money to buy this Stock!", 403)
        try:
            db.execute(
                """
                    UPDATE users
                    SET cash = cash - ?
                    WHERE id = ?;
                """,
                purchase_total,
                user["id"]
            )
            db.execute(
                """
                    INSERT INTO stocks (owner_id, symbol, shares)
                    VALUES (?, ?, ?)
                    ON CONFLICT(owner_id, symbol) DO UPDATE SET
                        shares = stocks.shares + excluded.shares;
                """,
                user["id"],
                response["symbol"],
                shares
            )
            db.execute(
                """
                    INSERT INTO transactions (owner_id, symbol, shares, type, price)
                    VALUES (?, ?, ?, 'buy', ?);
                """,
                user["id"],
                response["symbol"],
                shares,
                response["price"]
            )
        except Exception as e:
            print("Transaction failed:", e)
            return apology("Somehow Transaction has failed", 500)

        return redirect(url_for("index", type="bought"))

    query_stock = request.args.get("stock")
    return render_template("buy.html", query_stock=query_stock)


@app.route("/history")
@login_required
def history():
    transactions = db.execute("SELECT * FROM transactions WHERE owner_id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/session-info")
@login_required
def session_info():
    username_row = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    if len(username_row) != 1:
        return jsonify(
            error="No user ID found",
            message="This session's user_id is set for a non-existent user, this should'nt happen once this route is authenticated",
            status=400,
        )
    return jsonify(username=username_row[0]["username"], status=200)


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        stock_symbol = request.form.get("symbol")
        response = lookup(stock_symbol)
        if response == None:
            return apology("This stock symbol doesn't exists!")
        return render_template('quoted.html', response=response)

    return render_template("quote.html")


@app.route("/add-cash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "POST":
        cash = request.form.get("cash")
        if (float(cash) <= 0):
            return apology("Deposit value must be a positive number", 400)

        try:
            db.execute('UPDATE users SET cash = cash + ? WHERE id = ?',
                       float(cash), session["user_id"])
        except ValueError as update_failure:
            print("Value Error for UPDATING user's cash:", update_failure)
            return apology("Something went really really wrong", 500)

        return redirect(url_for("index", type="deposit"))

    return render_template("add-cash.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if username == "" or password == "" or confirmation == "":
            return apology("One of the fields of the form is empty. Fill it.")
        elif password != confirmation:
            return apology("Passwords are not matching!")
        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)",
                username,
                generate_password_hash(password)
            )
            return redirect("/login")
        except ValueError as repeated_user_error:
            print("Value Error for username:", repeated_user_error)
            return apology("There is already an user with this username")

    return render_template("register.html")


@app.route("/change-password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        new_password = request.form.get("new_password")
        user_session_data = db.execute(
            'SELECT username, hash FROM users WHERE id = ?', session["user_id"])

        if username == "" or password == "" or new_password == "" or confirmation == "":
            return apology("One of the fields of the form is empty. Fill it.", 400)
        elif len(user_session_data) == 0:
            return apology("Something went really really wrong", 500)
        elif len(user_session_data) != 1 or user_session_data[0]["username"] != username:
            return apology("The current username is wrong", 403)
        elif len(user_session_data) != 1 or not check_password_hash(
            user_session_data[0]["hash"], password
        ):
            return apology("The current password is wrong", 403)
        elif password != confirmation:
            return apology("Passwords are not matching!", 400)
        try:
            db.execute(
                "UPDATE users SET hash = ? WHERE id = ? LIMIT 1",
                generate_password_hash(new_password),
                session["user_id"]
            )
            return redirect("/login")
        except ValueError as repeated_user_error:
            return apology("There is already an user with this username")

    return render_template("change_password.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_stocks = db.execute("SELECT * FROM stocks WHERE owner_id = ?", session["user_id"])
    if request.method == "POST":
        stock_symbol = request.form.get("symbol")  # Turn to select and adapt validations
        shares = request.form.get("shares")
        if stock_symbol == "":
            return apology("Please provide the Stock Symbol!", 400)
        if shares == "" or int(shares) <= 0:
            return apology("Please provide a positive number for Shares!", 400)

        response = lookup(stock_symbol)
        if response == None:
            return apology("Stock Symbol Not Found", 404)

        for stock in user_stocks:
            if stock["symbol"] == stock_symbol.upper() and int(stock["shares"]) < int(shares):
                return apology("You don't have this many shares to sell", 400)

        user = db.execute('SELECT * FROM users WHERE id = ? LIMIT 1', session["user_id"])[0]
        purchase_total = response["price"] * int(shares)
        try:
            db.execute(
                """
                    UPDATE users
                    SET cash = cash + ?
                    WHERE id = ?;
                """,
                purchase_total,
                user["id"]
            )
            db.execute(
                """
                    INSERT INTO stocks (owner_id, symbol, shares)
                    VALUES (?, ?, ?)
                    ON CONFLICT(owner_id, symbol) DO UPDATE SET
                        shares = stocks.shares - excluded.shares;
                """,
                user["id"],
                response["symbol"],
                shares
            )
            db.execute("DELETE FROM stocks WHERE shares <= 0")
            db.execute(
                """
                    INSERT INTO transactions (owner_id, symbol, shares, type, price)
                    VALUES (?, ?, ?, 'sell', ?);
                """,
                user["id"],
                response["symbol"],
                shares,
                response["price"]
            )

        except Exception as e:
           # db.execute("ROLLBACK;")
            print("Transaction failed:", e)
            return apology("Somehow Transaction has failed", 500)

        return redirect(url_for("index", type="sold"))
    query_stock = request.args.get("stock")
    return render_template("sell.html", stocks=user_stocks, query_stock=query_stock)
