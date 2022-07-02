///////////////////////////////
//EEPROM
//////////////////////////////

/// RW byte
void EEPROM_Level_read(byte addr, int8_t curVal[2]) {
  curVal[0] = EEPROM.read(addr);
  curVal[1] = EEPROM.read(addr + 1);
}
void EEPROM_Level_write(byte addr, int8_t curVal[2]) {
  EEPROM.update(addr, curVal[0]);
  EEPROM.update(addr + 1, curVal[1]);
}

// RW int
int EEPROM_Int_read(byte addr)
{
  byte byte1 = EEPROM.read(addr);
  byte byte2 = EEPROM.read(addr + 1);
  return (byte1 << 8) + byte2;
}

void EEPROM_Int_Write(byte addr, int number)
{
  byte byte1 = number >> 8;
  byte byte2 = number & 0xFF;
  EEPROM.write(addr, byte1);
  EEPROM.write(addr + 1, byte2);
}
void GetLevelHwSetup()
{
  byte i;
  for (i = 0; i < 4; i++) {
    LowLevels[i] = EEPROM_Int_read(levelHwAddress[0] + i * 2);
  }
  for (i = 0; i < 4; i++) {
    HighLevels[i] = EEPROM_Int_read(levelHwAddress[1] + i * 2);
  }
}

void Switch2Manual() {
  EEPROM.update(ManualAddr, 1);
  cStatus.manual = 1;
  cStatus.servicemode = 0;
}

void Switch2Auto() {
  EEPROM.update(ManualAddr, 0);
  cStatus.manual = 0;
  cStatus.servicemode = 0;
  waitLowUpF = 0;
  waitLowUpR = 0;
}
void GetPreSetup()
{
  //cStatus.servicemode;
  cStatus.manual = EEPROM.read(ManualAddr);
  cStatus.fcheckDoor = EEPROM.read(fcheckDoorAddr);
  cStatus.fcheckEngine = EEPROM.read(fcheckEngineAddr);
  cStatus.lcdv = EEPROM.read(lcdvAddr);
  cStatus.nomPreset = EEPROM.read(PresetAddr);
}

void SetPreSetup()
{
  EEPROM.update(ManualAddr, cStatus.manual);
  EEPROM.update(lcdvAddr, cStatus.lcdv);
  EEPROM.update(PresetAddr, cStatus.nomPreset);
  EEPROM.update(fcheckDoorAddr, cStatus.fcheckDoor);
  EEPROM.update(fcheckEngineAddr, cStatus.fcheckEngine);
}
void ReadLevelPreset(byte addr)
{
  EEPROM_Level_read(firstValueAddress + addr * 2, cStatus.PresetLevels);
}

void SaveSetLevelPreset(byte nomPreset) {
  EEPROM.update(PresetAddr, nomPreset);
  Switch2Auto();
}

byte fSaveMinMax(byte nom)
{
  byte r = 0;
  switch (nom) {
    case 1:  //min F
      EEPROM_Int_Write(levelHwAddress[0] + 0, curSuspention[0].RAW);
      EEPROM_Int_Write(levelHwAddress[0] + 2, curSuspention[1].RAW);
      r = 1;
      break;
    case 2:  //min R
      EEPROM_Int_Write(levelHwAddress[0] + 4, curSuspention[2].RAW);
      EEPROM_Int_Write(levelHwAddress[0] + 6, curSuspention[3].RAW);
      r = 2;
      break;
    case 3:   //max F
      EEPROM_Int_Write(levelHwAddress[1] + 0, curSuspention[0].RAW);
      EEPROM_Int_Write(levelHwAddress[1] + 2, curSuspention[1].RAW);
      r = 1;
      break;
    case 4:   //max R
      EEPROM_Int_Write(levelHwAddress[1] + 4, curSuspention[2].RAW);
      EEPROM_Int_Write(levelHwAddress[1] + 6, curSuspention[3].RAW);
      r = 2;
      break;
  }
  return r;
}
