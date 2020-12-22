-- -------------------------------------
-- DBS211 - Lab 03
-- Name: Uliana Rozzhyvaikina
-- StudentID: 132294190
-- Date: 06/11/2020
-- -------------------------------------

--1.A
SELECT  employeenumber, firstname, lastname , city, phone, postalcode
FROM employees, offices
WHERE  employees .officecode = offices.officecode
AND offices.officecode ='4';

--1.B
SELECT  employeenumber, firstname, lastname, city, phone, postalcode
FROM employees  JOIN offices 
ON employees .officecode = offices.officecode 
AND employees.officecode='4';
--2 
SELECT c.customernumber, c.customername,TO_CHAR(p.paymentdate, 'mon dd, yyyy') , p.amount
FROM customers c JOIN payments p
ON c.customernumber = p.customernumber
AND c.country ='Canada'
ORDER BY c.customername;

--3
SELECT c.customernumber, c.customername
FROM customers c
LEFT JOIN payments p ON p.customernumber = c.customernumber
WHERE p.customernumber IS NULL and c.country = 'USA'
ORDER BY c.customernumber;


--4.a
CREATE OR REPLACE VIEW vwCustomerOrder AS
(SELECT o.customernumber, od.ordernumber, o.orderdate,
p.productname,od.quantityordered, od.priceeach
FROM orders o INNER JOIN orderdetails od ON o.ordernumber = od.ordernumber
JOIN products p ON od.productcode = p.productcode );
--4.b
SELECT * FROM vwcustomerorder;

--5
CREATE OR REPLACE VIEW vwCustomerOrder AS
SELECT o.customernumber, od.ordernumber, o.orderdate,
p.productname,od.quantityordered, od.priceeach, od.orderlinenumber
FROM orders o INNER JOIN orderdetails od ON o.ordernumber = od.ordernumber
JOIN products p ON od.productcode = p.productcode
WHERE customernumber ='124'
ORDER BY ordernumber, orderlinenumber;
SELECT * FROM vwcustomerorder;
--6
SELECT  c.customernumber, c.contactlastname , c.contactfirstname, c.phone, c.creditlimit
FROM customers c LEFT JOIN orders o
ON c.customernumber = o.customernumber
WHERE o.ordernumber IS NULL;

--7
CREATE OR REPLACE VIEW vwEmployeeManager AS
(SELECT e.*, emp.firstname AS managerFirstName, 
emp.lastname AS managerLastName
FROM employees e JOIN employees emp
ON e.reportsto = emp.employeenumber OR emp.reportsto is NULL);
SELECT * FROM vwemployeemanager;
--8
CREATE OR REPLACE VIEW vwEmployeeManager AS
(SELECT e.*, emp.firstname AS managerFirstName, 
emp.lastname AS managerLastName
FROM employees e JOIN employees emp
ON e.reportsto = emp.employeenumber);

--9
DROP VIEW vwEmployeeManager;
DROP VIEW vwCustomerOrder;
