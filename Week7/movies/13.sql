SELECT DISTINCT
  people.name
FROM
  stars
  JOIN people ON person_id = people.id
  JOIN movies ON movie_id = movies.id
WHERE
  movies.id IN (
    SELECT
      movie_id
    FROM
      stars
    WHERE
      person_id = (
        SELECT
          id
        FROM
          people
        WHERE
          name = 'Kevin Bacon'
          AND birth = 1958
      )
  )
  AND NOT (
    people.name = 'Kevin Bacon'
    AND birth = 1958
  );
