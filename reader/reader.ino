const int sensorPin = A0;
const int calibrationDelay = 2000;
const int calibrationNumReads = 100;
const int calibrationReadSpacing = 20;

const int outputReadSpacing = 16;

float passiveBase;
float activeBase;

float averagedRead(int pin, int numReads, int readSpacing) {

  long total = 0;
  for(int i = 0; i < numReads; i++) {
    total += analogRead(pin);
    delay(readSpacing);
  }

  return (float)total / (float)numReads;
  
}

float calibrate(int raw) {

  return ((float)raw - passiveBase) / (activeBase - passiveBase);
  
}

void setup() {

  Serial.begin(115200);
  pinMode(sensorPin, INPUT);

  Serial.println("> Calibrating passive, relax the sensor...");
  delay(calibrationDelay);
  Serial.println("> Calibration started.");
  passiveBase = averagedRead(sensorPin, calibrationNumReads, calibrationReadSpacing);

  Serial.println("> Calibrating active, use the sensor...");
  delay(calibrationDelay);
  Serial.println("> Calibration started.");
  activeBase = averagedRead(sensorPin, calibrationNumReads, calibrationReadSpacing);

}

void loop() {

  int raw = analogRead(sensorPin);
  float calibrated = calibrate(raw);

  Serial.print("grip ");
  
  Serial.print(calibrated);
  Serial.print(' ');

  int bar = (int)(calibrated * 40.0f);
  for(int i = 0; i < bar; i++) Serial.print('>');
  Serial.println();
  
  delay(outputReadSpacing);

}
