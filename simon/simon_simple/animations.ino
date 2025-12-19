

void animIntro() {
  digitalWrite(BROCHE_LED_HG, HIGH);
  delay(125);
  digitalWrite(BROCHE_LED_HD, HIGH);
  delay(125);
  digitalWrite(BROCHE_LED_BD, HIGH);
  delay(125);
  digitalWrite(BROCHE_LED_BG, HIGH);
  delay(125);
  digitalWrite(BROCHE_LED_HG, LOW);
  delay(125);
  digitalWrite(BROCHE_LED_HD, LOW);
  delay(125);
  digitalWrite(BROCHE_LED_BD, LOW);
  delay(125);
  digitalWrite(BROCHE_LED_BG, LOW);
  delay(625);
}


void animGaveOver() {
  tone(BROCHE_BUZZER, 80, 300);
  delay(400);
  tone(BROCHE_BUZZER, 50, 800);
  delay(1000);
}

void animWin() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(BROCHE_LED_HG, HIGH);
    digitalWrite(BROCHE_LED_HD, HIGH);
    digitalWrite(BROCHE_LED_BD, HIGH);
    digitalWrite(BROCHE_LED_BG, HIGH);
    delay(125);
    digitalWrite(BROCHE_LED_HG, LOW);
    digitalWrite(BROCHE_LED_HD, LOW);
    digitalWrite(BROCHE_LED_BD, LOW);
    digitalWrite(BROCHE_LED_BG, LOW);
    delay(125);
  }
}