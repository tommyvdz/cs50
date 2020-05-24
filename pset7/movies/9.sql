SELECT name
FROM people
WHERE people.id IN (SELECT DISTINCT people.id FROM people
    JOIN stars on people.id = stars.person_id
    JOIN movies on movies.id = stars.movie_id
WHERE year = 2004)
ORDER BY birth
