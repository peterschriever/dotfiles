SELECT
  1 as CONTRACT,
  TO_CHAR(CONTRACTDATE, 'HH24')as HourOfTheDay,
  TO_CHAR(CONTRACTDATE, 'DAY') as DayOfTheWeek,
  TO_CHAR(CONTRACTDATE, 'IW') as WeekNumber,
  TO_CHAR(CONTRACTDATE, 'DDD') as DayNumber,
  TO_CHAR(CONTRACTDATE, 'MON') as MonthOfTheYear,
  TO_CHAR(CONTRACTDATE, 'YYYY-MM-DD') AS ContractDate,
  F_MEDIAEXPOSURERATING(CONTRACTDATE) AS ExposureRating
FROM CONTRACTS