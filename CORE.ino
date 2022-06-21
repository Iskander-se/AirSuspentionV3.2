void MainTask() {
  fAirPowerT();
  GetLevels();
  GetPressure();
  GetFlags();
  if (cStatus.engine < 40) {
    cStatus.wait = 30;
  }

  if (cStatus.manual) fManualMode();
  else {
    fLevelBain();
    if (cStatus.door < 2 ) IntentSetBL.SWITCH = 0;
    else if ((cStatus.door > 3) && (cStatus.door < 50)) cStatus.cBlur = 0;
    else cStatus.cBlur = 10;
    
    if (!cMenu.nom) {
      fSUBcore();
    }
  }
  fSerialWorker();
  if (cStatus.wait > 0) cStatus.wait --;
  // VAG-MB Block is doing its job
  fVAGBlockWork();
  // if VAG block does working is send its composite
  if (ValveSet.SWITCH != 4) sWorkSend2HU();
  sCurHWLevel2HU();
}

void LowSerialTask() {
  fCheckWarnings();
  //Seriallog();
  if (cAlertArr.Valves != NULL) SerialAlertSend2HU("v", cAlertArr.Valves);
  if (cAlertArr.BanksF != NULL) SerialAlertSend2HU("b", cAlertArr.BanksF);
  if (cAlertArr.BanksR != NULL) SerialAlertSend2HU("b", cAlertArr.BanksR);
  if (cAlertArr.Power != NULL) SerialAlertSend2HU("p", cAlertArr.Power);
}

void PanelTask() {
  GetKey();
  if (cMenu.wait > 0) cMenu.wait --;
  else cMenu.nom = 0;
  if (cMenu.nom) {
    fLCDmenu();
    return;
  }
  int curArr[4];
  switch (cStatus.lcdv) {
    case 0:
      for (int i = 0; i < 4; i++) curArr[i] = IntentHeap.curTargetLevels[i] / 10;
      break;
    case 1:
      for (int i = 0; i < 4; i++) curArr[i] = curSuspention[i].Avg / 10;
      break;
    case 2:
      for (int i = 0; i < 4; i++) curArr[i] = curSuspention[i].RAW;
      break;
    case 3:
      for (int i = 0; i < 4; i++) curArr[i] = curSuspention[i].Apld;
      break;
    default:
      for (int i = 0; i < 4; i++) curArr[i] = curSuspention[i].Avg / 10;
  }

  fLCDView4Int(curArr);
  fLCDViewIntents();
  if (cStatus.manual)fLCDViewStM();
  else fLCDViewAuto();

  // sometimes send if OK and free woking in VAG-block
  if (ValveSet.SWITCH == 4) sWorkSend2HU();
}

void fVAGBlockWork() {
  if (ValveSet.SWITCH > 2 && (ValveSet.FL || ValveSet.FR || ValveSet.RL || ValveSet.RR)) ValveSet.SWITCH = 0;
  switch (ValveSet.SWITCH) {
    case 1 : //UP
      digitalWrite(vEXH, 0);
      if (cStatus.pRES > 800) {         //  work it from reciver
        digitalWrite(vRES, 1);
        digitalWrite(vPC, 0);
        ValveSet.WP = 0;
      } else if (cStatus.pRES < 650) { ///  work it without reciver
        digitalWrite(vRES, 0);
        digitalWrite(vPC, 1);
        ValveSet.WP = 2;
      } else {                         // compressor + reciver
        ValveSet.WP = 1;
        digitalWrite(vRES, 1);
        digitalWrite(vPC,  cStatus.airPowerF);
      }
      break;
    case 2:  //DOWN
      digitalWrite(vEXH, 1);
      digitalWrite(vRES, 0);
      digitalWrite(vPC, 0);
      ValveSet.WP = 0;
      break;
    case 3:  //CRARGE
      cStatus.airPowerF = 1;
      fChargeRES();
      break;
    case 4:  //FREE2CRARGE
      if (cStatus.wait > 1) cStatus.airPowerF = 0;
      if ((cStatus.pRES > 350 && cStatus.pRES < 860) || ValveSet.WP == 1) {
        ValveSet.WP = 1;
        fChargeRES();
      }
      else {
        digitalWrite(vEXH, 0);    digitalWrite(vRES, 0);    digitalWrite(vPC, 0);
      }
      break;
    case 5:  //Transit
      digitalWrite(vEXH, 0);
      digitalWrite(vRES, 1);
      digitalWrite(vPC, 0);
      break;
    default:
      digitalWrite(vEXH, 0);
      digitalWrite(vRES, 0);
      digitalWrite(vPC, 0);
  }
  digitalWrite(vFL, ValveSet.FL);
  digitalWrite(vFR, ValveSet.FR);
  digitalWrite(vRL, ValveSet.RL);
  digitalWrite(vRR, ValveSet.RR);
}

void fChargeRES()
{
  if (cStatus.airPowerF == 2) {
    digitalWrite(vEXH, 0);
    digitalWrite(vRES, 0);
    digitalWrite(vPC, 0);
    ValveSet.WP = 0;
    return;
  }
  if (cStatus.pRES > 980 && ValveSet.SWITCH != 3) {
    cStatus.airPowerF = 2; // OVER
    digitalWrite(vEXH, 1);
    digitalWrite(vRES, 0);
    digitalWrite(vPC, 0);
  } else {
    digitalWrite(vEXH, 0);
    digitalWrite(vRES, cStatus.airPowerF);
    digitalWrite(vPC, cStatus.airPowerF);
  }
  return;
}
