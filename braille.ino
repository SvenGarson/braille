void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Define Required Pin Modes
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // Screw Around
  for (int i = 2; i <= 9; ++i)
  {
    digitalWrite(i, HIGH);
  }
}
