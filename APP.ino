void GetLevelInstance (byte addr) {
  //if (addr > 0)GetLevelPreset(addr);
  IntentHeap.curTargetLevels[0] = cStatus.PresetLevels[0] * 10 + cStatus.shiftL;
  IntentHeap.curTargetLevels[1] = cStatus.PresetLevels[0] * 10 + cStatus.shiftR;
  IntentHeap.curTargetLevels[2] = cStatus.PresetLevels[1] * 10 + cStatus.shiftL;
  IntentHeap.curTargetLevels[3] = cStatus.PresetLevels[1] * 10 + cStatus.shiftR;

}

void fAirPowerT() {
  if (cStatus.airPowerF == 2) {
    for (int i = 0; i < 4; i++ ) if (cWarningArr.Power > 0) cWarningArr.Power--;
  }
  if (cStatus.airPowerF && ValveSet.WP)  {
    cStatus.airPowerT++;
  }
  else {
    if (cStatus.airPowerT > 0) {
      cStatus.airPowerT--;
    }
  }
  if (cStatus.airPowerT > 100) {
    cStatus.airPowerF = 0;
    cWarningArr.Power++;
  }
  if (cStatus.airPowerT < 1) cStatus.airPowerF = 1;
}

void fCheckWarnings() {
  bool alert = 0;
  if (cWarningArr.Power > 2) {
    cWarningArr.Power = 0;
    alert = 1;
    cAlertArr.Power = "R" + String(cStatus.pRES, DEC) + "P" + String(cStatus.pVAG, DEC);
    tone(piPin, 1100, 110);
  }

  if (cWarningArr.BanksF > 30) {
    cWarningArr.BanksF = 0;
    alert = 1;
    cAlertArr.BanksF = "F" + String(IntentSetBL.FL) + ":" + String(IntentSetBL.FR) + "P" + String(cStatus.pVAG, DEC);
    Switch2Manual();
  }

  if (cWarningArr.BanksR > 30) {
    cWarningArr.BanksR = 0;
    alert = 1;
    cAlertArr.BanksR = "R" + String(IntentSetBL.RL) + ":" + String(IntentSetBL.RR) + "P" + String(cStatus.pVAG, DEC);
    Switch2Manual();
  }

  if (cWarningArr.Valves > 70) {
    cWarningArr.Valves = 0;
    alert = 1;
    cAlertArr.Valves = "V" + String(IntentSetBL.FL) + ":" + String(IntentSetBL.FR) + ":" + String(IntentSetBL.RL) + ":" + String(IntentSetBL.RR) + ":" + String(IntentSetBL.SWITCH) + "|" + String(cStatus.pVAG);
    Switch2Manual();
  }
  cStatus.alert = alert;
  if (cStatus.alert && !cStatus.mute) {
    cStatus.wait = 0;
    tone(piPin, 1100, 110);
  }
}

void fManualMode()
{
  IntentSetBL = {0, 0, 0, 0, 0, 0, 1};
  if (cStatus.manual == 2) {
    cStatus.manual = 3;
    cStatus.wait = 0;
  }
  if (cStatus.wait < 1) {
    ValveSet.FL = 0;
    ValveSet.FR = 0;
    ValveSet.RL = 0;
    ValveSet.RR = 0;
    if (ValveSet.SWITCH < 3)ValveSet.SWITCH = 0;
  }
}
