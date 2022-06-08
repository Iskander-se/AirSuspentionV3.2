void MainTask(){
  GetLevels();
}

void LowSerialTask(){
  BTseriallog();
}

void PanelTask(){
  int lcdv=1;
  //GetKey();
  int curArr[4];
  switch (lcdv) {
    case 0:
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
      break;
  }
  fLCDView4Int(curArr);
  
}

void BTseriallog(){
  lcd.setCursor(5, 1); lcd.print(tempTimer3); lcd.print(" ");
  HwSerial.print(" "); HwSerial.print(tempTimer); HwSerial.print(" "); HwSerial.println(tempTimer3);
}
