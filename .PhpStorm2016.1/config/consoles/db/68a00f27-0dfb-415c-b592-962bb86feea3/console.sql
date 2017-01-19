SELECT
  EVENTS.ID AS EVENT,
  STUDENTS.NAME AS WAITER,
  ORDERS.ID AS ORDER_ID,
  ORDERITEMS.ID AS ORDERITEM,
  ITEMS.TYPE AS TYPE_OF_CONSUMPTION,
  ORDERS.DATEORDER AS "DATE",
  TO_NUMBER(TO_CHAR(ORDERS.DATEORDER, 'IW')) AS WEEK,
  TO_CHAR(ORDERS.DATEORDER, 'DAY') AS DAY
FROM
  EVENTS
JOIN SCHEDULES
  ON EVENTS.ID = SCHEDULES.EVENTS_ID
JOIN APPLIES
  ON SCHEDULES.ID = APPLIES.SCHEDULES_ID
JOIN STUDENTS
  ON APPLIES.STUDENTS_ID = STUDENTS.ID
JOIN ORDERS
  ON STUDENTS.ID = ORDERS.STUDENTS_ID
JOIN ORDERITEMS
  ON ORDERS.ID = ORDERITEMS.ORDERS_ID
JOIN ITEMS
  ON ORDERITEMS.ITEMS_ID = ITEMS.ID
WHERE
  APPLIES.CAPACITY = 'WAITER'
GROUP BY EVENTS.ID, STUDENTS.NAME, ORDERS.ID, ORDERITEMS.ID, ITEMS.TYPE, ORDERS.DATEORDER;