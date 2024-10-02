CREATE TABLE IF NOT EXISTS books (
    id INTEGER,
    title TEXT,
    published NUMERIC,
    rating INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE IF NOT EXISTS authors (
    id INTEGER,
    name TEXT,
    birthday NUMERIC,
    PRIMARY KEY(id)
);
CREATE TABLE IF NOT EXISTS authored (
    author_id INTEGER,
    book_id INTEGER,
    PRIMARY KEY(author_id, book_id),
    FOREIGN KEY(author_id) REFERENCES authors(id),
    FOREIGN KEY(book_id) REFERENCES books(id)
);

