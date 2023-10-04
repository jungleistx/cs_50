-- In 8.sql, write a SQL query to list the names of all people who starred in Toy Story.
-- Your query should output a table with a single column for the name of each person.
-- You may assume that there is only one movie in the database with the title Toy Story.

/*
-- V1
SELECT DISTINCT(people.name)
	FROM people, movies, stars
	WHERE stars.movie_id = (SELECT id from movies WHERE title = 'Toy Story')
	AND people.id = stars.person_id;

-- Run Time: real 1.247 user 1.227155 sys 0.019642
*/

-- V2
SELECT name FROM people WHERE id IN
	(SELECT person_id FROM stars WHERE movie_id =
	(SELECT id FROM movies WHERE title = 'Toy Story'));

-- Run Time: real 0.061 user 0.053998 sys 0.005708