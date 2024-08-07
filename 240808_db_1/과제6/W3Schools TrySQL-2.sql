select Address "주소", City "도시", PostalCode "우편번호" from Customers order by PostalCode desc;

select * from OrderDetails order by OrderDetailID desc limit 5;

select * from Orders order by OrderID desc limit 3, 7;

select OrderDetailID "상세주문번호", OrderID "주문번호", ProductID "상품번호", Quantity "수량"
from OrderDetails
where OrderID <= 10000 or ProductID >= 50
order by OrderDetailID desc
limit 8;