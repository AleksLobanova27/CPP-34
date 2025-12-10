--Название и продолжительность самого длинного трека
SELECT title, duration
FROM Tracks
ORDER BY duration DESC
LIMIT 1;

--Треки с продолжительностью не менее 3,5 минут (210 секунд)
SELECT title, duration
FROM Tracks
WHERE duration >= 210;

--Названия сборников 2018–2020 гг. включительно
SELECT title
FROM Compilations
WHERE year BETWEEN 2018 AND 2020;

--Исполнители, чьё имя состоит из одного слова
SELECT name
FROM Artists
WHERE name NOT LIKE '% %';

--Названия треков, в которых есть слова «мой» или «my»
SELECT title
FROM Tracks
WHERE LOWER(title) LIKE '%мой%'
   OR LOWER(title) LIKE '%my%';
