void MainTask() {
  GetLevels();
  fLevelBain();
  GetPressure();
}

void LowSerialTask() {
  BTseriallog();
}

void PanelTask() {
  GetKey();
  int curArr[4];
  cStatus.lcdv = cMenu.shift+1;
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
  fLCDViewAuto();

}

void BTseriallog() {
  lcd.setCursor(5, 1); lcd.print(tempTimer3); lcd.print(" ");
  String str = "";
  str = str + String(tempTimer, DEC);
  str = str + " ";
  str = str + String(tempTimer3, DEC);

  str = str + " || wait:" + String(cStatus.wait) + " S:" + String(cStatus.servicemode) + " M:" + String(cStatus.manual);
  str = str + " || " + String(IntentSetBL.FL) + "-" + String(IntentSetBL.FR) + "-" + String(IntentSetBL.RL)+ "-" + String(IntentSetBL.RR)+ "-" + String(IntentSetBL.SWITCH);
  //  BtSerial.print(" wLowUpF:"); BtSerial.print(waitLowUpF);
  //  BtSerial.print(" wLowUpR:"); BtSerial.print(waitLowUpR);
  str = str + " ||  ";
  for (int i = 0; i < 4; i++) {
    str = str + " RAW:" + String(curSuspention[i].RAW, DEC);
    str = str + " Avg:" + String(curSuspention[i].Avg/10, DEC);
    str = str + " Max:" + String(curSuspention[i].Max/10, DEC);
    str = str + " Min:" + String(curSuspention[i].Min/10, DEC);
    str = str + " D:" + String(curSuspention[i].Apld, DEC);
  }
  HwSerial.println(str);
  Serial.println(str);
}
