void SerialAlertSend2HU(String pp, String msg) {
  String str = "@a:";
  str = str + String(pp) + ":";
  str = str + msg + "^";

  Serial.println(str);
  HwSerial.println(str);
}

void sWorkSend2HU() {
  String str = "@w:b:";
  str = str + String(ValveSet.SWITCH, DEC);
  str = str + String(ValveSet.FL, DEC);
  str = str + String(ValveSet.FR, DEC);
  str = str + String(ValveSet.RL, DEC);
  str = str + String(ValveSet.RR, DEC);
  if (ValveSet.SWITCH == 1) str = str + String(ValveSet.WP, DEC);
  else str = str + String(cStatus.airPowerF, DEC);
  str = str + "^";
  Serial.println(str);
  HwSerial.println(str);
}
void sCurHWLevel2HU() {
  String str = "@l:c:";
  int curArr[4];
  for (int i = 0; i < 4; i++) curArr[i] = curSuspention[i].Avg / 10;
  if (curArr[0] < 15)str = str + String('0'); str = str + String(curArr[0], HEX);
  if (curArr[1] < 15)str = str + String('0'); str = str + String(curArr[1], HEX);
  if (curArr[2] < 15)str = str + String('0'); str = str + String(curArr[2], HEX);
  if (curArr[3] < 15)str = str + String('0'); str = str + String(curArr[3], HEX);
  str = str + "^";
  Serial.println(str);
  HwSerial.println(str);
}

void Seriallog() {
  String str = "";
  str = str + String(tempTimer, DEC);
  str = str + " ";
  str = str + String(tempTimer3, DEC);

  str = str + " || wait:" + String(cStatus.wait) + " S:" + String(cStatus.servicemode) + " M:" + String(cStatus.manual);
  str = str + " || " + String(IntentSetBL.FL) + "-" + String(IntentSetBL.FR) + "-" + String(IntentSetBL.RL) + "-" + String(IntentSetBL.RR) + "-" + String(IntentSetBL.SWITCH);
  //  BtSerial.print(" wLowUpF:"); BtSerial.print(waitLowUpF);
  //  BtSerial.print(" wLowUpR:"); BtSerial.print(waitLowUpR);
  str = str + " ||  ";
  for (int i = 0; i < 4; i++) {
    str = str + " RAW:" + String(curSuspention[i].RAW, DEC);
    str = str + " Avg:" + String(curSuspention[i].Avg / 10, DEC);
    str = str + " Max:" + String(curSuspention[i].Max / 10, DEC);
    str = str + " Min:" + String(curSuspention[i].Min / 10, DEC);
    str = str + " D:" + String(curSuspention[i].Apld, DEC);
  }
  Serial.println(str);
  //HwSerial.println(str);

}
