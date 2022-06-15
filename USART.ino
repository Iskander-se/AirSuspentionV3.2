void SerialAlertSend2HU(String pp, String msg) {
  String str = "@a:";
  str = str + String(pp) + ":";
  str = str + msg + "^";

  Serial.println(str);
  Serial.flush();
  HwSerial.println(str);
  HwSerial.flush();
}

void BTseriallog() {
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
  HwSerial.println(str);

}
