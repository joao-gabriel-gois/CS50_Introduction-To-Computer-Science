-- Seeding Books
INSERT INTO books (title, published, rating)
VALUES (
  "Ensaio sobre a Lucidez",
  "2004",
  4.8
);
INSERT INTO books (title, published, rating)
VALUES (
  "Ensaio sobre a Cegueira",
  "1995",
  4.9
);
INSERT INTO books (title, published, rating)
VALUES (
  "As intermitências da Morte",
  "2005",
  5
);
INSERT INTO books (title, published, rating)
VALUES (
  "Capitães da Areia",
  "1937",
  4.7
);
INSERT INTO books (title, published, rating)
VALUES (
  "A Morte e a Morte de Quincas berro D'Água",
  "1959",
  4.9
);
INSERT INTO books (title, published, rating)
VALUES (
  "O Capital",
  "1867",
  5
);

--Seeding Authors
INSERT INTO authors (name, birthday)
VALUES (
  'José Saramago',
  '16-11-1922'
);
INSERT INTO authors (name, birthday)
VALUES (
  'Jorge Amado',
  '10-08-1912'
);
INSERT INTO authors (name, birthday)
VALUES (
  'Karl Marx',
  '05-05-1818'
);

--Seeding authored many-to-many relational table
--  using nested queries in order to find correct IDs dynamically
INSERT INTO authored (author_id, book_id)
VALUES (
  (SELECT id FROM authors WHERE name = 'José Saramago'),
  (SELECT id FROM books WHERE title = 'Ensaio sobre a Lucidez')
);
INSERT INTO authored (author_id, book_id)
VALUES (
  (SELECT id FROM authors WHERE name = 'José Saramago'),
  (SELECT id FROM books WHERE title = 'Ensaio sobre a Cegueira')
);
INSERT INTO authored (author_id, book_id)
VALUES (
  (SELECT id FROM authors WHERE name = 'José Saramago'),
  (SELECT id FROM books WHERE title = 'As intermitências da Morte')
);
INSERT INTO authored (author_id, book_id)
VALUES (
  (SELECT id FROM authors WHERE name = 'Jorge Amado'),
  (SELECT id FROM books WHERE title = 'Capitães da Areia')
);
INSERT INTO authored (author_id, book_id)
VALUES (
  (SELECT id FROM authors WHERE name = 'Jorge Amado'),
  (SELECT id FROM books WHERE title = "A Morte e a Morte de Quincas berro D'Água")
);
INSERT INTO authored (author_id, book_id)
VALUES (
  (SELECT id FROM authors WHERE name = 'Karl Marx'),
  (SELECT id FROM books WHERE title = 'O Capital')
);

