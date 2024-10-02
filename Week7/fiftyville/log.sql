-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checking all crimes, one mentioned the bakery and the cs50 duck - 10:15 AM of 28th July 2003
-- SELECT * FROM crime_scene_reports;

-- Checking the interviews for the very same day:
-- SELECT transcript FROM interviews WHERE day = 28;

-- The 3 latests interviews (after Sherlock Holmes Lorem Ipsum) mentioned that
  -- 1) 10 minutes after the theft the thief exited of the bakery (10:25am)
--SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND (minute >= 15 AND minute <= 25) AND activity = 'exit';
  -- 2) Before 10 AM the thief was walking by the ATM on Legget Street after withdrawing some money
--SELECT account_number FROM atm_transactions WHERE day = 28 AND atm_location = "Leggett Street" AND transaction_type = 'withdraw';
  -- 3) Phone call of less than 60s duration before exiting bakery parking, that mentioned a plan to fly in then next day (29th July)
--SELECT caller, receiver FROM phone_calls WHERE duration <= 60 AND day = 28;
--SELECT id, destination_airport_id, MIN(hour) FROM flights WHERE day = 29; -- Earliest flight id = 36
--SELECT passport_number FROM passengers WHERE flight_id = 36;

-- RESOLUTION:
-- With account_number we can find a person_id in bank_accounts
-- With the caller of the phone calls, the phone number
-- With the flight, the passport_number
-- With the bakery parking log, the license plate

-- These are the univocal references to a person. You could find the thief with the following final query:
SELECT
  name
FROM
  people
  JOIN bank_accounts ON id = person_id
WHERE
  phone_number IN (
    SELECT caller FROM phone_calls WHERE duration <= 60 AND day = 28 AND month = 7 AND year = 2023
  ) AND passport_number IN (
      SELECT passport_number FROM passengers WHERE flight_id = (
        SELECT id FROM (SELECT id, MIN(hour) FROM flights WHERE day = 29 AND month = 7 AND year = 2023)
      )
  ) AND license_plate IN (
    SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2023 AND hour = 10 AND (minute >= 15 AND minute <= 25) AND activity = 'exit'
  ) AND bank_accounts.account_number IN (
    SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location = "Leggett Street" AND transaction_type = 'withdraw'
  );
-- And his name is Bruce.

-- To get the City where he flew
SELECT
  city
FROM
  airports
WHERE
  id = (
    SELECT destination_airport_id FROM (SELECT destination_airport_id, MIN(hour) FROM flights WHERE day = 29 AND month = 7 AND year = 2023)
  );


-- And finally, with Bruces phone number, we know he called to his accomplice when leaving the bakery, so...
SELECT
  name
FROM
  people
WHERE
  phone_number = (
    SELECT
      receiver
    FROM
      phone_calls
    WHERE
      duration <= 60
      AND day = 28
      AND month = 7
      AND year = 2023
      AND caller = (
        -- Previous query for Bruce, but getting the phone number
        SELECT
          phone_number
        FROM
          people
          JOIN bank_accounts ON id = person_id
        WHERE
          phone_number IN (
            SELECT caller FROM phone_calls WHERE duration <= 60 AND day = 28 AND month = 7 AND year = 2023
          ) AND passport_number IN (
              SELECT passport_number FROM passengers WHERE flight_id = (
                SELECT id FROM (SELECT id, MIN(hour) FROM flights WHERE day = 29 AND month = 7 AND year = 2023)
              )
          ) AND license_plate IN (
            SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2023 AND hour = 10 AND (minute >= 15 AND minute <= 25) AND activity = 'exit'
          ) AND bank_accounts.account_number IN (
            SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location = "Leggett Street" AND transaction_type = 'withdraw'
          )
      )
  );
