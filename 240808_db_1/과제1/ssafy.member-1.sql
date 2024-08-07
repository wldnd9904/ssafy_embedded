USE SSAFY;
-- 1. 모든 필드 출력 + id 가 3, 5번인 레코드만 출력
SELECT * FROM `MEMBER` WHERE MEMBER_ID IN (3,5);

-- 2. id, age 필드 출력, 2<=id<=5인 레코드만 출력하기 (조건에 AND 사용)
SELECT MEMBER_ID, AGE FROM `MEMBER` WHERE MEMBER_ID >= 2 AND MEMBER_ID <= 5;

-- 3. 나이가 20대인 친구들만 출력 (모든필드)
SELECT * FROM `MEMBER` WHERE AGE BETWEEN 20 AND 29;

-- 4. id가 짝수면서 age는 홀수인 친구들만 출력 (사람 이름만)
SELECT NAME FROM `MEMBER` WHERE (NOT MEMBER_ID&1) AND AGE&1;

-- 5. id를 "번호", name을 "성함", age를 "나이"로 출력 + 나이 오름차순으로 정렬
SELECT MEMBER_ID "번호", NAME "성함", AGE "나이" FROM `MEMBER` ORDER BY AGE;

-- 6. 이름 사전 순서대로 나이, 이름만 출력하기
SELECT AGE, NAME FROM `MEMBER` ORDER BY NAME;