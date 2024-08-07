use world;
-- 1. 인구수가 1000명 미만이면서, A로 시작하는 도시 찾기
select * from city where Population < 1000 and `Name` like "A%";

-- 2. 일본(JPN)에서 인구수가 100만명 ~ 200만명 인 도시를 찾아 도시 이름과 국가 코드 필드만 출력
select `Name`, CountryCode from city where CountryCode="JPN" and Population between 1000000 and 2000000;

-- 3. kim이라는 글자가 포함된 도시명  찾기
select * from city where `Name` like "%kim%";

-- 4. world 스키마의 레코드 총 개수 출력
select
    (select count(*) from city) +
    (select count(*) from country) +
    (select count(*) from countrylanguage);
    
-- 5. 하위 5개의 도시 코드, 인구수 출력
select CountryCode, Population from city order by Population limit 5;

-- 6. TOP 5개의 국가 코드, 인구수 출력
select `Code`, Population from country order by Population desc limit 5;