// 2 знака => байт
byte Dchar2hex(char ch1, char ch2) {
  int val = 0;
  if (ch1 >= 'A' && ch1 <= 'F') val = (ch1 - 'A' + 10) << 4;
  else val = (ch1 - '0') << 4;
  if (ch2 >= 'A' && ch2 <= 'F') val += ch2 - 'A' + 10;
  else val += ch2 - '0';
  return val;
}

void GetLevelInstance (byte addr) {
  if (addr > 0) ReadLevelPreset(addr);
  IntentHeap.curTargetLevels[0] = cStatus.PresetLevels[0] * 10 + cStatus.shiftL;
  IntentHeap.curTargetLevels[1] = cStatus.PresetLevels[0] * 10 + cStatus.shiftR;
  IntentHeap.curTargetLevels[2] = cStatus.PresetLevels[1] * 10 + cStatus.shiftL;
  IntentHeap.curTargetLevels[3] = cStatus.PresetLevels[1] * 10 + cStatus.shiftR;

}

void fSerialWorker() {
  packFromHU = SerialRead();
  if (packFromHU.command != 0)
  {
    byte addr = 0;


    switch (packFromHU.command) {
      case 's':       /////////////////////////////////////////////////////////////////////////////// задание произвольного уровня
        cStatus.manual = 0;
        cStatus.PresetLevels[0] = packFromHU.data[0];
        cStatus.PresetLevels[1] = packFromHU.data[1];
        sSavedLevelSend2HU(packFromHU.nom + '0', cStatus.PresetLevels, packFromHU.port);
        GetLevelInstance(0);
        break;
      case 'p':       /////////////////////////////////////////////////////////////////////////////// выбор установленнго пресета
        cStatus.nomPreset = packFromHU.nom;
        GetLevelInstance(cStatus.nomPreset);
        SaveSetLevelPreset(cStatus.nomPreset);
        sSavedLevelSend2HU(packFromHU.nom + '0', cStatus.PresetLevels, packFromHU.port);
        break;
      case 'm':     //@m1:1100^ ///////////////////////////////////////////////////////////////////// ручное управление из головного устройства
        Switch2Manual();
        ValveSet.SWITCH = (packFromHU.nom > 0) ? 1 : 2;
        ValveSet.WP = 0;
        ValveSet.FL = ((packFromHU.data[0] == 16) || (packFromHU.data[0] == 17));
        ValveSet.FR = ((packFromHU.data[0] == 1) || (packFromHU.data[0] == 17));
        ValveSet.RL = ((packFromHU.data[1] == 16) || (packFromHU.data[1] == 17));
        ValveSet.RR = ((packFromHU.data[1] == 1) || (packFromHU.data[1] == 17));
        cStatus.wait = 40;
        break;
      case 'w':  /////////////////////////////////////////////////////////////////////////////////////// запись в EEPROM пресета
        addr = firstValueAddress + packFromHU.nom * 2;
        EEPROM_Level_write(addr, packFromHU.data);
        break;
      case 'r':       /////////////////////////////////////////////////////////////////////////////// чтение из EEPROM пресета на выбор
        addr = firstValueAddress + packFromHU.nom * 2;
        int8_t data[2];
        EEPROM_Level_read(addr, data);
        sSavedLevelSend2HU(packFromHU.nom + '0', data, packFromHU.port);
        break;
      default:
        HwSerial.println("packFromHU &&&");
        HwSerial.print("   SerialPack:");
        HwSerial.print(" "); HwSerial.print(packFromHU.command);
        HwSerial.print(" "); HwSerial.print(packFromHU.nom);
        HwSerial.print(" data[2]:["); HwSerial.print(packFromHU.data[0]);
        HwSerial.print(";"); HwSerial.print(packFromHU.data[1]);
        HwSerial.println("]");
    }
  }
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
  if (cWarningArr.Power > 5) {
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
    cAlertArr.Valves = String(IntentSetBL.FL > 0) + String(IntentSetBL.FR > 0) + String(IntentSetBL.RL > 0) + String(IntentSetBL.RR > 0) + String(IntentSetBL.SWITCH) + "P" + String(cStatus.pVAG);
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

/////////////////// One Custom story
int GetBankPressure(byte bank)
{
  digitalWrite(vRES, 0);
  digitalWrite(vPC, 0);
  digitalWrite(vEXH, 0);
  digitalWrite(vFL, bank == 0);
  digitalWrite(vFR, bank == 1);
  digitalWrite(vRL, bank == 2);
  digitalWrite(vRR, bank == 3);
  delay(500);
  GetPressure();
  delay(100);
  digitalWrite(vFL, 0);
  digitalWrite(vFR, 0);
  digitalWrite(vRL, 0);
  digitalWrite(vRR, 0);
  return cStatus.pVAG;
}

void Get4Pressure() {
  int curArr[4];
  for (byte i = 0; i < 4; i++)  {
    digitalWrite(vRES, 0);
    digitalWrite(vPC, 0);
    digitalWrite(vEXH, 1);
    delay(1500);
    curArr[i] = GetBankPressure(i);
  }
  digitalWrite(vFL, 0);
  digitalWrite(vFR, 0);
  digitalWrite(vRL, 0);
  digitalWrite(vRR, 0);
  fLCDView4Int(curArr);
}
