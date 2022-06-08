void fLCDView4Int(int curArr[4])
{
  lcd.setCursor(1, 0);  lcd.print( curArr[0]); lcd.print("  ");
  lcd.setCursor(11, 0); if (curArr[1] > -1) lcd.print(" "); if (curArr[1] < 100) lcd.print(" "); lcd.print(curArr[1]); lcd.print("  ");
  lcd.setCursor(1, 1);  lcd.print(curArr[2]);  lcd.print("  ");
  lcd.setCursor(11, 1); if (curArr[3] > -1) lcd.print(" "); if (curArr[3] < 100) lcd.print(" "); lcd.print(curArr[3]); lcd.print("  ");
}
