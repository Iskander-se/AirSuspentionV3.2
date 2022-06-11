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

  if ((curFDeviation < -curFAmplitude) || (curRDeviation < -curRAmplitude)) {  //    _ x _   ///////////////////////////////////// если перед или зад низко, дальше амлитуды хода
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
  else if ((curFDeviation > curFAmplitude) || (curRDeviation > curRAmplitude)) { //   ^ x ^   ///////////////////////////////////// если перед или зад высоко, дальше амлитуды хода
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
