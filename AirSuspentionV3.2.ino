#include <LiquidCrystal_I2C_OLED.h>
#include <ADS1115_WE.h>
#include <EEPROM.h>


int tempTimer = 1;
int tempTimer2 = 1;
int tempTimer3 = 1;

////////// Constants
#define ePin  PB4 // Engine ON
#define dPin  PB3 // Door open
#define piPin  PB13 //
#define bN1pin PB14
#define bN2pin PB15
#define bN3pin PA8

#define vFL   PA1
#define vFR   PA2
#define vRR   PA3
#define vRL   PA4
#define vPC   PA6  // реле компрессора
#define vRES  PA7 //
#define vEXH  PB0 //


//#define vFL   PA0
//#define vFR   PA1
//#define vRR   PA2
//#define vRL   PA3
//#define vPC   PA5  // реле компрессора
//#define vRES  PA6 //
//#define vEXH  PA7 //

#define LCDadr 0x27
#define ADCPadr 0x48
#define ADCSadr 0x49

#define PresetAddr 30
#define ManualAddr 31
#define lcdvAddr 32
#define firstValueAddress 60

HardwareSerial HwSerial(PA10, PA9);
LiquidCrystal_I2C lcd(LCDadr, 16, 2);
ADS1115_WE ADCP = ADS1115_WE(ADCPadr);
ADS1115_WE ADCS = ADS1115_WE(ADCSadr);
byte up[] =   {  B00000,  B00100,  B01110,  B10101,  B00100,  B00100,  B00000,  B00000};
byte down[] = {  B00000,  B00000,  B00100,  B00100,  B10101,  B01110,  B00100,  B00000};
const byte levelHwAddress[3] = {4, 12, 20};      // Переменная для хранения первых адресов
const int8_t CompressorTimeLimit = 50;


struct {
  byte Levels = 0;
  byte Valves = 0;
  byte BanksF = 0;
  byte BanksR = 0;
  byte Power = 0;
} cWarningArr;

///////// Variables
int16_t LowLevels[4];
int16_t HighLevels[4];


bool waitLowUpF = 0;
bool waitLowUpR = 0;

struct stSuspention {
  int16_t RAW;
  int16_t Min;
  int16_t Max;
  int16_t Avg;
  int16_t Apld;
  int16_t Intent;
} curSuspention[4];

struct {
  bool FL; bool FR;
  bool RL; bool RR;
  byte SWITCH;   // 0=Stop; 1=UP; 2=DOWN; 3=CHARGE; 4=Free
  byte WP;      // 0=NO; 1=NEED;
  byte LastSWITCH;
} ValveSet = {0, 0, 0, 0, 4, 0, 0};

struct stIntentBlock {
  int FL; int FR;
  int RL; int RR;
  byte SWITCH;
  byte HOPE;
  bool startI;
} IntentSetBL = {0, 0, 0, 0, 0, 0, 1};

struct {
  int16_t curTargetLevels[4];
  int8_t addr;
} IntentHeap;

struct {
  int servicemode = 0;
  int manual = 0;
  bool alert = 0;
  int airPowerF = 1; // 0=OFF; 1=ON; 2=OVER
  int engine = 0;
  int door = 0;
  bool mute = 0;
  int lcdv = 1;
  int pVAG ;
  int pRES ;
  int wait;
  int cBlur;
  int airPowerT = 0;
  int shiftL = 0; // Экспериментальный сдвиг
  int shiftR = 0; // Экспериментальный сдвиг
  int8_t PresetLevels[2] = {50, 50};
  int nomPreset = 0;
} cStatus;

struct {
  int wait = 0;
  int nom = 0;
  int shift = 0;
  bool bs, b1, b2;
} cMenu;

struct stTarget {
  int curDeviation;
  int curTargetL = 50;
  int curTargetR = 50;
  int curSwitch = 0;
};

unsigned long previousMillis = 0;
const long period = 1000;
int globalTimer;
struct Axis {
  int L = 0;
  int R = 0;
  int Switch = 0;
};

struct sTimeer {
  unsigned long previous;
  long period;
};


struct SerialPack {
  char command;
  byte nom;
  int8_t data[2];
} packFromHU;

void setup() {
  lcd.init();
  lcd.clear();
  lcd.init();
  lcd.init();
  lcd.createChar(1, up);
  lcd.createChar(2, down);
  //Serial.begin();
  HwSerial.begin(115200);
  pinMode(ePin, INPUT);
  pinMode(dPin, INPUT);
  pinMode(bN1pin, INPUT);
  pinMode(bN2pin, INPUT);
  pinMode(bN3pin, INPUT);
  pinMode(vFL, OUTPUT);
  pinMode(vFR, OUTPUT);
  pinMode(vRL, OUTPUT);
  pinMode(vRR, OUTPUT);
  pinMode(vRES, OUTPUT);
  pinMode(vEXH, OUTPUT);
  pinMode(vPC, OUTPUT);
  pinMode(piPin, OUTPUT);
  digitalWrite(vFL, 0);
  digitalWrite(vFR, 0);
  digitalWrite(vRL, 0);
  digitalWrite(vRR, 0);
  lcd.backlight();
  lcd.home();
  lcd.setCursor(3, 0);
  lcd.print("GALANT  EA");
  lcd.setCursor(1, 1);
  lcd.print("Air Suspention");
  if (!ADCS.init() || !ADCP.init()) {

  }
  ADCS.setVoltageRange_mV(ADS1115_RANGE_6144);
  ADCP.setVoltageRange_mV(ADS1115_RANGE_6144);
  //GetPreSetup();// Начальная инициализация параметров и состояния
  GetLevelHwSetup(); // Инициализация записаных значений настроек датчиков
  //GetLevelInvent(cStatus.nomPreset);
  delay(500);
  lcd.init();
  lcd.clear();
}

sTimeer MainTime = {0, 100};
sTimeer LowTasklTime = {0, 2000};
sTimeer InterfaceTime = {0, 200};

void loop() {

  unsigned long currentMillis = millis();
  if (currentMillis - MainTime.previous >= MainTime.period) {
    MainTime.previous = currentMillis;
    MainTask();
    tempTimer3 = tempTimer2;
    tempTimer2 = 0;
  } else {
    tempTimer2++;
  }

  if (currentMillis - LowTasklTime.previous >= LowTasklTime.period) {
    LowTasklTime.previous = currentMillis;
    LowSerialTask();
    tempTimer = 0;
  } else {
    tempTimer++;
  }

  if (currentMillis - InterfaceTime.previous >= InterfaceTime.period) {
    InterfaceTime.previous = currentMillis;
    PanelTask();

  }

}
