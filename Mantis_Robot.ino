struct Motors {
  byte pwmPin;
  byte dirPin;
};

Motors M1 = {2, 22};
Motors M2 = {3, 23};
Motors M3 = {5, 24};
Motors M4 = {6, 25};

const byte statusPin = 13;
const byte ch1Pin = 9;
const byte ch2Pin = 10;
const byte ch3Pin = 11;
const byte ch4Pin = 8;
const byte ch5Pin = 12;
const byte ch6Pin = 13;

int ch1Val;
int ch2Val;
int ch3Val;
int ch4Val;
bool ch5Val;
bool ch6Val;
int pwmSpeedA = 0;
int pwmSpeedB = 0;
int pwmSpeedC = 0;
int pwmSpeedD = 0;
bool dir = 0;

void mControlA(int mspeed, int mdir) {
  if (mdir == 0) {
    digitalWrite(M1.dirPin, LOW);
  } else {
    digitalWrite(M1.dirPin, HIGH);
  }
  analogWrite(M1.pwmPin, mspeed);
}


void mControlB(int mspeed, int mdir) {
  if (mdir == 0) {
    digitalWrite(M2.dirPin, LOW);
  } else {
    digitalWrite(M2.dirPin, HIGH);
  }
  analogWrite(M2.pwmPin, mspeed);
}

void mControlC(int mspeed, int mdir) {
  if (mdir == 0) {
    digitalWrite(M3.dirPin, LOW);
  } else {
    digitalWrite(M3.dirPin, HIGH);
  }
  analogWrite(M3.pwmPin, mspeed);
}

void mControlD(int mspeed, int mdir) {
  if (mdir == 0) {
    digitalWrite(M4.dirPin, LOW);
  } else {
    digitalWrite(M4.dirPin, HIGH);
  }
  analogWrite(M4.pwmPin, mspeed);
}


void setup() {
  Serial.begin(115200);
  pinMode(M1.pwmPin, OUTPUT);
  pinMode(M1.dirPin, OUTPUT);
  pinMode(M2.pwmPin, OUTPUT);
  pinMode(M2.dirPin, OUTPUT);
  pinMode(M3.pwmPin, OUTPUT);
  pinMode(M3.dirPin, OUTPUT);
  pinMode(M4.pwmPin, OUTPUT);
  pinMode(M4.dirPin, OUTPUT);
  pinMode(statusPin, OUTPUT);
  pinMode(ch1Pin, INPUT);
  pinMode(ch2Pin, INPUT);
  pinMode(ch3Pin, INPUT);
  pinMode(ch5Pin, INPUT);
  pinMode(ch6Pin, INPUT);
  digitalWrite(statusPin, LOW);
  
  setPwmFrequency(M1.pwmPin, 8);  //pins 2,3,5
  setPwmFrequency(M3.pwmPin, 8);  //pins 6,7,8
}

void loop() {
  ch1Val = readChannel(ch1Pin, -100, 100, 0);
  ch2Val = readChannel(ch2Pin, -100, 100, 0);
  ch3Val = readChannel(ch3Pin, 0, 255, 0);
  ch4Val = readChannel(ch4Pin, -100, 100, 0);
  ch5Val = readSwitch(ch5Pin, 0);
  ch6Val = readSwitch(ch6Pin, 0);
  Serial.print(ch1Val);
  Serial.write(9);
  Serial.print(ch2Val);
  Serial.write(9);
  Serial.print(ch3Val);
  Serial.write(9);
  Serial.print(ch4Val);
  Serial.write(9);
  Serial.print(ch5Val);
  Serial.write(9);
  Serial.println(ch6Val);
  pwmSpeedA = ch3Val;
  pwmSpeedB = ch3Val;
  pwmSpeedC = ch3Val;
  pwmSpeedD = ch3Val;
  
  dir = (ch5Val == 0) ? 1 : 0;

  //Serial.print("Dir: ");
  //Serial.println(dir);
  
  
  pwmSpeedA = pwmSpeedA + ch1Val;
  pwmSpeedB = pwmSpeedB + ch1Val;
  pwmSpeedC = pwmSpeedC - ch1Val;
  pwmSpeedD = pwmSpeedD - ch1Val;
  pwmSpeedA = constrain(pwmSpeedA, 0, 255);
  pwmSpeedB = constrain(pwmSpeedB, 0, 255);
  pwmSpeedC = constrain(pwmSpeedC, 0, 255);
  pwmSpeedD = constrain(pwmSpeedD, 0, 255);
  
  if (ch6Val == 0) {
    analogWrite(M1.pwmPin, 0);
    analogWrite(M2.pwmPin, 0);
    analogWrite(M3.pwmPin, 0);
    analogWrite(M4.pwmPin, 0);
  } else {
    mControlA(pwmSpeedA, dir);
    mControlB(pwmSpeedB, dir);
    mControlC(pwmSpeedC, dir);
    mControlD(pwmSpeedD, dir);
  }
}
