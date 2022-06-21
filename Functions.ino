void setPwmFrequency(int pin, int divisor) {
  int myEraser = 7;
  byte mode;
  switch(divisor) {
    case 1: mode = 0x01; break;
    case 8: mode = 0x02; break;
    case 64: mode = 0x03; break;
    case 256: mode = 0x04; break;
    case 1024: mode = 0x05; break;
    default: return;
  }
    if (pin == 4 || pin == 13) {
    TCCR0B &= ~myEraser;
    TCCR0B |= mode; 
  }
    if (pin == 11 || pin == 12) {
    TCCR1B &= ~myEraser;
    TCCR1B |= mode; 
  }
    if (pin == 9 || pin == 10) {
    TCCR2B &= ~myEraser;
    TCCR2B |= mode; 
  }
  if (pin == 2 || pin == 3 || pin == 5) {
    TCCR3B &= ~myEraser;
    TCCR3B |= mode; 
  }
    if (pin == 6 || pin == 7 || pin == 8) {
    TCCR4B &= ~myEraser;
    TCCR4B |= mode; 
  } 
}

// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
