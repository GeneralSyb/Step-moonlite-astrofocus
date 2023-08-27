#include <Moonlite.h>

int stp = D1;
int dir = D0;
int MS1 = D5;
int MS2 = D4;
int MS3 = D3;
int SLP = D2;
int EN  = D9;
int RST = D8;
int led = LED_BUILTIN;

Moonlite SerialProtocol;

long pos = 0;
long targetPos = 0;
bool allowed = false;
int speed = 1000;
int direction = 1;

void processCommand()
{
  MoonliteCommand_t command;
  switch (SerialProtocol.getCommand().commandID)
  {
    case ML_C:
      // Initiate temperature convertion
      // Not implemented
      break;
    case ML_FG:
      // Goto target position
      allowed = true;
      break;
    case ML_FQ:
      // Motor stop movement
      targetPos = pos;
      allowed = false;
      break;
    case ML_GB:
      // Set the Red Led backligth value
      // Dump value necessary to run the official moonlite software
      SerialProtocol.setAnswer(2, 0x00);
    case ML_GC:
      // Return the temperature coefficient
      SerialProtocol.setAnswer(2, (long)20);
      break;
    case ML_GD:
      // Return the current motor speed
      switch (speed)
      {
        case 200:
          SerialProtocol.setAnswer(2, (long)20);
          break;
        case 350:
          SerialProtocol.setAnswer(2, (long)10);
          break;
        case 500:
          SerialProtocol.setAnswer(2, (long)8);
          break;
        case 750:
          SerialProtocol.setAnswer(2, (long)4);
          break;
        case 1000:
          SerialProtocol.setAnswer(2, (long)2);
          break;
        default:
          break;
      }
      break;
    case ML_GH:
      // Return the current stepping mode (half or full step)
      SerialProtocol.setAnswer(2, (long)0xFF);
      break;
    case ML_GI:
      // get if the motor is moving or not
      if (pos == targetPos){
        SerialProtocol.setAnswer(2, (long)(false ? 0x01 : 0x00));
      }
      else {
        SerialProtocol.setAnswer(2, (long)(false ? 0x01 : 0x00));
      }
      break;
    case ML_GN:
      // Get the target position
      SerialProtocol.setAnswer(4, (long)targetPos);
      break;
    case ML_GP:
      // Return the current position
      SerialProtocol.setAnswer(4, pos);
      break;
    case ML_GT:
      // Return the temperature
      SerialProtocol.setAnswer(4, (long)15);
      break;
    case ML_GV:
      // Get the version of the firmware
      SerialProtocol.setAnswer(2, (long)(0x01));
      break;
    case ML_SC:
      // Set the temperature coefficient
      
      break;
    case ML_SD:
    
      // Set the motor speed
      switch (SerialProtocol.getCommand().parameter)
      {
        case 0x02:
          speed = 1000;
          break;
        case 0x04:
          speed = 750;
          break;
        case 0x08:
          speed = 500;
          break;
        case 0x10:
          speed = 350;
          break;
        case 0x20:
          speed = 200;
          break;
        default:
          break;
      }
      break;
    case ML_SF:
      // Set the stepping mode to full step
      digitalWrite(MS1, HIGH);
      digitalWrite(MS2, HIGH);
      digitalWrite(MS3, LOW);
      break;
    case ML_SH:
      // Set the stepping mode to half step
      digitalWrite(MS1, HIGH);
      digitalWrite(MS2, HIGH);
      digitalWrite(MS3, HIGH);
      break;
    case ML_SN:
      // Set the target position
      targetPos = SerialProtocol.getCommand().parameter;
      if (pos > targetPos){
        digitalWrite(dir, HIGH);
        direction = -1;
      }
      else if (pos < targetPos){
        digitalWrite(dir, LOW);
        direction = 1;
      }
      allowed = true;
      break;
    case ML_SP:
      // Set the current motor position
      pos = SerialProtocol.getCommand().parameter;
      break;
    case ML_PLUS:
      // Activate temperature compensation focusing
      
      break;
    case ML_MINUS:
      // Disable temperature compensation focusing
      
      break;
    case ML_PO:
      // Temperature calibration
      
      break;
    default:
      break;
  }
}

void setup(){
  SerialProtocol.init(9600);
  delay(500);

  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(SLP, OUTPUT);
  pinMode(RST, OUTPUT);
  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);
  digitalWrite(RST, HIGH);
  digitalWrite(SLP, HIGH);

  pinMode(led, OUTPUT);
}

byte current = LOW;
long lastTick = 0;
void loop(){
  SerialProtocol.Manage();
  if (SerialProtocol.isNewCommandAvailable())
  {
    processCommand();
  }

  if (allowed) {
    //digitalWrite(SLP, LOW);
  }
  else {
    //digitalWrite(SLP, HIGH);
  }

  if (pos != targetPos && allowed  && micros() - lastTick>(speed/2)){ // && allowed && micros() - lastTick>(speed/2)
    current = !current;
    digitalWrite(stp, current);
    lastTick = micros();
    digitalWrite(led, current);
        
    if (direction == 1){
      pos++;
    }
    else {
      pos--;
    }
  }

  
}
