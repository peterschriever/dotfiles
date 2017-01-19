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