const int SENSOR_PIN = 4;
const int LED_PIN = 3;

const int OPEN_RANGE_MIN = 2265;
const int OPEN_RANGE_MAX = 2290;

const unsigned long ALERT_DELAY = 5000;

bool doorOpen = false;
bool alertActive = false;
unsigned long doorOpenedTime = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Fridge door alert started");
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);

  bool currentDoorOpen = (sensorValue >= OPEN_RANGE_MIN && sensorValue <= OPEN_RANGE_MAX);

  if (currentDoorOpen && !doorOpen) {
    doorOpen = true;
    alertActive = false;
    doorOpenedTime = millis();

    Serial.print("Sensor value: ");
    Serial.print(sensorValue);
    Serial.println(" | State: OPEN");
  }

  if (!currentDoorOpen && doorOpen) {
    doorOpen = false;
    alertActive = false;
    digitalWrite(LED_PIN, LOW);

    Serial.print("Sensor value: ");
    Serial.print(sensorValue);
    Serial.println(" | State: CLOSED");
  }

  if (doorOpen && !alertActive) {
    if (millis() - doorOpenedTime >= ALERT_DELAY) {
      alertActive = true;
      digitalWrite(LED_PIN, HIGH);

      Serial.print("Sensor value: ");
      Serial.print(sensorValue);
      Serial.println(" | ALERT: Door left open too long!");
    }
  }

  if (!doorOpen) {
    digitalWrite(LED_PIN, LOW);
  }

  Serial.print("Sensor value: ");
  Serial.print(sensorValue);
  Serial.print(" | Door: ");
  Serial.print(doorOpen ? "OPEN" : "CLOSED");
  Serial.print(" | LED: ");
  Serial.println(alertActive ? "ON" : "OFF");

  delay(300);
}