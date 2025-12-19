void testerComposants() {

  if (test_led) {
    Serial.println("Test des LEDs");

    Serial.println("LED haut gauche (jaune)");
    digitalWrite(BROCHE_LED_HG, HIGH);
    delay(2000);

    Serial.println("LED haut droite (bleu)");
    digitalWrite(BROCHE_LED_HD, HIGH);
    delay(2000);

    Serial.println("LED bas droite (vert)");
    digitalWrite(BROCHE_LED_BD, HIGH);
    delay(2000);

    Serial.println("LED bas gauche (rouge)");
    digitalWrite(BROCHE_LED_BG, HIGH);
    delay(2000);

    Serial.println("buzzer à 440Hz");
    tone(BROCHE_BUZZER, 440, 1000);
    delay(1000);

    test_led = false;
  }

  if (digitalRead(BROCHE_BOUTON_HG) == HIGH) {
    Serial.println("Bouton haut gauche appuyé");
    digitalWrite(BROCHE_LED_HG, LOW);
    delay(300);
  }

  if (digitalRead(BROCHE_BOUTON_HD) == HIGH) {
    Serial.println("Bouton haut droite appuyé");
    digitalWrite(BROCHE_LED_HD, LOW);
    delay(300);
  }

  if (digitalRead(BROCHE_BOUTON_BD) == HIGH) {
    Serial.println("Bouton bas droite appuyé");
    digitalWrite(BROCHE_LED_BD, LOW);
    delay(300);
  }

  if (digitalRead(BROCHE_BOUTON_BG) == HIGH) {
    Serial.println("Bouton bas gauche appuyé");
    digitalWrite(BROCHE_LED_BG, LOW);
    delay(300);
  }
}