-- ЖАНРЫ
INSERT INTO Genres (name) VALUES
    ('Rock'),
    ('Pop'),
    ('Hip-Hop');

-- ИСПОЛНИТЕЛИ
INSERT INTO Artists (name) VALUES
    ('Metallica'),
    ('Adele'),
    ('Eminem'),
    ('Imagine Dragons');

-- СВЯЗЬ ИСПОЛНИТЕЛИ–ЖАНРЫ
INSERT INTO ArtistsGenres (artist_id, genre_id) VALUES
    (1, 1), -- Metallica - Rock
    (2, 2), -- Adele - Pop
    (3, 3), -- Eminem - Hip-Hop
    (4, 1), -- Imagine Dragons - Rock
    (4, 2); -- Imagine Dragons - Pop

-- АЛЬБОМЫ
INSERT INTO Albums (title, year) VALUES
    ('Master of Puppets', 1986),
    ('25', 2015),
    ('Revival', 2017),
    ('Collab 2020', 2020);  -- совместный альбом

-- СВЯЗЬ ИСПОЛНИТЕЛИ–АЛЬБОМЫ
INSERT INTO ArtistsAlbums (artist_id, album_id) VALUES
    (1, 1),  -- Metallica - Master of Puppets
    (2, 2),  -- Adele - 25
    (3, 3),  -- Eminem - Revival
    (1, 4),  -- Metallica - Collab 2020
    (3, 4);  -- Eminem   - Collab 2020

-- ТРЕКИ (duration — в секундах)
INSERT INTO Tracks (title, duration, album_id) VALUES
    ('Battery',             312, 1), -- 5:12
    ('Master of Puppets',   515, 1), -- 8:35
    ('Hello',               295, 2), -- 4:55
    ('Send My Love',        223, 2), -- 3:43
    ('My Name Is',          268, 3), -- 4:28
    ('River',               224, 3), -- 3:44
    ('Our Collab My Track', 210, 4), -- 3:30
    ('Finale 2020',         260, 4); -- 4:20

-- СБОРНИКИ
INSERT INTO Compilations (title, year) VALUES
    ('Rock Collection 2018',     2018),
    ('Best Ballads 2019',        2019),
    ('Rap Hits 2020',            2020),
    ('My Favorites 2021',        2021);

-- СВЯЗЬ СБОРНИКИ–ТРЕКИ
INSERT INTO CompilationsTracks (compilation_id, track_id) VALUES
    (1, 1), -- Rock Collection 2018: Battery
    (1, 2), -- Rock Collection 2018: Master of Puppets
    (2, 3), -- Best Ballads 2019: Hello
    (2, 4), -- Best Ballads 2019: Send My Love
    (3, 5), -- Rap Hits 2020: My Name Is
    (3, 6), -- Rap Hits 2020: River
    (4, 2), -- My Favorites 2021: Master of Puppets
    (4, 5); -- My Favorites 2021: My Name Is
