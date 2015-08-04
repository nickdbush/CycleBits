//Init pins
const int LED_PIN = 13;
const int DETECTOR_PIN = 4;

//For calculations of speed
const int RADIUS = 10; //cm
const float CIRCUMFERENCE = 2 * PI * RADIUS;

int lastDetectorState = HIGH;
int revs = 0; //revs per second
int detectorState = HIGH;

//Timers
long lastDebounceTime = millis();
long lastTime = millis();
long debounceDelay = 50;


void setup() {
  pinMode(DETECTOR_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  debounce();
  long current = millis();
  if((current - lastTime) >= 5000) {
    Serial.println(calculateSpeed());
    revs = 0;
    lastTime = current;
  }
}

void debounce() {
  //The detector is LOW if the circuit is complete
  int status = digitalRead(DETECTOR_PIN);
  //Check to see if changed
  if(status != lastDetectorState) {
    lastDebounceTime = millis();
  }
  //Check timers
  if((millis() - lastDebounceTime) >= debounceDelay) {
    if(status != detectorState) {
      detectorState = status;
      //Now do logic
      if(detectorState == LOW) {
        revs ++;
      }
    }
  }
  lastDetectorState = status;
}

float calculateSpeed() {
  return ((revs  * CIRCUMFERENCE) / 100) / 5;
}

