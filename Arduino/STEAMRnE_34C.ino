void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

String state = "0";

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    if (Serial.find("state:(") ){
      state = Serial.readStringUntil(')');
    }
    Serial.println(state);
    if (state == "0") {
      digitalWrite(2, HIGH);
    } else {
      digitalWrite(2, LOW);
    }
  }
}
