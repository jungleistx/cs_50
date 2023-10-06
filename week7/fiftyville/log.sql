-- Keep a log of any SQL queries you execute as you solve the mystery.

-- look at the layout
.schema
-- KNOWN INFO: date of crime: june 28 2021, on Humphrey Street
-- lets take a look at the reports
SELECT * FROM crime_scene_reports;
-- find the correct report
SELECT * FROM crime_scene_reports WHERE street LIKE 'Humphrey%';
-- filter more
SELECT * FROM crime_scene_reports WHERE street = 'Humphrey Street' AND month = 7 AND day = 28 AND year = 2021;
-- get the id of the correct report
SELECT * FROM crime_scene_reports WHERE street = 'Humphrey Street' AND month = 7 AND day = 28 AND year = 2021 and description LIKE "%duck%";
-- CLUE: time-of-crime: 10:15 AND crimescene: Humphrey Street bakery (3 witnesses)
-- look the layout of the interviews
SELECT * FROM interviews LIMIT 2;
-- find the interviews that mentions bakery on the day of theft
SELECT * FROM interviews WHERE transcript LIKE '%bakery%'
	AND month = 7 and year = 2021 and day = 28;
-- CLUE: suspect was 10:15 - 10:25 in bakery parkinglot, found in security footage
-- CLUE: suspect withdraw money from ATM in Leggett Street before theft
-- CLUE: suspect called after theft, duration of call < 1min. Plan was to take earliest flight tomorrow, person on the phone purchased the tickets
-- lets look at the bakery security logs
SELECT * FROM bakery_security_logs LIMIT 3;
-- narrow down the search
SELECT * FROM bakery_security_logs WHERE day = 28 AND year = 2021 AND month = 7 AND hour = 10 AND minute >= 15 AND minute <= 25;
-- one of these 8 results has the suspects car (column license_plate)
-- look at the atm history
SELECT * FROM atm_transactions LIMIT 3;
-- search with correct information
SELECT * FROM atm_transactions
	WHERE atm_location = 'Leggett Street'
	AND transaction_type = 'withdraw'
	AND year = 2021 AND month = 7 AND day = 28
	;
-- one of these transactions is from the thief
-- lets look at the phonecalls
SELECT * FROM phone_calls LIMIT 5;
-- seach with the known information
SELECT * FROM phone_calls
	WHERE year = 2021 AND month = 7 AND day = 28
	AND duration < 60
	;
-- one of these phonenumbers belongs to the thief and accomplice
-- lets try to combine known information from people table to get suspects name
SELECT name FROM people
	WHERE license_plate IN
	(
	SELECT license_plate FROM bakery_security_logs
	WHERE day = 28 AND year = 2021
	AND month = 7 AND hour = 10 AND minute >= 15 AND minute <= 25
	)
	AND phone_number IN
	(
	SELECT caller FROM phone_calls
	WHERE year = 2021 AND month = 7 AND day = 28
	AND duration < 60
	)
	;
-- now we have 4 names of possible thief
-- lets try to include to atm-transactions
SELECT name FROM people
	WHERE id IN
	(
	SELECT person_id FROM bank_accounts
	WHERE account_number IN
	(
	SELECT account_number FROM atm_transactions
	WHERE atm_location = 'Leggett Street'
	AND transaction_type = 'withdraw'
	AND year = 2021 AND month = 7 AND day = 28
	)
	)
	AND license_plate IN
	(
	SELECT license_plate FROM bakery_security_logs
	WHERE day = 28 AND year = 2021
	AND month = 7 AND hour = 10 AND minute >= 15 AND minute <= 25
	)
	AND phone_number IN
	(
	SELECT caller FROM phone_calls
	WHERE year = 2021 AND month = 7 AND day = 28
	AND duration < 60
	)
	;
-- now we have 2 names for the suspect, Diana and Bruce, who both made the call, withdraw money and left the bakery at correct time
-- lets look at the flights table
SELECT * FROM flights LIMIT 3;
-- lets search for the next days first flight
SELECT * FROM flights
	WHERE year = 2021 AND month = 7 AND day = 29
	ORDER BY hour, minute
	LIMIT 1
	;
-- this is the flight the accomplice purchased
-- lets look at the passenger list in the flight
SELECT * FROM passengers
	WHERE flight_id =
	(
	SELECT id FROM flights
	WHERE year = 2021 AND month = 7 AND day = 29
	ORDER BY hour, minute
	LIMIT 1
	)
	;
-- lets get the names of the passengers
SELECT name FROM people
	WHERE passport_number IN
	(
	SELECT passport_number FROM passengers
	WHERE flight_id =
	(
	SELECT id FROM flights
	WHERE year = 2021 AND month = 7 AND day = 29
	ORDER BY hour, minute
	LIMIT 1
	)
	)
	;
-- combine the earlier information with the passengers list
SELECT name FROM people
	WHERE id IN
	(
	SELECT person_id FROM bank_accounts
	WHERE account_number IN
	(
	SELECT account_number FROM atm_transactions
	WHERE atm_location = 'Leggett Street'
	AND transaction_type = 'withdraw'
	AND year = 2021 AND month = 7 AND day = 28
	)
	)
	AND license_plate IN
	(
	SELECT license_plate FROM bakery_security_logs
	WHERE day = 28 AND year = 2021
	AND month = 7 AND hour = 10 AND minute >= 15 AND minute <= 25
	)
	AND phone_number IN
	(
	SELECT caller FROM phone_calls
	WHERE year = 2021 AND month = 7 AND day = 28
	AND duration < 60
	)
	AND passport_number IN
	(
	SELECT passport_number FROM passengers
	WHERE flight_id =
	(
	SELECT id FROM flights
	WHERE year = 2021 AND month = 7 AND day = 29
	ORDER BY hour, minute
	LIMIT 1
	)
	)
	;
-- now we have found the thief, Bruce!
-- lets find the city they espaced into
SELECT city FROM airports
	WHERE id =
	(
	SELECT destination_airport_id FROM flights
	WHERE year = 2021 AND month = 7 AND day = 29
	ORDER BY hour, minute
	LIMIT 1
	)
	;
-- they escaped to New York City
-- lets find the accomplice
-- get Bruces phone-number
SELECT phone_number FROM people
	WHERE name = 'Bruce';
-- find the calls Bruce made
SELECT * from phone_calls
	WHERE caller =
	(
	SELECT phone_number FROM people
	WHERE name = 'Bruce'
	)
	;
-- refine parameters
SELECT * from phone_calls
	WHERE caller =
	(
	SELECT phone_number FROM people
	WHERE name = 'Bruce'
	)
	AND year = 2021 AND month = 7 AND day = 28
	AND duration < 60
	;
-- now we have the receivers phone-number
-- find the name of the accomplice
SELECT name FROM people
	WHERE phone_number =
	(
	SELECT receiver from phone_calls
	WHERE caller =
	(
	SELECT phone_number FROM people
	WHERE name = 'Bruce'
	)
	AND year = 2021 AND month = 7 AND day = 28
	AND duration < 60
	)
	;
-- name of the accomplice is Robin!
-- lets look what info we have on Robin
SELECT * FROM people WHERE name = 'Robin';
-- he doesnt have a passport so he probably didnt board the flight
-- lets try to look the bakery logs
SELECT * from bakery_security_logs
	WHERE license_plate =
	(
	SELECT license_plate FROM people WHERE name = 'Robin'
	)
	;
-- found activity on the morning of the theft in the bakery parkinglot
-- find the calls Bruce had
SELECT
	id,
	(SELECT name FROM people WHERE phone_number = caller) AS caller,
	(SELECT name FROM people WHERE phone_number = receiver) AS receiver,
	year, month, day, duration
	FROM phone_calls
	WHERE
	caller = (SELECT phone_number FROM people WHERE name = 'Bruce')
	OR
	receiver = (SELECT phone_number FROM people WHERE name = 'Bruce')
	;
-- bakery logs from people who talked with the thief on the phone
SELECT
	b.id, b.year, b.month, b.day, b.hour, b.minute, b.activity,
	(SELECT p.name FROM people p WHERE p.license_plate = b.license_plate) as license_plate,
	license_plate
	FROM bakery_security_logs b
	WHERE b.license_plate IN
	(
	SELECT license_plate FROM people
	WHERE name IN
	(
	SELECT
	(SELECT name FROM people WHERE phone_number = receiver) AS receiver
	FROM phone_calls
	WHERE
	(caller = (SELECT phone_number FROM people WHERE name = 'Bruce')
	OR
	receiver = (SELECT phone_number FROM people WHERE name = 'Bruce'))
	AND year = 2021 AND month = 7 AND day >= 25 AND day <= 30
	)
	)
	AND b.day >= 27 AND b.day <= 29
	;



-- CONCLUSION:
-- CLUE1: withdraw money from Leggett Street
SELECT * FROM atm_transactions
	WHERE account_number =
	(SELECT account_number FROM bank_accounts
	WHERE person_id =
	(SELECT id FROM people WHERE name = 'Bruce')
	)
	AND day = 28
	;
-- CLUE2: was at the crimescene at the time-of-crime
SELECT * FROM bakery_security_logs
	WHERE license_plate =
	(SELECT license_plate FROM people WHERE name = 'Bruce')
	;
-- CLUE3: took a phonecall on the day of theft, duration < 1min
SELECT * FROM phone_calls
	WHERE caller =
	(SELECT phone_number FROM people WHERE name = 'Bruce')
	AND day = 28 AND duration < 60
	;
-- CLUE4: onboard the first next days flight
SELECT name FROM people
	WHERE passport_number IN
	(
	SELECT passport_number FROM passengers
	WHERE flight_id =
	(SELECT id FROM flights
	WHERE year = 2021 AND month = 7 AND day = 29
	ORDER BY hour, minute
	LIMIT 1
	)
	)
	AND name = 'Bruce'
	;
