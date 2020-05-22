SELECT DISTINCT name
FROM people
    JOIN directors on people.id = directors.person_id
    JOIN ratings on ratings.movie_id = directors.movie_id
WHERE ratings.rating >= 9.0
ORDER BY people.name;
