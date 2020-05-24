SELECT title
FROM movies
    JOIN stars on movies.id = stars.movie_id
    JOIN people on people.id = stars.person_id
    JOIN ratings on movies.id = ratings.movie_id
WHERE people.name = "Chadwick Boseman"
ORDER BY ratings.rating DESC
LIMIT 5;
