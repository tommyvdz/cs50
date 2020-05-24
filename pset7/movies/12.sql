SELECT title
FROM movies
    JOIN stars on movies.id = stars.movie_id
    JOIN people on people.id = stars.person_id AND (people.name = "Johnny Depp" OR people.name = "Helena Bonham Carter")
GROUP BY title
HAVING count(stars.movie_id) > 1;

