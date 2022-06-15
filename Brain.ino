void fLevelBain()
{
  int16_t curFDeviation = (curSuspention[0].Avg + curSuspention[1].Avg) - (IntentHeap.curTargetLevels[0] + IntentHeap.curTargetLevels[1]); //Отклонение среднего по переду от цели
  int16_t curRDeviation = (curSuspention[2].Avg + curSuspention[3].Avg) - (IntentHeap.curTargetLevels[2] + IntentHeap.curTargetLevels[3]); //Отклонение среднего по корме от цели
  int16_t curFAmplitude = curSuspention[0].Apld + curSuspention[1].Apld + cStatus.cBlur; // Амплитуда + слепая зона
  int16_t curRAmplitude = curSuspention[2].Apld + curSuspention[3].Apld + cStatus.cBlur; // Амплитуда + слепая зона

  int heelFront = curSuspention[0].Avg - curSuspention[1].Avg; // Крен по оси
  int heelRear = curSuspention[2].Avg - curSuspention[3].Avg; // Крен по оси

  ///////SERVICEMOD ===========
  //Нужна скорейшая реакция
  if (cStatus.servicemode) {
    curFAmplitude = 0;
    curRAmplitude = 0;
    if (waitLowUpF && (curFDeviation < 0)) waitLowUpF = 0;
    if (waitLowUpR && (curRDeviation < 0)) waitLowUpR = 0;
  }

  // twixDelta //// front < 0 < rear

  if ((curFDeviation < -curFAmplitude) || (curRDeviation < -curRAmplitude)) {  //    _ x _   ///////////////////////////////////// if front and rear is low, more current amplitude
    //tempIfSwitch = 1;

    if ((curFDeviation < curRDeviation) || (curFDeviation < curRDeviation / 2 && IntentSetBL.SWITCH == 1)) {
      //    _ x ~   /////////////////////////////////////
      //tempIfSwitch = 2;
      if (IntentHeap.curTargetLevels[0] - cStatus.cBlur > curSuspention[0].Max) {
        if (IntentSetBL.FL < 50) IntentSetBL.FL++;
      }
      else IntentSetBL.FL = 0;
      if (IntentHeap.curTargetLevels[1] - cStatus.cBlur > curSuspention[1].Max) {
        if (IntentSetBL.FR < 50) IntentSetBL.FR++;
      }
      else IntentSetBL.FR = 0;
      if (IntentSetBL.FL || IntentSetBL.FR)IntentSetBL.SWITCH = 1;
      IntentSetBL.RL = 0;
      IntentSetBL.RR = 0;
    } else {
      //    ~ x _   /////////////////////////////////////
      //tempIfSwitch = 3;
      if (IntentHeap.curTargetLevels[2] - cStatus.cBlur > curSuspention[2].Max) {
        if (IntentSetBL.RL < 50) IntentSetBL.RL++;
      }
      else IntentSetBL.RL = 0;
      if (IntentHeap.curTargetLevels[3] - cStatus.cBlur > curSuspention[3].Max) {
        if (IntentSetBL.RR < 50) IntentSetBL.RR++;
      }
      else IntentSetBL.RR = 0;
      if (IntentSetBL.RL || IntentSetBL.RR)IntentSetBL.SWITCH = 2;
      IntentSetBL.FL = 0;
      IntentSetBL.FR = 0;
    }

  }
  else if ((curFDeviation > curFAmplitude) || (curRDeviation > curRAmplitude)) { //   ^ x ^   ///////////////////////////////////// if front and rear is high, more current amplitude  
    //tempIfSwitch = 4;
    if (((curFDeviation > curRDeviation) || (curFDeviation > curRDeviation / 2 && IntentSetBL.SWITCH == 3)) && !waitLowUpF) {
      //    _ x ~   /////////////////////////////////////
      if (IntentHeap.curTargetLevels[0] + cStatus.cBlur < curSuspention[0].Min) {
        if (IntentSetBL.FL < 50) IntentSetBL.FL++;
      }
      else IntentSetBL.FL = 0;
      if (IntentHeap.curTargetLevels[1] + cStatus.cBlur < curSuspention[1].Min) {
        if (IntentSetBL.FR < 50) IntentSetBL.FR++;
      }
      else IntentSetBL.FR = 0;
      if (IntentSetBL.FL || IntentSetBL.FR)IntentSetBL.SWITCH = 3;
      IntentSetBL.RL = 0;
      IntentSetBL.RR = 0;
    } else if (!waitLowUpR) {
      //    ~ x _   /////////////////////////////////////
      if (IntentHeap.curTargetLevels[2] + cStatus.cBlur < curSuspention[2].Min) {
        if (IntentSetBL.RL < 50) IntentSetBL.RL++;
      }
      else IntentSetBL.RL = 0;
      if (IntentHeap.curTargetLevels[3] + cStatus.cBlur < curSuspention[3].Min) {
        if (IntentSetBL.RR < 50) IntentSetBL.RR++;
      }
      else IntentSetBL.RR = 0;
      if (IntentSetBL.RL || IntentSetBL.RR)IntentSetBL.SWITCH = 4;
      IntentSetBL.FL = 0;
      IntentSetBL.FR = 0;
    }

  }
  else {
    IntentSetBL.FL = 0; IntentSetBL.FR = 0;
    IntentSetBL.RL = 0; IntentSetBL.RR = 0;
    IntentSetBL.SWITCH = 0;
  }

  //Если намерения не ясны => их нет
  //sif (IntentSetBL.FL == 0 && IntentSetBL.FR == 0 && IntentSetBL.RL == 0 && IntentSetBL.RR == 0)    IntentSetBL.CurRELAY = 0;
}

void fSUBcore() {
  // 1: Front up;    2: Rear up;     3: Front down;    4: Rear down;
  int suff = 20;
  int waitS1 = 4;
  int waitS2 = 6;
  int newSWITCH = ValveSet.SWITCH;
  ValveSet.FL = 0;  ValveSet.FR = 0;
  ValveSet.RL = 0;  ValveSet.RR = 0;
  switch (IntentSetBL.SWITCH)
  {
    case 1 : // Front up
      ValveSet.FL = (IntentSetBL.FL > waitS1);  ValveSet.FR = (IntentSetBL.FR > waitS1);
      if (cStatus.pVAG > 160 && cStatus.pVAG < 760 && (IntentSetBL.FL > waitS2 || IntentSetBL.FR > waitS2)) newSWITCH = 1;
      else {
        newSWITCH = 0;
        IntentSetBL.HOPE++;
        if (IntentSetBL.HOPE > suff) cWarningArr.BanksF++;
      }
      break;
    case 2:  // Rear up
      ValveSet.RL = (IntentSetBL.RL > waitS1);  ValveSet.RR = (IntentSetBL.RR > waitS1);
      if (cStatus.pVAG > 170 && cStatus.pVAG < 430 && (IntentSetBL.RL > waitS2 || IntentSetBL.RR > waitS2)) newSWITCH = 1;
      else {
        newSWITCH = 0;
        IntentSetBL.HOPE++;
        if (IntentSetBL.HOPE > suff) cWarningArr.BanksR++;
      }
      break;
    case 3 : // Front down
      ValveSet.FL = (IntentSetBL.FL > waitS1);  ValveSet.FR = (IntentSetBL.FR > waitS1);
      if (cStatus.pVAG > 200 && (IntentSetBL.FL > waitS2 || IntentSetBL.FR > waitS2)) newSWITCH = 2;
      else {
        newSWITCH = 0;
        IntentSetBL.HOPE++;
        if (IntentSetBL.HOPE > suff)cWarningArr.BanksF++;
      }

      break;
    case 4:  // Rear down
      ValveSet.RL = (IntentSetBL.RL > waitS1);  ValveSet.RR = (IntentSetBL.RR > waitS1);
      if (cStatus.pVAG > 180 && (IntentSetBL.RL > waitS2 || IntentSetBL.RR > waitS2)) newSWITCH = 2;
      else {
        newSWITCH = 0;
        IntentSetBL.HOPE++;
        if (IntentSetBL.HOPE > suff) cWarningArr.BanksR++;
      }
      break;
    default: // ~0 FREE
      IntentSetBL.HOPE = 0;
      newSWITCH = 4;
  }
  if (cWarningArr.BanksF > 0 || cWarningArr.BanksR > 0) {
    ///////SERVICEMOD ===========////   3: Front down;    4: Rear down;

    //Разгрузка подушек висящих на подьемнике или домкрате
    //For make pressure to low when stand on services lift  
    if (cStatus.servicemode) {
      if (cWarningArr.BanksF > 15 && IntentSetBL.SWITCH == 3) {
        cWarningArr.BanksF = 0;
        waitLowUpF = true;
      }
      if (cWarningArr.BanksR > 15 && IntentSetBL.SWITCH == 4) {
        cWarningArr.BanksR = 0;
        waitLowUpR = true;
      }

      if (waitLowUpF) {
        cWarningArr.Valves = 0;
        ValveSet.FL = 0; ValveSet.FR = 0;
        newSWITCH = 0;
      }
      if (waitLowUpR) {
        cWarningArr.Valves = 0;
        ValveSet.RL = 0; ValveSet.RR = 0;
        newSWITCH = 0;
      }
    }
  }
  if ((newSWITCH == 1) || (newSWITCH == 2)) {
    cWarningArr.Valves++;
    cStatus.wait = 20;
  }
  if (ValveSet.SWITCH != newSWITCH || newSWITCH == 4) {
    cWarningArr.Valves = 0;
    IntentSetBL.HOPE = 0;
  }
  ValveSet.SWITCH = newSWITCH;
}
