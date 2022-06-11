void GetLevels() {
  int cVar;
  for (int i = 0; i < 4; i++ ) {
    switch (i) {
      case 0: ADCS.setCompareChannels(ADS1115_COMP_0_GND); break;
      case 1: ADCS.setCompareChannels(ADS1115_COMP_1_GND); break;
      case 2: ADCS.setCompareChannels(ADS1115_COMP_2_GND); break;
      case 3: ADCS.setCompareChannels(ADS1115_COMP_3_GND); break;
    }
    ADCS.startSingleMeasurement();
    while (ADCS.isBusy()) {}
    curSuspention[i].RAW = ADCS.getRawResult() / 100;
    cVar = map(curSuspention[i].RAW, LowLevels[i], HighLevels[i], 0, 1000);
    curSuspention[i].Avg = (curSuspention[i].Avg * 4 + cVar) / 5;
    curSuspention[i].Max = (curSuspention[i].Max < cVar) ? cVar : (curSuspention[i].Max * 5 + curSuspention[i].Avg) / 6;
    curSuspention[i].Min = (curSuspention[i].Min > cVar) ? cVar : (curSuspention[i].Min * 5 + curSuspention[i].Avg) / 6;
    curSuspention[i].Apld = (curSuspention[i].Max - curSuspention[i].Min);
  }

}

void GetPressure()
{
  ADCP.setCompareChannels(ADS1115_COMP_0_GND);
  ADCP.startSingleMeasurement();
  while (ADCP.isBusy()) {}
  cStatus.pRES = map(ADCP.getRawResult(), 2667, 24011, 0, 1020);

  ADCP.setCompareChannels(ADS1115_COMP_1_GND);
  ADCP.startSingleMeasurement();
  while (ADCP.isBusy()) {}
  cStatus.pVAG = map(ADCP.getRawResult(), 3414, 8890, 250, 1070);
}
