SerialPack SerialRead()
{
  char bufferArr[100], ch;
  SerialPack cPack;
  cPack.command = 0;
  int i = 0;

  while ( Serial.available()) {
    delay(1);
    HwSerial.println("   Serial.available():");
    ch = Serial.read();
    if (ch == '^') {
      break;
    }
    if (ch == '@') i = 0;
    if (ch > 30) bufferArr[i++] = ch;
  }

  if (i > 0)  {
    cPack = sfParcer(i, bufferArr);
    cPack.port = 0;
  }

  if (cPack.command == 0) {
    while ( HwSerial.available()) {
      delay(1);
      ch = HwSerial.read();
      if (ch == '^') {
        break;
      }
      if (ch == '@') i = 0;
      if (ch > 30) bufferArr[i++] = ch;
    }
    if (i > 0)  {
      HwSerial.print("sfParcer");
      cPack = sfParcer(i, bufferArr); 
      cPack.port = 1;
    }
   
  }

  return cPack;
}

SerialPack sfParcer(int i, char bufferArr[100])
{
  SerialPack cPack;
  cPack.command = bufferArr[1];
  switch (i) {
    case 5:
      cPack.nom = bufferArr[2] - '0';
      break;
    case 8:
      cPack.nom = bufferArr[2] - '0';
      cPack.data[0] = Dchar2hex(bufferArr[4], bufferArr[5]);
      cPack.data[1] = Dchar2hex(bufferArr[6], bufferArr[7]);
      break;
    default:
      cPack.nom = bufferArr[2] - '0';
      if (cPack.command == 'c') {
        cPack.data[0] = bufferArr[4];
        cPack.data[1] = bufferArr[5];
      }
  }

  return cPack;
  //@p5:*^
  //@m1:1000^
}

/////////////////////////////// Sendersess   ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void SerialAlertSend2HU(String pp, String msg) {
  String str = "@a:";
  str = str + String(pp) + ":";
  str = str + msg + "^";

  Serial.println(str);
  HwSerial.println(str);
}

void sSavedLevelSend2HU(char nom, int8_t cArray[2], int port) {
  String str = "@l:";
  str = str + String(nom, DEC) + ":";
  if (cArray[0] < 15)str = str + String('0'); str = str + String(cArray[0], HEX);
  if (cArray[1] < 15)str = str + String('0'); str = str + String(cArray[1], HEX);
  str = str + "^";
  if (port == 0)Serial.println(str);
  else HwSerial.println(str);
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
