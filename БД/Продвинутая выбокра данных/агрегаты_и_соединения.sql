--Количество исполнителей в каждом жанре
SELECT g.name      AS genre,
       COUNT(ag.artist_id) AS artist_count
FROM Genres g
LEFT JOIN ArtistsGenres ag ON g.genre_id = ag.genre_id
GROUP BY g.genre_id, g.name;

--Количество треков в альбомах 2019–2020 годов
SELECT COUNT(t.track_id) AS track_count
FROM Tracks t
JOIN Albums a ON t.album_id = a.album_id
WHERE a.year BETWEEN 2019 AND 2020;

--Средняя продолжительность треков в каждом альбоме
SELECT a.title              AS album,
       AVG(t.duration)      AS avg_duration_seconds
FROM Albums a
JOIN Tracks t ON a.album_id = t.album_id
GROUP BY a.album_id, a.title;

--Исполнители, которые не выпускали альбомы в 2020 году
SELECT DISTINCT ar.name
FROM Artists ar
WHERE ar.artist_id NOT IN (
    SELECT aa.artist_id
    FROM ArtistsAlbums aa
    JOIN Albums a ON aa.album_id = a.album_id
    WHERE a.year = 2020
);

--Названия сборников, где есть конкретный исполнитель (например, Eminem)
SELECT DISTINCT c.title
FROM Compilations c
JOIN CompilationsTracks ct ON c.compilation_id = ct.compilation_id
JOIN Tracks t              ON ct.track_id = t.track_id
JOIN Albums a              ON t.album_id = a.album_id
JOIN ArtistsAlbums aa      ON a.album_id = aa.album_id
JOIN Artists ar            ON aa.artist_id = ar.artist_id
WHERE ar.name = 'Eminem';
