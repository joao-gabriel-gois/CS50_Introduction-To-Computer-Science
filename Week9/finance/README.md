# CS50's Finance

<sup style="color: #AAA"> Flask Application - Week 9</sup>

### Understanding the application
This is my resolution for **[CS 50's problem-set 9](https://cs50.harvard.edu/x/2024/psets/9/finance/)**. All details can be found in this url. For this project, all the mentioned specs were implemented and, additionally, we had the following extra features as part of the [**personal touch**](https://cs50.harvard.edu/x/2024/psets/9/finance/#personal-touch):

<blockquote style="font-style: italic; color: #777;padding-top:0.25em;padding-bottom:0.75em;">

**Recomended:**

* Allow users to change their passwords.
* Allow users to add additional cash to their account.
* Allow users to buy more shares or sell shares of stocks they already own via index itself, without having to type stocks’ symbols manually.
</blockquote>

<blockquote style="margin-top:0;padding-top:0.5em;padding-bottom:0.75em;">

**New features:**
* Implement some other feature of comparable scope. **Which are**:
    * Last username reminder:
        * Once you logout, the last used username will be automatically filled in the username input of the [`/login`](templates/login.html) page.
    * Front-end side validations:
        * All fields display realtime messages about possible validation errors for each case. By going to [`static/script.js`](static/script.js) and changing the `WITH_BLOCKING_VALIDATIONS` to `true`, the frontend side validations will also disable the submit buttons on HTML side.
</blockquote>

---
### Running the Application
As part of the exercise specs, it was required to apply changes in the database provided by them. In order to organize this better, this project contain some db migration scripts. The current application db is in the root directory and the filename is `finance.db`. Also, inside the [`db/test/`](db/test/) you can find the [`finance_clean.db`](db/test/finance_clean.db) file which contains the pure version that came with the exercise.


<blockquote style="padding-top:0.25em;padding-bottom:0.75em;color:#999;">
<div style="text-align:left;font-size:14pt;margin-top:0.25em;margin-bottom:0.5em;color:#FA0;">⚠️ Warning</div>

All the scripts to prepare python env and set up migrations are set for Debian Based Linux systems. Try to overcome it for your OS based on their source code. Also: In case you have anaconda3 installed, its `~/anaconda3/bin/openssl` binary might impact hashing support for `/login`. Run `openssl version -d` to check if it is correctly pointing to `/usr/lib/ssl` and, if not, find a way to overcome it by either rearranging `$PATH` to have the system openssl version as a priority (recommended) or you can also move temporarily anaconda3 openssl binary. In both cases, once done, check `openssl version -d` again.
</blockquote>

#### How to handle migrations
This version already is set and pointing to a ready-to-use database, `finance.db`.

**Details:**
_There is a bash script in the root directory called `./run_migration` which will migrate the DB in `./finance.db` by default. The current file is already updated and don't require any migration. But you can pass an extra argument to this script with a new DB name and in case it exists in root directory, it will run migration on it. In case it is not there, it will check [`db/test/`](db/test/) and it will migrate any db file with the same name in this tests dir. If it doesn't exists also in `db/test/`, the script will first create a new db inside `db/test/`, then run the migration on it. You can find more details by checking both [`./run_migration`](./run_migration) and [`scripts/migration.py`](scripts/migration.py) files._

#### Executing Flask Server
Simply run `./run_flask_app`. This version will automatically work only by running this command. However, for new dbs or future modifications, this command will only work after being sure that:
1. an available sqlite3 .db file is at the root directory
2. it was properly migrated (`./run_migration`)
3. it's path is correctly referenced inside `app.py`.
