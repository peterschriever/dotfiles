SELECT
  EXPOSUREDATE AS DateOfExposure,
  to_number(to_char(EXPOSUREDATE,'HH24')) AS HourOfExposure,
  to_char(EXPOSUREDATE,'DY') AS DayOfExposure,
  to_number(to_char(EXPOSUREDATE,'WW')) AS WeekOfExposure,
  to_number(to_char(EXPOSUREDATE,'DDD')) AS DayNumber
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT
  EXPOSUREDATE AS DateOfExposure,
  to_number(to_char(EXPOSUREDATE,'HH24')) AS HourOfExposure,
  to_char(EXPOSUREDATE,'DAY') AS DayOfExposure,
  to_number(to_char(EXPOSUREDATE,'WW')) AS WeekOfExposure,
  to_number(to_char(EXPOSUREDATE,'DDD')) AS DayNumber
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT
  EXPOSUREDATE AS DateOfExposure,
  to_number(to_char(EXPOSUREDATE,'HH24')) AS HourOfExposure,
  to_char(EXPOSUREDATE,'DAY') AS DayOfExposure,
  to_number(to_char(EXPOSUREDATE,'WW')) AS WeekOfExposure,
  to_number(to_char(EXPOSUREDATE,'DDD')) AS DayNumber,
  F_MEDIA('tv', WeekOfExposure, DayNumber, 'p') AS TvPositive
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT
  EXPOSUREDATE AS DateOfExposure,
  to_number(to_char(EXPOSUREDATE,'HH24')) AS HourOfExposure,
  to_char(EXPOSUREDATE,'DAY') AS DayOfExposure,
  to_number(to_char(EXPOSUREDATE,'WW')) AS WeekOfExposure,
  to_number(to_char(EXPOSUREDATE,'DDD')) AS DayNumber,
  F_MEDIA('tv', WeekOfExposure, 12, 'p') AS TvPositive
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT
  EXPOSUREDATE AS DateOfExposure,
  to_number(to_char(EXPOSUREDATE,'HH24')) AS HourOfExposure,
  to_char(EXPOSUREDATE,'DAY') AS DayOfExposure,
  to_number(to_char(EXPOSUREDATE,'WW')) AS WeekOfExposure,
  to_number(to_char(EXPOSUREDATE,'DDD')) AS DayNumber,
  F_MEDIA('tv', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'p') AS TvPositive
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT
  EXPOSUREDATE AS DateOfExposure,
  to_number(to_char(EXPOSUREDATE,'HH24')) AS HourOfExposure,
  to_char(EXPOSUREDATE,'DAY') AS DayOfExposure,
  to_number(to_char(EXPOSUREDATE,'WW')) AS WeekOfExposure,
  to_number(to_char(EXPOSUREDATE,'DDD')) AS DayNumber,
  F_MEDIA('tv', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'p') AS TvPositive,
  F_MEDIA('radio', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'p') AS RadioPositive,
  F_MEDIA('newspaper', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'p') AS NewspaperPositive,
  F_MEDIA('internet', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'p') AS InternetPositive,
  F_MEDIA('weekly magazine', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'p') AS WeeklyMagazinePositive,
  F_MEDIA('tv', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'n') AS TvPositive,
  F_MEDIA('radio', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'n') AS RadioPositive,
  F_MEDIA('newspaper', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'n') AS NewspaperPositive,
  F_MEDIA('internet', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'n') AS InternetPositive,
  F_MEDIA('weekly magazine', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'n') AS WeeklyMagazinePositive
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT
  EXPOSUREDATE AS DateOfExposure,
  to_number(to_char(EXPOSUREDATE,'HH24')) AS HourOfExposure,
  to_char(EXPOSUREDATE,'DAY') AS DayOfExposure,
  to_number(to_char(EXPOSUREDATE,'WW')) AS WeekOfExposure,
  to_number(to_char(EXPOSUREDATE,'DDD')) AS DayNumber,
  F_MEDIA('tv', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'p') AS TvPositive,
  F_MEDIA('radio', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'p') AS RadioPositive,
  F_MEDIA('newspaper', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'p') AS NewspaperPositive,
  F_MEDIA('internet', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'p') AS InternetPositive,
  F_MEDIA('weekly magazine', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'p') AS WeeklyMagazinePositive,
  F_MEDIA('tv', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'n') AS TvNegative,
  F_MEDIA('radio', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'n') AS RadioNegative,
  F_MEDIA('newspaper', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'n') AS NewspaperNegative,
  F_MEDIA('internet', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'n') AS InternetNegative,
  F_MEDIA('weekly magazine', to_number(to_char(EXPOSUREDATE,'WW')), to_number(to_char(EXPOSUREDATE,'DDD')),
          'n') AS WeeklyMagazinNegative
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT
  CONTRACTDATE,
  to_number(TO_CHAR(CONTRACTDATE, 'HH24')) as Hour,
  TO_CHAR(CONTRACTDATE, 'DAY') as Day,
  to_number(TO_CHAR(CONTRACTDATE, 'IW')) as Week,
  to_number(TO_CHAR(CONTRACTDATE, 'DDD')) as DayNumber,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'tv') as tv_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'radio') as radio_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'newspaper') as newspaper_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'internet') as internet_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'weekly magazine') as weekly_magazine_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'tv') as tv_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'radio') as Radio_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'newspaper') as newspaper_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'internet') as internet_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'weekly magazine') as weekly_magazine_negative
FROM CONTRACTS
;-- -. . -..- - / . -. - .-. -.--
SELECT
  CONTRACTDATE,
  TO_CHAR(CONTRACTDATE, 'HH24') as Hour,
  TO_CHAR(CONTRACTDATE, 'DAY') as Day,
  TO_CHAR(CONTRACTDATE, 'IW') as Week,
  TO_CHAR(CONTRACTDATE, 'DDD') as DayNumber,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'tv') as tv_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'radio') as radio_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'newspaper') as newspaper_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'internet') as internet_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'weekly magazine') as weekly_magazine_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'tv') as tv_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'radio') as Radio_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'newspaper') as newspaper_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'internet') as internet_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'weekly magazine') as weekly_magazine_negative
FROM CONTRACTS
;-- -. . -..- - / . -. - .-. -.--
SELECT
  CONTRACTDATE,
  TO_CHAR(TO_TIMESTAMP(CONTRACTDATE), 'HH24') as Hour,
  TO_CHAR(CONTRACTDATE, 'DAY') as Day,
  TO_CHAR(CONTRACTDATE, 'IW') as Week,
  TO_CHAR(CONTRACTDATE, 'DDD') as DayNumber,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'tv') as tv_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'radio') as radio_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'newspaper') as newspaper_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'internet') as internet_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'weekly magazine') as weekly_magazine_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'tv') as tv_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'radio') as radio_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'newspaper') as newspaper_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'internet') as internet_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'weekly magazine') as weekly_magazine_negative
FROM CONTRACTS
;-- -. . -..- - / . -. - .-. -.--
SELECT
  CONTRACTDATE,
  TO_CHAR(TO_TIMESTAMP(CONTRACTDATE), 'HH24') as Hour,
  TO_CHAR(TO_TIMESTAMP(CONTRACTDATE), 'DAY') as Day,
  TO_CHAR(TO_TIMESTAMP(CONTRACTDATE), 'IW') as Week,
  TO_CHAR(TO_TIMESTAMP(CONTRACTDATE), 'DDD') as DayNumber,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'tv') as tv_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'radio') as radio_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'newspaper') as newspaper_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'internet') as internet_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'weekly magazine') as weekly_magazine_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'tv') as tv_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'radio') as radio_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'newspaper') as newspaper_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'internet') as internet_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'weekly magazine') as weekly_magazine_negative
FROM CONTRACTS
;-- -. . -..- - / . -. - .-. -.--
SELECT
  CONTRACTDATE,
  TO_CHAR(CONTRACTDATE, 'HH24') as Hour,
  TO_CHAR(CONTRACTDATE, 'DAY') as Day,
  TO_CHAR(CONTRACTDATE, 'IW') as Week,
  TO_CHAR(CONTRACTDATE, 'DDD') as DayNumber,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'tv') as tv_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'radio') as radio_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'newspaper') as newspaper_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'internet') as internet_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'p', 'weekly magazine') as weekly_magazine_positive,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'tv') as tv_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'radio') as radio_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'newspaper') as newspaper_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'internet') as internet_negative,
  F_MEDIA(to_date(CONTRACTDATE, 'YYYY-MM-DD'), 'n', 'weekly magazine') as weekly_magazine_negative
FROM CONTRACTS
;-- -. . -..- - / . -. - .-. -.--
SELECT
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'YYYY-MM-DD')as CurDate,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'HH24')as CurHour,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'DAY')as CurDay,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'IW')as CurWeek,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'D')as CurDayNumber,
  F_MEDIA(CONTRACTDATE,'p','tv') as tv_positive,
  F_MEDIA(CONTRACTDATE,'p','radio') as radio_positive,
  F_MEDIA(CONTRACTDATE,'p','newspaper') as newspaper_positive,
  F_MEDIA(CONTRACTDATE,'p','internet') as internet_positive,
  F_MEDIA(CONTRACTDATE,'p','weeklymagazine') as weekly_magazine_positive,
  F_MEDIA(CONTRACTDATE,'n','tv') as tv_negative,
  F_MEDIA(CONTRACTDATE,'n','radio') as Radio_negative,
  F_MEDIA(CONTRACTDATE,'n','newspaper') as newspaper_negative,
  F_MEDIA(CONTRACTDATE,'n','internet') as internet_negative,
  F_MEDIA(CONTRACTDATE,'n','weeklymagazine') as weekly_magazine_negative
FROM CONTRACTS
;-- -. . -..- - / . -. - .-. -.--
SELECT
  to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'DDD') AS MediaDayNumber,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'tv') AS TV_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'tv') AS TV_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'internet') AS INTERNET_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'internet') AS INTERNET_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'newspaper') AS NEWSPAPER_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'newspaper') AS NEWSPAPER_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'radio') AS RADIO_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'radio') AS RADIO_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'weekly magazine') AS MAGAZINE_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'weekly magazine') AS MAGAZINE_NEGATIVE
FROM
  MEDIA
GROUP BY to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON'), MEDIA.MEDIADATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON') AS MEDIAMONTH,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'tv') AS TV_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'tv') AS TV_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'internet') AS INTERNET_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'internet') AS INTERNET_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'newspaper') AS NEWSPAPER_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'newspaper') AS NEWSPAPER_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'radio') AS RADIO_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'radio') AS RADIO_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'weekly magazine') AS MAGAZINE_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'weekly magazine') AS MAGAZINE_NEGATIVE
FROM
  MEDIA
GROUP BY to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON'), MEDIA.MEDIADATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON') AS MEDIAMONTH,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'tv') AS TV_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'tv') AS TV_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'internet') AS INTERNET_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'internet') AS INTERNET_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'newspaper') AS NEWSPAPER_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'newspaper') AS NEWSPAPER_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'radio') AS RADIO_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'radio') AS RADIO_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'weekly magazine') AS MAGAZINE_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'weekly magazine') AS MAGAZINE_NEGATIVE
FROM
  MEDIA
GROUP BY to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON')
;-- -. . -..- - / . -. - .-. -.--
MEDIA.MEDIADATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  DISTINCT to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON') AS MEDIAMONTH,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'tv') AS TV_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'tv') AS TV_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'internet') AS INTERNET_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'internet') AS INTERNET_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'newspaper') AS NEWSPAPER_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'newspaper') AS NEWSPAPER_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'radio') AS RADIO_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'radio') AS RADIO_NEGATIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'p', 'weekly magazine') AS MAGAZINE_POSITIVE,
  F_MEDIA(MEDIA.MEDIADATE, 'n', 'weekly magazine') AS MAGAZINE_NEGATIVE
FROM
  MEDIA
GROUP BY to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON'), MEDIA.MEDIADATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON') AS MEDIAMONTH,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'tv')) AS TV_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'tv')) AS TV_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'internet')) AS INTERNET_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'internet')) AS INTERNET_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'newspaper')) AS NEWSPAPER_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'newspaper')) AS NEWSPAPER_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'radio')) AS RADIO_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'radio')) AS RADIO_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'weekly magazine')) AS MAGAZINE_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'weekly magazine')) AS MAGAZINE_NEGATIVE
FROM
  MEDIA
GROUP BY to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON'), MEDIA.MEDIADATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON') AS MEDIAMONTH,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'tv')) AS TV_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'internet')) AS INTERNET_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'newspaper')) AS NEWSPAPER_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'radio')) AS RADIO_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'weekly magazine')) AS MAGAZINE_POSITIVE,

  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'tv')) AS TV_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'internet')) AS INTERNET_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'newspaper')) AS NEWSPAPER_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'radio')) AS RADIO_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'weekly magazine')) AS MAGAZINE_NEGATIVE
FROM
  MEDIA
GROUP BY to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON'), MEDIA.MEDIADATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'YEAR') AS MEDIAYEAR,
  to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON') AS MEDIAMONTH,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'tv')) AS TV_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'internet')) AS INTERNET_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'newspaper')) AS NEWSPAPER_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'radio')) AS RADIO_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'weekly magazine')) AS MAGAZINE_POSITIVE,

  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'tv')) AS TV_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'internet')) AS INTERNET_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'newspaper')) AS NEWSPAPER_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'radio')) AS RADIO_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'weekly magazine')) AS MAGAZINE_NEGATIVE
FROM
  MEDIA
GROUP BY to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON'), MEDIA.MEDIADATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'YYYY') AS MEDIAYEAR,
  to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON') AS MEDIAMONTH,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'tv')) AS TV_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'internet')) AS INTERNET_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'newspaper')) AS NEWSPAPER_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'radio')) AS RADIO_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'weekly magazine')) AS MAGAZINE_POSITIVE,

  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'tv')) AS TV_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'internet')) AS INTERNET_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'newspaper')) AS NEWSPAPER_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'radio')) AS RADIO_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'weekly magazine')) AS MAGAZINE_NEGATIVE
FROM
  MEDIA
GROUP BY to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON'), MEDIA.MEDIADATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  -- 21-6-2013
  to_char(TO_DATE(MEDIA.MEDIADATE, 'DD-MM-YYYY'), 'YYYY') AS MEDIAYEAR,
--   to_char(TO_DATE(MEDIA.MEDIADATE, 'DD-MM-YYYY'), 'MON') AS MEDIAMONTH,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'tv')) AS TV_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'internet')) AS INTERNET_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'newspaper')) AS NEWSPAPER_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'radio')) AS RADIO_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'weekly magazine')) AS MAGAZINE_POSITIVE,

  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'tv')) AS TV_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'internet')) AS INTERNET_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'newspaper')) AS NEWSPAPER_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'radio')) AS RADIO_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'weekly magazine')) AS MAGAZINE_NEGATIVE
FROM
  MEDIA
GROUP BY to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON'), MEDIA.MEDIADATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  -- 21-6-2013
  to_char(TO_DATE(MEDIA.MEDIADATE, 'DD-MM-YYYY'), 'YYYY') AS MEDIAYEAR,
--   to_char(TO_DATE(MEDIA.MEDIADATE, 'DD-MM-YYYY'), 'MON') AS MEDIAMONTH,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'tv')) AS TV_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'internet')) AS INTERNET_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'newspaper')) AS NEWSPAPER_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'radio')) AS RADIO_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'weekly magazine')) AS MAGAZINE_POSITIVE,

  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'tv')) AS TV_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'internet')) AS INTERNET_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'newspaper')) AS NEWSPAPER_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'radio')) AS RADIO_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'weekly magazine')) AS MAGAZINE_NEGATIVE
FROM
  MEDIA
GROUP BY MEDIA.MEDIADATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  -- 21-6-2013
  to_char(TO_DATE(MEDIA.MEDIADATE, 'DD-MM-YYYY'), 'YYYY') AS MEDIAYEAR,
  to_char(TO_DATE(MEDIA.MEDIADATE, 'DD-MM-YYYY'), 'MON') AS MEDIAMONTH,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'tv')) AS TV_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'internet')) AS INTERNET_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'newspaper')) AS NEWSPAPER_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'radio')) AS RADIO_POSITIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'p', 'weekly magazine')) AS MAGAZINE_POSITIVE,

  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'tv')) AS TV_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'internet')) AS INTERNET_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'newspaper')) AS NEWSPAPER_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'radio')) AS RADIO_NEGATIVE,
  SUM(F_MEDIA(MEDIA.MEDIADATE, 'n', 'weekly magazine')) AS MAGAZINE_NEGATIVE
FROM
  MEDIA
GROUP BY to_char(TO_DATE(MEDIA.MEDIADATE, 'YYYY-MM-DD HH24:mi:ss'), 'MON'), MEDIA.MEDIADATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'YYYY-MM-DD')as ContractDate,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'HH24')as HourOfTheDay,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'DAY')as DayOfTheWeek,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'IW')as WeekNumber,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'DDD')as DayNumber,
  F_MEDIA(TO_DATE(CONTRACTDATE, 'YYYY-MM-DD HH24:MI:SS'), 'p','tv') as tv_positive,
  F_MEDIA(TO_DATE(CONTRACTDATE, 'YYYY-MM-DD HH24:MI:SS'), 'p','radio') as radio_positive,
  F_MEDIA(TO_DATE(CONTRACTDATE, 'YYYY-MM-DD HH24:MI:SS'), 'p','newspaper') as newspaper_positive,
  F_MEDIA(TO_DATE(CONTRACTDATE, 'YYYY-MM-DD HH24:MI:SS'), 'p','internet') as internet_positive,
  F_MEDIA(TO_DATE(CONTRACTDATE, 'YYYY-MM-DD HH24:MI:SS'), 'p','weeklymagazine') as weekly_magazine_positive,
  F_MEDIA(TO_DATE(CONTRACTDATE, 'YYYY-MM-DD HH24:MI:SS'), 'n','tv') as tv_negative,
  F_MEDIA(TO_DATE(CONTRACTDATE, 'YYYY-MM-DD HH24:MI:SS'), 'n','radio') as Radio_negative,
  F_MEDIA(TO_DATE(CONTRACTDATE, 'YYYY-MM-DD HH24:MI:SS'), 'n','newspaper') as newspaper_negative,
  F_MEDIA(TO_DATE(CONTRACTDATE, 'YYYY-MM-DD HH24:MI:SS'), 'n','internet') as internet_negative,
  F_MEDIA(TO_DATE(CONTRACTDATE, 'YYYY-MM-DD HH24:MI:SS'), 'n','weeklymagazine') as weekly_magazine_negative
FROM CONTRACTS
;-- -. . -..- - / . -. - .-. -.--
SELECT
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'YYYY-MM-DD')as ContractDate,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'HH24')as HourOfTheDay,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'DAY')as DayOfTheWeek,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'IW')as WeekNumber,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'DDD')as DayNumber,
  F_MEDIA(TO_TIMESTAMP(CONTRACTDATE), 'p','tv') as tv_positive,
  F_MEDIA(TO_TIMESTAMP(CONTRACTDATE), 'p','radio') as radio_positive,
  F_MEDIA(TO_TIMESTAMP(CONTRACTDATE), 'p','newspaper') as newspaper_positive,
  F_MEDIA(TO_TIMESTAMP(CONTRACTDATE), 'p','internet') as internet_positive,
  F_MEDIA(TO_TIMESTAMP(CONTRACTDATE), 'p','weeklymagazine') as weekly_magazine_positive,
  F_MEDIA(TO_TIMESTAMP(CONTRACTDATE), 'n','tv') as tv_negative,
  F_MEDIA(TO_TIMESTAMP(CONTRACTDATE), 'n','radio') as Radio_negative,
  F_MEDIA(TO_TIMESTAMP(CONTRACTDATE), 'n','newspaper') as newspaper_negative,
  F_MEDIA(TO_TIMESTAMP(CONTRACTDATE), 'n','internet') as internet_negative,
  F_MEDIA(TO_TIMESTAMP(CONTRACTDATE), 'n','weeklymagazine') as weekly_magazine_negative
FROM CONTRACTS
;-- -. . -..- - / . -. - .-. -.--
SELECT
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'YYYY-MM-DD')as ContractDate,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'HH24')as HourOfTheDay,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'DAY')as DayOfTheWeek,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'IW')as WeekNumber,
  TO_CHAR(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'DDD')as DayNumber,
  F_MEDIA(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'p','tv') as tv_positive,
  F_MEDIA(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'p','radio') as radio_positive,
  F_MEDIA(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'p','newspaper') as newspaper_positive,
  F_MEDIA(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'p','internet') as internet_positive,
  F_MEDIA(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'p','weeklymagazine') as weekly_magazine_positive,
  F_MEDIA(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'n','tv') as tv_negative,
  F_MEDIA(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'n','radio') as Radio_negative,
  F_MEDIA(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'n','newspaper') as newspaper_negative,
  F_MEDIA(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'n','internet') as internet_negative,
  F_MEDIA(TO_DATE(substr(CONTRACTDATE,0,19), 'YYYY-MM-DD HH24:MI:SS'), 'n','weeklymagazine') as weekly_magazine_negative
FROM CONTRACTS
;-- -. . -..- - / . -. - .-. -.--
SELECT count(*) INTO output
FROM MEDIA
WHERE
  TO_DATE(MEDIA.MEDIADATE, 'DD-MM-YYYY') = TO_CHAR(P_DATE, 'YYYY-MM-DD')
  AND
  MEDIA.EXPOSURERESULT = P_INFLUENCE
  AND
  (MEDIA.KIND = P_MEDIATYPE OR MEDIA.KIND = 'All')
;-- -. . -..- - / . -. - .-. -.--
SELECT
  TO_CHAR(CONTRACTDATE, 'YYYY-MM-DD') as ContractDate,
  TO_CHAR(CONTRACTDATE, 'HH24') as HourOfTheDay,
  TO_CHAR(CONTRACTDATE, 'DAY') as DayOfTheWeek,
  TO_CHAR(CONTRACTDATE, 'IW') as WeekNumber,
  TO_CHAR(CONTRACTDATE, 'DDD') as DayNumber,

  F_MEDIA(CONTRACTDATE, 'p','tv') as tv_positive,
  F_MEDIA(CONTRACTDATE, 'p','radio') as radio_positive,
  F_MEDIA(CONTRACTDATE, 'p','newspaper') as newspaper_positive,
  F_MEDIA(CONTRACTDATE, 'p','internet') as internet_positive,
  F_MEDIA(CONTRACTDATE, 'p','weeklymagazine') as weekly_magazine_positive,

  F_MEDIA(CONTRACTDATE, 'n','tv') as tv_negative,
  F_MEDIA(CONTRACTDATE, 'n','radio') as Radio_negative,
  F_MEDIA(CONTRACTDATE, 'n','newspaper') as newspaper_negative,
  F_MEDIA(CONTRACTDATE, 'n','internet') as internet_negative,
  F_MEDIA(CONTRACTDATE, 'n','weeklymagazine') as weekly_magazine_negative
FROM CONTRACTS
;-- -. . -..- - / . -. - .-. -.--
SELECT
  TO_CHAR(CONTRACTDATE, 'MON') as Month,
--   TO_CHAR(CONTRACTDATE, 'HH24') as HourOfTheDay,
--   TO_CHAR(CONTRACTDATE, 'DAY') as DayOfTheWeek,
--   TO_CHAR(CONTRACTDATE, 'IW') as WeekNumber,
--   TO_CHAR(CONTRACTDATE, 'DDD') as DayNumber,

  F_MEDIA(CONTRACTDATE, 'p','tv') as tv_positive,
  F_MEDIA(CONTRACTDATE, 'p','radio') as radio_positive,
  F_MEDIA(CONTRACTDATE, 'p','newspaper') as newspaper_positive,
  F_MEDIA(CONTRACTDATE, 'p','internet') as internet_positive,
  F_MEDIA(CONTRACTDATE, 'p','weeklymagazine') as weekly_magazine_positive,

  F_MEDIA(CONTRACTDATE, 'n','tv') as tv_negative,
  F_MEDIA(CONTRACTDATE, 'n','radio') as Radio_negative,
  F_MEDIA(CONTRACTDATE, 'n','newspaper') as newspaper_negative,
  F_MEDIA(CONTRACTDATE, 'n','internet') as internet_negative,
  F_MEDIA(CONTRACTDATE, 'n','weeklymagazine') as weekly_magazine_negative
FROM CONTRACTS
GROUP BY TO_CHAR(CONTRACTDATE, 'MON')
;-- -. . -..- - / . -. - .-. -.--
SELECT
  TO_CHAR(CONTRACTDATE, 'MON') as Month,
--   TO_CHAR(CONTRACTDATE, 'HH24') as HourOfTheDay,
--   TO_CHAR(CONTRACTDATE, 'DAY') as DayOfTheWeek,
--   TO_CHAR(CONTRACTDATE, 'IW') as WeekNumber,
--   TO_CHAR(CONTRACTDATE, 'DDD') as DayNumber,

  F_MEDIA(CONTRACTDATE, 'p','tv') as tv_positive,
  F_MEDIA(CONTRACTDATE, 'p','radio') as radio_positive,
  F_MEDIA(CONTRACTDATE, 'p','newspaper') as newspaper_positive,
  F_MEDIA(CONTRACTDATE, 'p','internet') as internet_positive,
  F_MEDIA(CONTRACTDATE, 'p','weeklymagazine') as weekly_magazine_positive,

  F_MEDIA(CONTRACTDATE, 'n','tv') as tv_negative,
  F_MEDIA(CONTRACTDATE, 'n','radio') as Radio_negative,
  F_MEDIA(CONTRACTDATE, 'n','newspaper') as newspaper_negative,
  F_MEDIA(CONTRACTDATE, 'n','internet') as internet_negative,
  F_MEDIA(CONTRACTDATE, 'n','weeklymagazine') as weekly_magazine_negative
FROM CONTRACTS
GROUP BY TO_CHAR(CONTRACTDATE, 'MON'), CONTRACTDATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  TO_CHAR(CONTRACTDATE, 'MON') as Month,
--   TO_CHAR(CONTRACTDATE, 'HH24') as HourOfTheDay,
--   TO_CHAR(CONTRACTDATE, 'DAY') as DayOfTheWeek,
--   TO_CHAR(CONTRACTDATE, 'IW') as WeekNumber,
--   TO_CHAR(CONTRACTDATE, 'DDD') as DayNumber,

  F_MEDIA(CONTRACTDATE, 'p','tv') as tv_positive,
  F_MEDIA(CONTRACTDATE, 'p','radio') as radio_positive,
  F_MEDIA(CONTRACTDATE, 'p','newspaper') as newspaper_positive,
  F_MEDIA(CONTRACTDATE, 'p','internet') as internet_positive,
  F_MEDIA(CONTRACTDATE, 'p','weeklymagazine') as weekly_magazine_positive,

  F_MEDIA(CONTRACTDATE, 'n','tv') as tv_negative,
  F_MEDIA(CONTRACTDATE, 'n','radio') as Radio_negative,
  F_MEDIA(CONTRACTDATE, 'n','newspaper') as newspaper_negative,
  F_MEDIA(CONTRACTDATE, 'n','internet') as internet_negative,
  F_MEDIA(CONTRACTDATE, 'n','weeklymagazine') as weekly_magazine_negative
FROM CONTRACTS
ORDER BY tv_positive DESC
;-- -. . -..- - / . -. - .-. -.--
SELECT
  TO_CHAR(MEDIADATE, 'YYYY-MM-DD') as ContractDate,
  TO_CHAR(MEDIADATE, 'HH24') as HourOfTheDay,
  TO_CHAR(MEDIADATE, 'DAY') as DayOfTheWeek,
  TO_CHAR(MEDIADATE, 'IW') as WeekNumber,
  TO_CHAR(MEDIADATE, 'DDD') as DayNumber,

  F_MEDIA(MEDIADATE, 'p','tv') as tv_positive,
  F_MEDIA(MEDIADATE, 'p','radio') as radio_positive,
  F_MEDIA(MEDIADATE, 'p','newspaper') as newspaper_positive,
  F_MEDIA(MEDIADATE, 'p','internet') as internet_positive,
  F_MEDIA(MEDIADATE, 'p','weeklymagazine') as weekly_magazine_positive,

  F_MEDIA(MEDIADATE, 'n','tv') as tv_negative,
  F_MEDIA(MEDIADATE, 'n','radio') as Radio_negative,
  F_MEDIA(MEDIADATE, 'n','newspaper') as newspaper_negative,
  F_MEDIA(MEDIADATE, 'n','internet') as internet_negative,
  F_MEDIA(MEDIADATE, 'n','weeklymagazine') as weekly_magazine_negative
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'YYYY-MM-DD') as ContractDate,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'HH24') as HourOfTheDay,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'DAY') as DayOfTheWeek,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'IW') as WeekNumber,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'DDD') as DayNumber,

  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','tv') as tv_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','radio') as radio_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','newspaper') as newspaper_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','internet') as internet_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','weeklymagazine') as weekly_magazine_positive,

  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','tv') as tv_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','radio') as Radio_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','newspaper') as newspaper_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','internet') as internet_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','weeklymagazine') as weekly_magazine_negative
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT
  MEDIADATE as ContractDate,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'HH24') as HourOfTheDay,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'DAY') as DayOfTheWeek,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'IW') as WeekNumber,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'DDD') as DayNumber,

  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','tv') as tv_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','radio') as radio_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','newspaper') as newspaper_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','internet') as internet_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','weeklymagazine') as weekly_magazine_positive,

  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','tv') as tv_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','radio') as Radio_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','newspaper') as newspaper_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','internet') as internet_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','weeklymagazine') as weekly_magazine_negative
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT
  MEDIADATE as EXPOSUREDATE,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'HH24') as HourOfTheDay,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'DAY') as DayOfTheWeek,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'IW') as WeekNumber,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'DDD') as DayNumber,

  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','tv') as tv_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','radio') as radio_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','newspaper') as newspaper_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','internet') as internet_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','weeklymagazine') as weekly_magazine_positive,

  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','tv') as tv_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','radio') as Radio_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','newspaper') as newspaper_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','internet') as internet_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','weeklymagazine') as weekly_magazine_negative
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT 1 as CONTRACT,
       TO_CHAR(CONTRACTDATE, 'HH24')as HourOfTheDay,
       TO_CHAR(CONTRACTDATE, 'DAY') as DayOfTheWeek,
       TO_CHAR(CONTRACTDATE, 'IW') as WeekNumber,
       TO_CHAR(CONTRACTDATE, 'DDD') as DayNumber
FROM CONTRACTS
;-- -. . -..- - / . -. - .-. -.--
SELECT
       SUM(TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) AS PositiveExposure
FROM CONTRACT_MEDIA_EXPR
GROUP BY WEEKNUMBER
;-- -. . -..- - / . -. - .-. -.--
SELECT
       WEEKNUMBER,
       SUM(TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) AS PositiveExposure
FROM CONTRACT_MEDIA_EXPR
GROUP BY WEEKNUMBER
;-- -. . -..- - / . -. - .-. -.--
SELECT
  MEDIADATE as EXPOSUREDATE,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'HH24') as HourOfTheDay,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'DAY') as DayOfTheWeek,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'WW') as WeekNumber,
  TO_CHAR(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'DDD') as DayNumber,

  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','tv') as tv_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','radio') as radio_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','newspaper') as newspaper_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','internet') as internet_positive,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'p','weeklymagazine') as weekly_magazine_positive,

  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','tv') as tv_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','radio') as Radio_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','newspaper') as newspaper_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','internet') as internet_negative,
  F_MEDIA(TO_TIMESTAMP(MEDIADATE, 'DD-MM-YYYY'), 'n','weeklymagazine') as weekly_magazine_negative
FROM MEDIA
;-- -. . -..- - / . -. - .-. -.--
SELECT
  SUM((TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) - (TV_NEGATIVE + RADIO_NEGATIVE + NEWSPAPER_NEGATIVE + INTERNET_NEGATIVE + WEEKLY_MAGAZINE_NEGATIVE)) AS output
FROM CONTRACT_MEDIA_EXPR
WHERE
  TO_DATE(CONTRACT_MEDIA_EXPR.EXPOSUREDATE, 'DD-MM-YYYY') = TO_DATE(TO_CHAR('01-JAN-13 01.43.15.000000000 PM', 'YYYY-MM-DD'), 'YYYY-MM-DD')
;-- -. . -..- - / . -. - .-. -.--
SELECT
  SUM((TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) - (TV_NEGATIVE + RADIO_NEGATIVE + NEWSPAPER_NEGATIVE + INTERNET_NEGATIVE + WEEKLY_MAGAZINE_NEGATIVE)) AS output
FROM CONTRACT_MEDIA_EXPR
WHERE
  TO_DATE(CONTRACT_MEDIA_EXPR.EXPOSUREDATE, 'DD-MM-YYYY') = TO_DATE(TO_CHAR(to_timestamp('01-JAN-13 01.43.15.000000000 PM'), 'YYYY-MM-DD'), 'YYYY-MM-DD')
;-- -. . -..- - / . -. - .-. -.--
SELECT
  SUM((TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) - (TV_NEGATIVE + RADIO_NEGATIVE + NEWSPAPER_NEGATIVE + INTERNET_NEGATIVE + WEEKLY_MAGAZINE_NEGATIVE)) AS output
FROM CONTRACT_MEDIA_EXPR
WHERE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  SUM((TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) - (TV_NEGATIVE + RADIO_NEGATIVE + NEWSPAPER_NEGATIVE + INTERNET_NEGATIVE + WEEKLY_MAGAZINE_NEGATIVE)) AS output
FROM CONTRACT_MEDIA_EXPR
WHERE 1=1
;-- -. . -..- - / . -. - .-. -.--
SELECT
  SUM((TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) - (TV_NEGATIVE + RADIO_NEGATIVE + NEWSPAPER_NEGATIVE + INTERNET_NEGATIVE + WEEKLY_MAGAZINE_NEGATIVE)) AS output
FROM CONTRACT_MEDIA_EXPR
WHERE 1=1
--   TO_DATE(EXPOSUREDATE, 'DD-MM-YYYY') = TO_DATE(TO_CHAR(to_timestamp('01-JAN-13 01.43.15.000000000 PM'), 'YYYY-MM-DD'), 'YYYY-MM-DD');
GROUP BY EXPOSUREDATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  EXPOSUREDATE,
  SUM((TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) - (TV_NEGATIVE + RADIO_NEGATIVE + NEWSPAPER_NEGATIVE + INTERNET_NEGATIVE + WEEKLY_MAGAZINE_NEGATIVE)) AS output
FROM CONTRACT_MEDIA_EXPR
WHERE 1=1
--   TO_DATE(EXPOSUREDATE, 'DD-MM-YYYY') = TO_DATE(TO_CHAR(to_timestamp('01-JAN-13 01.43.15.000000000 PM'), 'YYYY-MM-DD'), 'YYYY-MM-DD');
GROUP BY EXPOSUREDATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  EXPOSUREDATE,
  TO_DATE(TO_CHAR(to_timestamp('01-JAN-13 01.43.15.000000000 PM'), 'YYYY-MM-DD'), 'YYYY-MM-DD') AS p_date,
  SUM((TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) - (TV_NEGATIVE + RADIO_NEGATIVE + NEWSPAPER_NEGATIVE + INTERNET_NEGATIVE + WEEKLY_MAGAZINE_NEGATIVE)) AS output
FROM CONTRACT_MEDIA_EXPR
WHERE 1=1
--   TO_DATE(EXPOSUREDATE, 'DD-MM-YYYY') = TO_DATE(TO_CHAR(to_timestamp('01-JAN-13 01.43.15.000000000 PM'), 'YYYY-MM-DD'), 'YYYY-MM-DD');
GROUP BY EXPOSUREDATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  EXPOSUREDATE,
  TO_DATE(TO_CHAR(to_timestamp('01-JAN-13 01.43.15.000000000 PM'), 'YYYY-MM-DD'), 'YYYY-MM-DD') = TO_DATE(EXPOSUREDATE, 'DD-MM-YYYY') AS p_date,
  SUM((TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) - (TV_NEGATIVE + RADIO_NEGATIVE + NEWSPAPER_NEGATIVE + INTERNET_NEGATIVE + WEEKLY_MAGAZINE_NEGATIVE)) AS output
FROM CONTRACT_MEDIA_EXPR
WHERE 1=1
--   TO_DATE(EXPOSUREDATE, 'DD-MM-YYYY') = TO_DATE(TO_CHAR(to_timestamp('01-JAN-13 01.43.15.000000000 PM'), 'YYYY-MM-DD'), 'YYYY-MM-DD');
GROUP BY EXPOSUREDATE
;-- -. . -..- - / . -. - .-. -.--
SELECT
  SUM((TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) - (TV_NEGATIVE + RADIO_NEGATIVE + NEWSPAPER_NEGATIVE + INTERNET_NEGATIVE + WEEKLY_MAGAZINE_NEGATIVE)) AS output
FROM CONTRACT_MEDIA_EXPR
WHERE 1=1
  TO_DATE(EXPOSUREDATE, 'DD-MM-YYYY') = TO_DATE(TO_CHAR(to_timestamp('24-JAN-13 01.43.15.000000000 PM'), 'YYYY-MM-DD'), 'YYYY-MM-DD')
;-- -. . -..- - / . -. - .-. -.--
SELECT
  SUM((TV_POSITIVE + RADIO_POSITIVE + NEWSPAPER_POSITIVE + INTERNET_POSITIVE + WEEKLY_MAGAZINE_POSITIVE) - (TV_NEGATIVE + RADIO_NEGATIVE + NEWSPAPER_NEGATIVE + INTERNET_NEGATIVE + WEEKLY_MAGAZINE_NEGATIVE)) AS output
FROM CONTRACT_MEDIA_EXPR
WHERE
  TO_DATE(EXPOSUREDATE, 'DD-MM-YYYY') = TO_DATE(TO_CHAR(to_timestamp('24-JAN-13 01.43.15.000000000 PM'), 'YYYY-MM-DD'), 'YYYY-MM-DD')