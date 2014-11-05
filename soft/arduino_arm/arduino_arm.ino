// Based on http://www.lamja.com/?p=504

#include <avr/interrupt.h>
#include <EEPROM.h>
#define HDServoMode 20
#define SerialInterfaceSpeed 115200    // Serial interface Speed
#define THERM A3
#define HEAT 8
#define MOT 6
#define LED 13

static unsigned int iCount;

static volatile uint8_t **OutPortTable;
static uint8_t* OutBitTable;

static volatile uint8_t *OutPortTable1[20] = {&PORTD,&PORTD,&PORTD,&PORTD,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB};
static uint8_t OutBitTable1[20] = {4,8,16,32,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
static volatile uint8_t *OutPortTable2[20] = {&PORTB,&PORTB,&PORTB,&PORTB,&PORTD,&PORTD,&PORTD,&PORTD,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB};
static uint8_t OutBitTable2[20] = {2,2,2,2,4,8,16,32,2,2,2,2,2,2,2,2,2,2,2,2};
static volatile uint8_t *OutPortTable3[20] = {&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTD,&PORTD,&PORTD,&PORTD,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB};
static uint8_t OutBitTable3[20] = {2,2,2,2,2,2,2,2,4,8,16,32,2,2,2,2,2,2,2,2};
static volatile uint8_t *OutPortTable4[20] = {&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTD,&PORTD,&PORTD,&PORTD,&PORTB,&PORTB,&PORTB,&PORTB};
static uint8_t OutBitTable4[20] = {2,2,2,2,2,2,2,2,2,2,2,2,4,8,16,32,2,2,2,2};

static unsigned int* MotorPW;
static unsigned int ServoPW[20] = {24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000};
static byte ServoInvert[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static byte Timer2Toggle;
static volatile uint8_t *OutPort1A = &PORTD;
static volatile uint8_t *OutPort1B = &PORTB;
static uint8_t OutBit1A = 4;
static uint8_t OutBit1B = 16;
static volatile uint8_t *OutPortNext1A = &PORTD;
static volatile uint8_t *OutPortNext1B = &PORTB;
static uint8_t OutBitNext1A = 4;
static uint8_t OutBitNext1B = 16;

static long ServoStepsHD[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static long ServoLastPos[20] = {24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000,24000};
static long StepsToGo[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
static int ChannelCount;

static long ServoGroupStepsToGo = 0;
static long ServoGroupServoLastPos[20];
static long ServoGroupStepsHD[20];
static int ServoGroupChannel[20];
static int ServoGroupNbOfChannels = 0;

static char SerialIn;
static int SerialCommand = 0; //0= none, 1 = '#' and so on...
static long SerialNumbers[10];
static int SerialNumbersLength = 0;
static boolean FirstSerialChannelAfterCR = 1;

static int SerialChannel = 0;
static long SerialPulseHD = 24000;
static long SerialPulseOffsetHD[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static long SerialPulseOffsetTempHD = 0;
static long SerialSpeedHD = 0;
static long SerialTime = 0;
static long SerialNegative = 1;
static boolean SerialNeedToMove = 0;
static char SerialCharToSend[50] = ".detratS slennahC 81 ovreSDH";
static int SerialNbOfCharToSend = 0;  //0= none, 1 = [0], 2 = [1] and so on...


void ServoMove(int Channel, long PulseHD, long SpeedHD, long Time)
{
// Use ServoMove(int Channel, long PulseHD, long SpeedHD, long Time) to control servos.
// One of th SpeedHD or Time can be set to 0 to only  use the other one for speed. If both are used,
// the one that takes the longest time, will be used
  ServoGroupMove(Channel, CheckRange(PulseHD), SpeedHD, Time);
  ServoGroupMoveActivate();
}

void setup()
{
 uint8_t id = EEPROM.read(10);
 pinMode(HEAT, OUTPUT);
  pinMode(MOT, OUTPUT);
 pinMode(THERM, INPUT);
 if (id==4)
 {
  OutPortTable = OutPortTable4;
  OutBitTable = OutBitTable4;
  MotorPW = &ServoPW[19];
 }
 else if (id==3)
 {
  OutPortTable = OutPortTable3;
  OutBitTable = OutBitTable3;
  MotorPW = &ServoPW[18];
 }
 else if (id==2)
 {
  OutPortTable = OutPortTable2;
  OutBitTable = OutBitTable2;
  MotorPW = &ServoPW[17];
 }
 else
 {
  OutPortTable = OutPortTable1;
  OutBitTable = OutBitTable1;
  MotorPW = &ServoPW[16];
 }
 Serial.begin(SerialInterfaceSpeed);
 ServoSetup();                       //Initiate timers and misc.
  
  #if HDServoMode == 18
    TIMSK0 = 0;                       // Disable timer 0. This can reduse jitter some more. But it's used for delay() funtions.
  #endif                              // This will disable delay()!
}

void loop()
{
    CheckSerial();
    uint16_t th;
    th=analogRead(THERM);
    if (th > 265)
    {
      digitalWrite(HEAT, 1);
      digitalWrite(LED, 1);
    }
    else if (th < 205)
    {
      digitalWrite(HEAT, 0);
      digitalWrite(LED, 0); 
    }
    
    if (*MotorPW > 24000)
    {
      analogWrite(MOT, (*MotorPW)-24000);
    }
    else
    {
      digitalWrite(MOT, 0);
    }
}

long CheckRange(long PulseHDValue)
{
  if(PulseHDValue > 39680) return 39680;
  else if(PulseHDValue < 8320) return 8320;
  else return PulseHDValue;
}

long CheckChannelRange(long CheckChannel)
{
  if(CheckChannel >= HDServoMode) return (HDServoMode-1);
  else if(CheckChannel < 0) return 0;
  else return CheckChannel;
}

void CheckSerial()     //Serial command interpreter.
{
  int i = 0;

  if(Serial.available() > 0)
  {
    SerialIn = Serial.read();
    Serial.write(SerialIn);
    if(SerialIn == '#') 
    {
      SerialCommand = 1;
      SerialNeedToMove = 1;
      if(!FirstSerialChannelAfterCR) ServoGroupMove(SerialChannel, CheckRange(SerialPulseHD), SerialSpeedHD, SerialTime);
      FirstSerialChannelAfterCR = 0;
    }
    if(SerialIn == 'p') SerialCommand = 2;
    if(SerialIn == 's') SerialCommand = 3;
    if(SerialIn == 'T') SerialCommand = 4;
    if(SerialIn == 'P') 
    {
      if(SerialCommand == 9) SerialCommand = 10;   // 'QP'
      else SerialCommand = 5;                      // 'P'
    }
    if(SerialIn == 'S') SerialCommand = 6;
    if(SerialIn == 'o') {SerialCommand = 7; SerialNeedToMove = 1;}
    if(SerialIn == 'O') {SerialCommand = 8; SerialNeedToMove = 1;}
    if(SerialIn == 'Q') SerialCommand = 9; 
    if(SerialIn == 'I') SerialCommand = 11; 
    if(SerialIn == 'N') SerialCommand = 12; 
    if(SerialIn == ' ' || SerialIn == 13)
    {
      if(SerialCommand == 1) {SerialChannel = CheckChannelRange(ConvertSerialNumbers()); SerialCommand = 0;}
      if(SerialCommand == 2) {SerialPulseHD = ConvertSerialNumbers() + SerialPulseOffsetHD[SerialChannel]; SerialCommand = 0;}
      if(SerialCommand == 3) {SerialSpeedHD = ConvertSerialNumbers(); SerialCommand = 0;}
      if(SerialCommand == 4) {SerialTime = ConvertSerialNumbers(); SerialCommand = 0;}
      if(SerialCommand == 5) {SerialPulseHD = ConvertSerialNumbers()*16 + SerialPulseOffsetHD[SerialChannel]; SerialCommand = 0;}
      if(SerialCommand == 6) {SerialSpeedHD = ConvertSerialNumbers()*16; SerialCommand = 0;}
      if(SerialCommand == 11) {ServoInvert[SerialChannel] = 1; SerialCommand = 0;}
      if(SerialCommand == 12) {ServoInvert[SerialChannel] = 0; SerialCommand = 0;}
      if(SerialCommand == 7) 
      {
        SerialPulseOffsetTempHD = ConvertSerialNumbers();
        SerialPulseHD = ServoPW[SerialChannel] - SerialPulseOffsetHD[SerialChannel] + SerialPulseOffsetTempHD;
        SerialTime = 10;
        SerialPulseOffsetHD[SerialChannel] = SerialPulseOffsetTempHD;
        SerialCommand = 0;
      }
      if(SerialCommand == 8) 
      {
        SerialPulseOffsetTempHD = ConvertSerialNumbers()*16;
        SerialPulseHD = ServoPW[SerialChannel] - SerialPulseOffsetHD[SerialChannel] + SerialPulseOffsetTempHD;
        SerialTime = 10;
        SerialPulseOffsetHD[SerialChannel] = SerialPulseOffsetTempHD;
        SerialCommand = 0;
      }
      if(SerialIn == 13) 
      {
        if(SerialNeedToMove)
        {
          ServoGroupMove(SerialChannel, CheckRange(SerialPulseHD), SerialSpeedHD, SerialTime);
          ServoGroupMoveActivate();
          FirstSerialChannelAfterCR = 1;
          SerialCommand = 0;
          SerialSpeedHD = 0;
          SerialTime = 0;
          SerialNeedToMove = 0;
        }
        if(SerialCommand == 9)
        {
          SerialCharToSend[0] = '.';
          for(i = 0; i < 20 ; i++)
          {
            if(StepsToGo[i] > 0) SerialCharToSend[0] = '+';
          }
          SerialNbOfCharToSend = 1;
          SerialCommand = 0;
        }
        else if(SerialCommand == 10)
        {
          for(i = 0; i < 18 ; i++)
          {
            SerialCharToSend[17 - i] = (ServoPW[i] - SerialPulseOffsetHD[i])/160;
          }
          SerialNbOfCharToSend = 18;
          SerialCommand = 0;
        }
      }
    }
    if((SerialIn >= '0') && (SerialIn <= '9')) {SerialNumbers[SerialNumbersLength] = SerialIn - '0'; SerialNumbersLength++;}
    if(SerialIn == '-') SerialNegative = -1;
  }
}

long ConvertSerialNumbers()         //Converts numbers gotten from serial line to long.
{
  int i = 0;
  
  long ReturnValue = 0;
  long Multiplier = 1;
  if(SerialNumbersLength > 0)
  {
    for(i = SerialNumbersLength-1 ; i >= 0 ; i--)
    {
      ReturnValue += SerialNumbers[i]*Multiplier;
      Multiplier *=10;
    }
    ReturnValue *= SerialNegative;
    SerialNumbersLength = 0;
    SerialNegative = 1;
    return ReturnValue;
  }
  else return 0;
}

void ServoGroupMove(int Channel, long PulseHD, long SpeedHD, long Time)    //ServoMove used by serial command interpreter
{
  long StepsToGoSpeed=0;
  long StepsToGoTime=0;
  
  ServoGroupChannel[ServoGroupNbOfChannels] = Channel;
  if(SpeedHD < 1) SpeedHD = 3200000;
  StepsToGoSpeed = abs((PulseHD - ServoPW[Channel]) / (SpeedHD / 50));
  StepsToGoTime = Time / 20;
  if(StepsToGoSpeed > ServoGroupStepsToGo) ServoGroupStepsToGo = StepsToGoSpeed;
  if(StepsToGoTime > ServoGroupStepsToGo) ServoGroupStepsToGo = StepsToGoTime;
  ServoGroupChannel[ServoGroupNbOfChannels] = Channel;
  ServoGroupServoLastPos[ServoGroupNbOfChannels] = PulseHD;
  ServoGroupNbOfChannels++;
}

void ServoGroupMoveActivate()                       //ServoMove used by serial command interpreter
{
  int ServoCount = 0;
  
  for(ServoCount = 0 ; ServoCount < ServoGroupNbOfChannels ; ServoCount++)
  {
    ServoStepsHD[ServoGroupChannel[ServoCount]] = (ServoGroupServoLastPos[ServoCount] - ServoPW[ServoGroupChannel[ServoCount]]) / ServoGroupStepsToGo;
    StepsToGo[ServoGroupChannel[ServoCount]] =ServoGroupStepsToGo;
    ServoLastPos[ServoGroupChannel[ServoCount]] = ServoGroupServoLastPos[ServoCount];
  }
  ServoGroupNbOfChannels = 0;
  ServoGroupStepsToGo = 0;
}

void RealTime50Hz() //Move servos every 20ms to the desired position.
{
  if(SerialNbOfCharToSend) {SerialNbOfCharToSend--; Serial.print(SerialCharToSend[SerialNbOfCharToSend]);}
  for(ChannelCount = 0; ChannelCount < 20; ChannelCount++)
  {
    if(StepsToGo[ChannelCount] > 0)
    {
      ServoPW[ChannelCount] += ServoStepsHD[ChannelCount];
      StepsToGo[ChannelCount] --;
    }
    else if(StepsToGo[ChannelCount] == 0)
    {
      ServoPW[ChannelCount] = ServoLastPos[ChannelCount];
      StepsToGo[ChannelCount] --;
    }
  }
}

ISR(TIMER1_COMPA_vect) // Interrupt routine for timer 1 compare A. Used for timing each pulse width for the servo PWM.
{ 
  *OutPort1A &= ~OutBit1A;                //Pulse A finished. Set to low
}

ISR(TIMER1_COMPB_vect) // Interrupt routine for timer 1 compare A. Used for timing each pulse width for the servo PWM.
{ 
  *OutPort1B &= ~OutBit1B;                //Pulse B finished. Set to low
}

ISR(TIMER2_COMPA_vect) // Interrupt routine for timer 2 compare A. Used for timing 50Hz for each servo.
{ 
  *OutPortNext1A |= OutBitNext1A;         // Start new pulse on next servo. Write pin HIGH
  *OutPortNext1B |= OutBitNext1B;         // Start new pulse on next servo. Write pin HIGH
}

ISR(TIMER2_COMPB_vect) // Interrupt routine for timer 2 compare A. Used for timing 50Hz for each servo.
{ 
  TIFR1 = 255;                                       // Clear  pending interrupts
  TCNT1 = 0;                                         // Restart counter for timer1
  TCNT2 = 0;                                         // Restart counter for timer2
  sei();
  *OutPort1A &= ~OutBit1A;                           // Set pulse low to if not done already
  *OutPort1B &= ~OutBit1B;                           // Set pulse low to if not done already
  OutPort1A = OutPortTable[Timer2Toggle];            // Temp port for COMP1A
  OutBit1A = OutBitTable[Timer2Toggle];              // Temp bitmask for COMP1A
  OutPort1B = OutPortTable[Timer2Toggle+10];         // Temp port for COMP1B
  OutBit1B = OutBitTable[Timer2Toggle+10];           // Temp bitmask for COMP1B
  if(ServoInvert[Timer2Toggle]) OCR1A = 48000 - ServoPW[Timer2Toggle] - 7985;                // Set timer1 count for pulse width.
  else OCR1A = ServoPW[Timer2Toggle]-7980;
  if(ServoInvert[Timer2Toggle+10]) OCR1B = 48000 - ServoPW[Timer2Toggle+10]-7970;            // Set timer1 count for pulse width.
  else OCR1B = ServoPW[Timer2Toggle+10]-7965;
  Timer2Toggle++;                                    // Next servo in line.
  if(Timer2Toggle==10)
  { 
    Timer2Toggle = 0;                                // If next servo is grater than 9, start on 0 again.
    RealTime50Hz();                                  // Do servo management
  }
  OutPortNext1A = OutPortTable[Timer2Toggle];        // Next Temp port for COMP1A
  OutBitNext1A = OutBitTable[Timer2Toggle];          // Next Temp bitmask for COMP1A
  OutPortNext1B = OutPortTable[Timer2Toggle+10];     // Next Temp port for COMP1B
  OutBitNext1B = OutBitTable[Timer2Toggle+10];       // Next Temp bitmask for COMP1B
}

void ServoSetup()
{
  // Timer 1 setup(16 bit):
  TCCR1A = 0;                     // Normal counting mode 
  TCCR1B = 1;                     // Set prescaler to 1 
  TCNT1 = 0;                      // Clear timer count 
  TIFR1 = 255;                    // Clear  pending interrupts
  TIMSK1 = 6;                     // Enable the output compare A and B interrupt 
  // Timer 2 setup(8 bit):
  TCCR2A = 0;                     // Normal counting mode 
  TCCR2B = 6;                     // Set prescaler to 256
  TCNT2 = 0;                      // Clear timer count 
  TIFR2 = 255;                    // Clear pending interrupts
  TIMSK2 = 6;                     // Enable the output compare A and B interrupt 
  OCR2A = 93;                     // Set counter A for about 500us before counter B below;
  OCR2B = 124;                    // Set counter B for about 2000us (20ms/10, where 20ms is 50Hz);
  
  #if HDServoMode == 18
  #elif HDServoMode == 20
    for(iCount=2;iCount<6;iCount++) pinMode(iCount, OUTPUT);    // Set all pins used to output:
  #endif
}
