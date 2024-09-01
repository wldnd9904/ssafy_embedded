## API 명세

다음과 같이 api를 호출합니다.

```
import api from "./api.js";
```

## 1. 모든 주문 목록 조회

```
api.orders.findAll();
```

- 설명: 모든 주문과 연관된 메뉴 정보를 조회합니다.
- 매개변수: 없음
- 응답:
  - **200 OK**: 다음 필드를 포함하는 주문 객체의 배열:
    - id (문자열): 주문의 고유 식별자
    - quantity (숫자): 주문 수량
    - request_detail (문자열): 추가 요청 사항
    - menu (객체): 주문과 연관된 메뉴 객체
    - menu_id (객체): 메뉴 ID를 포함하는 객체

## 2. 특정 주문 조회

```
api.orders.findOne(id);
```

- 설명: ID로 단일 주문을 조회하며, 메뉴 정보도 포함됩니다.
- 매개변수:
  - id (문자열): 주문의 고유 식별자
- 응답:
  - **200 OK**: 다음 필드를 포함하는 주문 객체:
    - id (문자열): 주문의 고유 식별자
    - quantity (숫자): 주문 수량
    - request_detail (문자열): 추가 요청 사항
    - menu (객체): 주문과 연관된 메뉴 객체
    - menu_id (객체): 메뉴 ID를 포함하는 객체
  - **404 Not Found**: 주문이 존재하지 않는 경우

## 3. 주문 생성

```
api.orders.create(quantity, requestDetail, menuId);
```

- 설명: 새로운 주문을 생성합니다.
- 매개변수:
  - quantity (숫자): 주문 수량
  - requestDetail (문자열): 추가 요청 사항
  - menuId (문자열): 주문할 메뉴의 ID
- 응답:
  - **201 Created**: 주문 생성 확인
  - **400 Bad Request**: 생성 중 오류가 발생한 경우

## 4. 주문 수정

```
api.orders.update(orderId, quantity, requestDetail, menuId);
```

- 설명: 주문을 수정합니다.
- 매개변수:
  - orderId (문자열): 주문의 고유 식별자
  - quantity (숫자): 수정할 주문 수량
  - requestDetail (문자열): 수정할 추가 요청 사항
  - menuId (문자열): 수정할 메뉴 ID
- 응답:
  - **200 OK**: 주문 수정 확인
  - **404 Not Found**: 주문이 존재하지 않는 경우
  - **400 Bad Request**: 수정 중 오류가 발생한 경우

## 5. 주문 삭제

```
api.orders.delete(order);
```

- 설명: 주문을 삭제합니다.
- 매개변수:
  - order (객체): 삭제할 주문
- 응답:
  - **200 OK**: 주문 삭제 확인
  - **404 Not Found**: 주문이 존재하지 않는 경우
  - **400 Bad Request**: 삭제 중 오류가 발생한 경우
