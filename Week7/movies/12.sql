SELECT
  movies.title
FROM
  stars
  JOIN movies ON movies.id = stars.movie_id
WHERE
  stars.person_id = (
    SELECT
      id
    FROM
      people
    WHERE
      name = 'Bradley Cooper'
  )
INTERSECT
SELECT
  movies.title
FROM
  stars
  JOIN movies ON movies.id = stars.movie_id
WHERE
  stars.person_id = (
    SELECT
      id
    FROM
      people
    WHERE
      name = 'Jennifer Lawrence'
  );
