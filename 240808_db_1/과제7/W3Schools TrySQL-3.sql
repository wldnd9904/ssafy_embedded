select * from OrderDetails where cast(ProductID as char) like "1%";

select * from OrderDetails
where floor(ProductID/10)%10 = 1;