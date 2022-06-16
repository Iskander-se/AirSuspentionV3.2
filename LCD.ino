void fLCDView4Int(int curArr[4])
{
  lcd.setCursor(1, 0);  lcd.print( curArr[0]); lcd.print("  ");
  lcd.setCursor(11, 0); if (curArr[1] > -1) lcd.print(" "); if (curArr[1] < 100) lcd.print(" "); lcd.print(curArr[1]); lcd.print("  ");
  lcd.setCursor(1, 1);  lcd.print(curArr[2]);  lcd.print("  ");
  lcd.setCursor(11, 1); if (curArr[3] > -1) lcd.print(" "); if (curArr[3] < 100) lcd.print(" "); lcd.print(curArr[3]); lcd.print("  ");
}

void fLCDViewIntents() {
  if ((ValveSet.SWITCH == 1) || (ValveSet.SWITCH == 2)) {
    lcd.setCursor(0, 0);  if (ValveSet.FL) lcd.write(ValveSet.SWITCH); else lcd.print(" ");
    lcd.setCursor(15, 0); if (ValveSet.FR) lcd.write(ValveSet.SWITCH); else lcd.print(" ");
    lcd.setCursor(0, 1);  if (ValveSet.RL) lcd.write(ValveSet.SWITCH); else lcd.print(" ");
    lcd.setCursor(15, 1); if (ValveSet.RR) lcd.write(ValveSet.SWITCH); else lcd.print(" ");
  }
  else {
    lcd.setCursor(0, 0);  if (IntentSetBL.FL) lcd.write(0xFF); else lcd.print(" ");
    lcd.setCursor(15, 0); if (IntentSetBL.FR) lcd.write(0xFF); else lcd.print(" ");
    lcd.setCursor(0, 1);  if (IntentSetBL.RL) lcd.write(0xFF); else lcd.print(" ");
    lcd.setCursor(15, 1); if (IntentSetBL.RR) lcd.write(0xFF); else lcd.print(" ");
  }
}
int LCDTimer = 0;
void fLCDViewAuto() {
  lcd.setCursor(5, 0); lcd.print(cStatus.pVAG);
  switch (IntentSetBL.SWITCH) {
    case 1: lcd.print(" FU");
      break;
    case 2: lcd.print(" RU");
      break;
    case 3: lcd.print(" FD");
      break;
    case 4: lcd.print(" RD");
      break;
    default: lcd.print(" --");
  }
  if (LCDTimer > 10) LCDTimer = 0;
  LCDTimer++;
  lcd.setCursor(5, 1);
  switch (LCDTimer) {
    case 1:
      lcd.print(cStatus.pRES);
      if (cAlertArr.Power != NULL) lcd.print("A!  ");
      else lcd.print("kpa ");
      break;
     case 8:
        lcd.print(tempTimer3); lcd.print(" ");

  }

  void fLCDViewStM() {
    if (cStatus.manual == 1) {
      lcd.clear();
      cStatus.manual = 2;
    }
    if (LCDTimer > 13) LCDTimer = 0;
    LCDTimer++;
    lcd.setCursor(6, 0); lcd.print("man");
    lcd.setCursor(5, 1);
    switch (LCDTimer) {
      case 1: if (cAlertArr.Valves != NULL) {
          lcd.print("VAGeRR!");
          break;
        }
      case 3: if (cAlertArr.BanksF != NULL) {
          lcd.print("FT-eRR!");
          break;
        }
      case 5: if (cAlertArr.BanksR != NULL) {
          lcd.print("RT-eRR!");
          break;
        }
      case 7: if (cAlertArr.Power != NULL) {
          lcd.print("AIReRR!");
          break;
        }
      case 9: lcd.print(cStatus.pRES); lcd.print("kpa ");
    }
  }

  void fLCDViewSaveStr(byte nom)
  {
    lcd.setCursor(0, nom); lcd.print("#");
    lcd.setCursor(15, nom); lcd.print("#");
    lcd.setCursor(6, 1); lcd.print("SAVE");
  }
