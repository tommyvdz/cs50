SELECT DISTINCT name
FROM people
    JOIN stars on people.id = stars.person_id AND (people.name != "Kevin Bacon")
WHERE stars.movie_id IN (SELECT stars.movie_id FROM stars JOIN people ON people.id = stars.person_id WHERE (people.name = "Kevin Bacon" AND people.birth = 1958));

