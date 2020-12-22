-- -------------------------------------
-- DBS211 - Lab 05
-- Name: Uliana Rozzhyvaikina
-- StudentID: 132294190
-- Date: 06/18/2020
-- -------------------------------------

SET AUTOCOMMIT ON; 
--1
CREATE TABLE L5_MOVIES (
    movieid  INT PRIMARY KEY,
    title  VARCHAR(35) NOT NULL,
    releaseYear INT NOT NULL,
    director INT NOT NULL,
    score DECIMAL(3,2),
    CONSTRAINT SCORE_chk CHECK (SCORE <= 5 AND SCORE > 0)
);
    CREATE TABLE L5_ACTORS (
    actorid int NOT NULL PRIMARY KEY,
    firstname varchar (30) NOT NULL,
    lastName varchar (30) NOT NULL
    );
    CREATE TABLE L5_CASTINGS (
    movieid INT NOT NULL,
    actorid int NOT NULL ,
    CONSTRAINT PK_CAST PRIMARY KEY (movieid, actorid),
    CONSTRAINT movieid_fk FOREIGN KEY (movieid) REFERENCES L5_MOVIES(movieid),
    CONSTRAINT actorid_fk  FOREIGN KEY (actorid) REFERENCES L5_ACTORS(actorid));
    
    CREATE TABLE L5_DIRECTORS (
    directorid int  PRIMARY KEY,
    firstname varchar(20) NOT NULL,
    lastname varchar(30) NOT NULL
    );
    
 --2
    ALTER TABLE L5_MOVIES 
    ADD CONSTRAINT fk_d 
    FOREIGN KEY (director) REFERENCES L5_DIRECTORS(directorid);
    
    --3
     ALTER TABLE L5_MOVIES 
    ADD CONSTRAINT unique_t
    UNIQUE (title);
    
    --4
    INSERT ALL
    INTO l5_directors VALUES ( 1010, 'Rob', 'Minkoff')
    INTO l5_directors VALUES ( 1020, 'Bill', 'Condon')
    INTO l5_directors VALUES ( 1050, 'Josh', 'Cooley')
    INTO l5_directors VALUES ( 2010, 'Brad', 'Bird')
    INTO l5_directors VALUES ( 3020, 'Lake', 'Bell')
    SELECT * FROM DUAL;
    
   INSERT ALL
   INTO l5_movies VALUES (100, 'The Lion King' , 2019, 3020, 3.50)
   INTO l5_movies VALUES (200 ,'Beauty and the Beast', 2017, 1050, 4.20)
   INTO l5_movies VALUES (300, 'Toy Story 4', 2019, 1020, 4.50)
   INTO l5_movies VALUES( 400, 'Mission Impossible', 2018, 2010, 5.00)
   INTO l5_movies VALUES (500, 'The Secret Life of Pets', 2016, 1010, 3.90)
   SELECT * FROM DUAL;
   

    --5 
    DROP TABLE l5_directors Cascade Constraints;
    DROP TABLE l5_castings Cascade Constraints;
    DROP TABLE l5_actors Cascade Constraints;
    DROP TABLE l5_movies Cascade Constraints;
-- The order is important due to integrity( PK FK) and contraints. If we will delete it in a wrong order
--it can leave orphaned records an break the data.

--6
CREATE TABLE employee2
  AS (SELECT * FROM employees);
  
  --7
  ALTER TABLE employee2
  ADD username varchar(30);
  
  --8
 TRUNCATE TABLE employee2;
 
 --9
 INSERT ALL INTO employee2 (employeenumber, lastname, firstname,extension,
 email, officecode, reportsto, jobtitle)
 SELECT * FROM employees;
 
 --10
 
 UPDATE employee2 
 SET firstname = 'Uliana',
     lastname ='Rozzhyvaikina'
     WHERE employeenumber = 1002;
 --11
 
INSERT INTO employee2 (username)
SELECT CONCAT(SUBSTR(firstname, 1, 1), lastname)
FROM employee2;

 
 --12
 DELETE FROM employee2
 WHERE officecode =4;
 
 --13
 DROP TABLE employee2;
 