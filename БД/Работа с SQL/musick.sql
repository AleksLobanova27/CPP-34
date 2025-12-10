-- ЖАНРЫ
CREATE TABLE IF NOT EXISTS Genres (
    genre_id   SERIAL PRIMARY KEY,
    name       VARCHAR(100) NOT NULL UNIQUE
);

-- ИСПОЛНИТЕЛИ
CREATE TABLE IF NOT EXISTS Artists (
    artist_id  SERIAL PRIMARY KEY,
    name       VARCHAR(150) NOT NULL
);

-- СВЯЗЬ многие-ко-многим: ИСПОЛНИТЕЛИ–ЖАНРЫ
CREATE TABLE IF NOT EXISTS ArtistsGenres (
    artist_id  INTEGER NOT NULL REFERENCES Artists(artist_id),
    genre_id   INTEGER NOT NULL REFERENCES Genres(genre_id),
    CONSTRAINT pk_artists_genres PRIMARY KEY (artist_id, genre_id)
);

-- АЛЬБОМЫ
CREATE TABLE IF NOT EXISTS Albums (
    album_id   SERIAL PRIMARY KEY,
    title      VARCHAR(200) NOT NULL,
    year       INTEGER
);

-- СВЯЗЬ многие-ко-многим: ИСПОЛНИТЕЛИ–АЛЬБОМЫ
CREATE TABLE IF NOT EXISTS ArtistsAlbums (
    artist_id  INTEGER NOT NULL REFERENCES Artists(artist_id),
    album_id   INTEGER NOT NULL REFERENCES Albums(album_id),
    CONSTRAINT pk_artists_albums PRIMARY KEY (artist_id, album_id)
);

-- ТРЕКИ (по-прежнему один альбом)
CREATE TABLE IF NOT EXISTS Tracks (
    track_id   SERIAL PRIMARY KEY,
    title      VARCHAR(200) NOT NULL,
    duration   INTEGER NOT NULL,         -- в секундах;
    album_id   INTEGER NOT NULL REFERENCES Albums(album_id)
);

-- СБОРНИКИ
CREATE TABLE IF NOT EXISTS Compilations (
    compilation_id SERIAL PRIMARY KEY,
    title          VARCHAR(200) NOT NULL,
    year           INTEGER
);

-- СВЯЗЬ многие-ко-многим: СБОРНИКИ–ТРЕКИ
CREATE TABLE IF NOT EXISTS CompilationsTracks (
    compilation_id INTEGER NOT NULL REFERENCES Compilations(compilation_id),
    track_id       INTEGER NOT NULL REFERENCES Tracks(track_id),
    CONSTRAINT pk_compilations_tracks PRIMARY KEY (compilation_id, track_id)
);

