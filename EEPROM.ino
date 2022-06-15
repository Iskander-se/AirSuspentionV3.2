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
