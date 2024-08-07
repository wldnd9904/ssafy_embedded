SELECT * FROM Orders where CustomerID > 33 and EmployeeID < 5;
select * from Orders where OrderID < 10000 and ShipperID < 5;
SELECT * FROM OrderDetails where ProductID > 14;
select CustomerName, City from Customers where CustomerID>10 and CustomerID<=50;
select * from Orders where CustomerID>=30 and CustomerID<40;
select ProductName, ProductID from Products where (not ProductID&1) and SupplierID&1;
