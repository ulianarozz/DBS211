-- -------------------------------------
-- DBS211 - Lab 03
-- Name: Uliana Rozzhyvaikina
-- StudentID: 132294190
-- Date: 06/04/2020
-- -------------------------------------

SET AUTOCOMMIT ON;
/*1*/ SELECT * FROM offices;
/*2*/  SELECT employeenumber, officecode
FROM employees
WHERE officecode =1;
/*3*/ SELECT customernumber, customername, contactlastname, phone, city
FROM customers
WHERE city = 'Paris';
/*4a*/  SELECT contactlastname || ', ' || contactfirstname AS fullname, customernumber,  phone, city
FROM customers
WHERE city = 'Paris';
/*4b*/ SELECT *
FROM customers
WHERE country = 'Canada';
/*5*/ SELECT DISTINCT customernumber
FROM payments;
/*6*/ SELECT customernumber, checknumber, amount
FROM payments
WHERE  (amount >=35000 and amount <=65000)
ORDER BY amount DESC;
/*7 */ SELECT *
FROM orders
WHERE status = 'Cancelled';
/*8*/  SELECT productcode, productname, buyprice, msrp, msrp-buyprice
AS markup, round(100*(msrp-buyprice)/buyprice, 1) AS percmarkup
FROM products;
/*9*/SELECT * 
FROM products
WHERE productname LIKE '%CO%' OR productname LIKE '%co%' 
OR productname LIKE '%Co%' OR productname LIKE '%cO%';
/*10*/ SELECT contactfirstname 
FROM customers 
WHERE contactfirstname LIKE 's%' OR contactfirstname LIKE 'S%' 
AND contactfirstname LIKE '%e%';
/*11*/ INSERT INTO employees 
VALUES (1535, 'Rozzhyvaikina' , 'Uliana', 'x50',
'urozzhyvaikina3@myseneca.ca', 4, 1088, 'Cashier');
/*12*/ SELECT *
FROM employees
WHERE employeenumber = 1535;

/*13*/ UPDATE employees SET jobtitle = 'Head Cashier'
WHERE employeenumber = 1535;

/*14*/ INSERT INTO employees VALUES
(1246, 'McKing', 'Ariela', 'x178', 'arielam@classicmodelcars.com', 6, 1535, 'Cashier');

/*15*/ DELETE FROM employees
WHERE  employeenumber= 1535;
/*I can not delete myself due to integrity. The system found child record (employee who report to me)*/

/*16*/ DELETE FROM employees
WHERE  employeenumber= 1246;
DELETE FROM employees
WHERE  employeenumber= 1535;
/* This time I was able to delete my self after deleting my child record -employee
who reports to me*/
/*17*/ INSERT ALL 
 INTO employees VALUES (1535, 'Rozzhyvaikina' , 'Uliana', 'x50',
'urozzhyvaikina3@myseneca.ca', 4, 1088, 'Cashier')
INTO employees  VALUES (1246, 'McKing', 'Ariela', 'x178', 'arielam@classicmodelcars.com', 6, 1088, 'Cashier')
SELECT * 
FROM DUAL;
/*18*/ DELETE FROM employees
WHERE employeenumber = 1535 OR employeenumber = 1246;
