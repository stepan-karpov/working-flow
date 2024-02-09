CREATE TABLE IF NOT EXISTS customers (
  id int PRIMARY KEY,
  first_name varchar(100),
  last_name varchar(100),
  age int,
  country varchar(100)
);


INSERT INTO customers (id, first_name, last_name, age, country) VALUES 
(1,	'John',	  'Doe',	      31,	'USA'),
(2,	'Robert',	'Luna',	      22,	'USA'),
(3,	'David',	'Robinson',	  22,	'UK'),
(4,	'John',	  'Reinhardt',	25,	'UK'),
(5,	'Betty',	'Doe',	      28,	'UAE');

SELECT * FROM customers;