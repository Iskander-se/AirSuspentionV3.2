void fLCDmenu()
{
  if (cMenu.wait > 38) lcd.clear();
//  switch (cMenu.nom)
//  {
//    case 1:
//
//      lcd.setCursor(5, 0); lcd.print(" MENU");
//      ValveSet.FL = 0;
//      ValveSet.FR = 0;
//      ValveSet.RL = 0;
//      ValveSet.RR = 0;
//      ValveSet.WP = 0;
//      ValveSet.SWITCH = 4;
//      break;
//    case 2:  // Выбор пресета
//      cStatus.nomPreset = cStatus.nomPreset + cMenu.shift;
//      if (cStatus.nomPreset < 1)cStatus.nomPreset = 0;
//      if (cStatus.nomPreset > 9)cStatus.nomPreset = 9;
//      if (cStatus.wait > 2) {
//        lcd.setCursor(4, 0); lcd.print("Preset "); lcd.print(cStatus.nomPreset); GetLevelInvent(cStatus.nomPreset);
//        lcd.setCursor(3, 1); lcd.print(cStatus.PresetLevels[0]); lcd.print("%  "); lcd.setCursor(6, 1); lcd.print(" <> "); lcd.print(cStatus.PresetLevels[1]); lcd.print("% ");
//      } else {
//        GetLevelInvent(cStatus.nomPreset);
//        SetLevelPreset(cStatus.nomPreset);
//      }
//      cMenu.shift = 0;
//      break;
//    case 3:
//      lcd.setCursor(0, 0); lcd.print("  MANUAL  SET  ");
//      lcd.setCursor(0, 1); lcd.print(" FRONT ][ REAR  ");
//      if (cMenu.shift != 0) {
//        Switch2Manual();
//        if (cStatus.mStep > 0) {
//          cMenu.nom = 31;
//        }
//        else {
//          cMenu.nom = 34;
//        }
//        cMenu.shift = 0;
//      }
//      break;
//    case 31:
//      lcd.setCursor(3, 0); lcd.print("   REAR   ");
//      lcd.setCursor(1, 1); lcd.print(" UP/DOWN ");
//      if (cStatus.mStep != 0) {
//        cStatus.manual = 1;
//        cStatus.wait = 20;
//        if (cMenu.shift < 0) {
//          ValveSet.SWITCH = 1;
//        }
//        else {
//          ValveSet.SWITCH = 2;
//        }
//      }
//      ValveSet.WP = 0;
//      ValveSet.FL = 0;
//      ValveSet.FR = 0;
//      ValveSet.RL = 1;
//      ValveSet.RR = 1;
//      if (cStatus.wait < 17) ValveSet.SWITCH = 0;
//      fVAGBlockWork();
//      GetPressure();
//      lcd.setCursor(10, 1); lcd.print(cStatus.pVAG); lcd.print("  ");
//      lcd.setCursor(1, 0); lcd.print( curSuspention[2].Avg / 10); lcd.print(" ");
//      if (curSuspention[3].Avg < 100) lcd.setCursor(14, 0); else lcd.setCursor(13, 0); lcd.print(curSuspention[3].Avg / 10);
//      cMenu.shift = 0;
//      break;
//    case 34:
//      lcd.setCursor(3, 0); lcd.print("   FRONT  ");
//      lcd.setCursor(1, 1); lcd.print(" UP/DOWN ");
//      if (cMenu.shift != 0) {
//        cStatus.manual = 1;
//        cStatus.wait = 20;
//        if (cStatus.mStep < 0) {
//          ValveSet.SWITCH = 1;
//        }
//        else {
//          ValveSet.SWITCH = 2;
//        }
//      }
//      ValveSet.WP = 0;
//      ValveSet.FL = 1;
//      ValveSet.FR = 1;
//      ValveSet.RL = 0;
//      ValveSet.RR = 0;
//      if (cStatus.wait < 17) ValveSet.SWITCH = 0;
//      lcd.setCursor(10, 1); lcd.print(cStatus.pVAG); lcd.print("  ");
//      lcd.setCursor(1, 0); lcd.print(curSuspention[0].Avg / 10); lcd.print(" ");
//      if (curSuspention[1].Avg < 100) lcd.setCursor(14, 0); else lcd.setCursor(13, 0); lcd.print(curSuspention[1].Avg / 10);
//      cMenu.shift = 0;
//      break;
//    case 4:
//      lcd.setCursor(0, 0); lcd.print(" MAIN/SERVICE  ");
//      if (cStatus.mStep == 0) {
//        lcd.setCursor(0, 1); lcd.print("SERVICE ][ SETS ");
//      } else {
//        if ( cStatus.mStep < 0) {
//          cMenu.nom = 40;
//        }
//        else {
//          cMenu.nom = 41;
//        }
//        cMenu.shift = 0;
//      }
//      break;
//    case 5:
//      if (cMenu.shift != 0) {
//        lcd.setCursor(1, 0); lcd.print("   ...WAIT    ");
//        lcd.setCursor(1, 1); lcd.print("               ");
//        Get4Pressure();
//        lcd.setCursor(5, 1); lcd.print(cStatus.pRES); lcd.print("kpa");
//        lcd.setCursor(5, 0); lcd.print("PRESS ");
//        cStatus.menu = 0;
//        cStatus.wait = 0;
//        //delay(5000);
//      } else {
//        lcd.setCursor(0, 0); lcd.print("  GET PRESSURE  ");
//        lcd.setCursor(0, 1); lcd.print(" 4 BANK + TANK  ");
//      }
//      break;
//
//    case 6:
//      lcd.setCursor(0, 0); lcd.print("  AIR CIRCUT  ");
//      if (cStatus.wait < 15) {
//        cStatus.wait = 15;
//        ValveSet.FL = 0;
//        ValveSet.FR = 0;
//        ValveSet.RL = 0;
//        ValveSet.RR = 0;
//        ValveSet.SWITCH = 5;
//        lcd.setCursor(1, 1); lcd.print("VAG"); lcd.print(cStatus.pVAG); lcd.print(" ");
//        lcd.setCursor(8, 1); lcd.print("RES"); lcd.print(cStatus.pRES); lcd.print(" ");
//        cMenu.shift = 0;
//      } else {
//        if (cMenu.shift == 0) {
//          lcd.setCursor(0, 1); lcd.print("    --------    ");
//        }
//        else {
//          lcd.setCursor(1, 1); lcd.print("Charge "); lcd.print(cStatus.pRES); lcd.print("  ");
//          ValveSet.FL = 0;
//          ValveSet.FR = 0;
//          ValveSet.RL = 0;
//          ValveSet.RR = 0;
//          ValveSet.SWITCH = 3;
//          cMenu.shift = 1;
//        }
//
//      }
//      break;
//    case 40:
//      lcd.setCursor(0, 0); lcd.print("  SERVICE MODE  ");
//      lcd.setCursor(0, 1); lcd.print("     START      ");
//      if (cStatus.wait < 3) {
//        cStatus.servicemode = true;
//        cStatus.manual = 0;
//      }
//      if (cMenu.shift != 0) {
//
//      }
//      break;
//    case 41:
//      lcd.setCursor(0, 0); lcd.print("     MAIN SET   ");
//      if (cMenu.shift == 0) {
//        lcd.setCursor(0, 1); lcd.print(" HWSETS X VIEW ");
//        if (cStatus.wait < 3) {
//          cStatus.wait = 10;
//        }
//      } else {
//        if ( cMenu.shift < 0) {
//          cMenu.nom = 44;
//        }
//        else {
//          cMenu.nom = 45;
//        }
//        cStatus.mStep = 0;
//      }
//      break;
//
//    case 44:
//      int curArr[4];
//      for (int i = 0; i < 4; i++) curArr[i] = curSuspention[i].RAW;
//      fLCDView4Int(curArr);
//      ValveSet.SWITCH = 4;
//      if (cStatus.wait > 5) {
//
//        lcd.setCursor(5, 0); lcd.print("Set LS");
//        lcd.setCursor(5, 1);
//        switch (cMenu.shift) {
//          case 1:    lcd.print("min F");  //min F
//            break;
//          case 2:    lcd.print("min R");  //min R
//            break;
//          case 3:    lcd.print("max F");  //max F
//            break;
//          case 4:    lcd.print("max R");   //max R
//            break;
//          default:
//            lcd.print("      ");
//            if (cStatus.wait < 5) {
//              cStatus.wait = 15;
//            }
//        }
//      } else {
//
//        Get_RAW_LS();
//        int nom = fSaveMinMax(cStatus.mStep);
//        fLCDViewSaveStr(nom);
//        cStatus.wait = 15;
//        cStatus.mStep = 0;
//        tone(piPin, 1000, 110);
//        lcd.clear();
//      }
//      break;
//    case 45:
//      if (cStatus.wait > 5) {
//        lcd.setCursor(5, 0); lcd.print("Set VIEW");
//        lcd.setCursor(5, 1);
//        switch (cMenu.shift) {
//          case 1:    lcd.print("Average ");
//            break;
//          case 2:    lcd.print(" RAW    ");
//            break;
//          case 3:    lcd.print("Amplitude ");
//            break;
//          default:
//            lcd.clear();
//            cStatus.mStep = 1;
//        }
//      } else {
//        cStatus.lcdv = cStatus.mStep;
//      }
//      break;
//    default:
//      lcd.clear();
//      lcd.setCursor(5, 0); lcd.print(" MENU");
//      //lcd.setCursor(4, 1); lcd.print(" "); lcd.print(cStatus.menu); lcd.print(" "); lcd.print(cStatus.mStep); lcd.print(" ");
//      cMenu.nom = 1;
//      break;
//  }
//
//  if (cStatus.wait < 1)
//  {
//    ValveSet.FL = 0;
//    ValveSet.FR = 0;
//    ValveSet.RL = 0;
//    ValveSet.RR = 0;
//    ValveSet.SWITCH = 4;
//    SetPreSetup();
//    lcd.clear();
//    //tone(piPin, 1100, 110); delay(300);
//    tone(piPin, 1000, 110);
//  }
}
