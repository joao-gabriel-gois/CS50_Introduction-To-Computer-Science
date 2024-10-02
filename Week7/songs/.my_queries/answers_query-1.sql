SELECT
    songs.id AS song_id,
    songs.name AS song_name,
    artists.name AS artist_name,
    energy,
    danceability,
    valence
FROM
    songs
    JOIN artists ON artists.id = artist_id
WHERE energy < (
    SELECT AVG(energy) FROM songs
) AND danceability < (
    SELECT AVG(danceability) FROM songs
) and valence < (
    SELECT AVG(valence) FROM songs
);

