
void testerEtatBoutons() {

  hg = false;
  hd = false;
  bd = false;
  bg = false;

  if (digitalRead(BROCHE_BOUTON_HG) == HIGH) hg = true;
  if (digitalRead(BROCHE_BOUTON_HD) == HIGH) hd = true;
  if (digitalRead(BROCHE_BOUTON_BD) == HIGH) bd = true;
  if (digitalRead(BROCHE_BOUTON_BG) == HIGH) bg = true;
}


void definirSequence() {

  Serial.print("Nouvelle séquence : ");
  for (int i = 0; i < longueur; i = i + 1) {
    sequence[i] = random(1, 5);  // un nombre entre 1 et 4
    Serial.print(sequence[i]);
    Serial.print(",");
  }
  Serial.println();
}

bool comparerSequences(int seq1[], int seq2[], int taille) {
  for (int i = 0; i <= taille; i = i+1) {
    if (seq1[i] != seq2[i]) {
      return false;
    }
  }
  return true;
}

void playCouleur(int couleur) {
  switch (couleur) {
    case 1:
      digitalWrite(BROCHE_LED_HG, HIGH);
      tone(BROCHE_BUZZER, 440, allumage);  // tone() ne bloque pas le déroulement du programme
      delay(allumage);
      digitalWrite(BROCHE_LED_HG, LOW);
      break;  // ne pas évaluer les cas suivants
    case 2:
      digitalWrite(BROCHE_LED_HD, HIGH);
      tone(BROCHE_BUZZER, 880, allumage);
      delay(allumage);
      digitalWrite(BROCHE_LED_HD, LOW);
      break;
    case 3:
      digitalWrite(BROCHE_LED_BD, HIGH);
      tone(BROCHE_BUZZER, 1760, allumage);
      delay(allumage);
      digitalWrite(BROCHE_LED_BD, LOW);
      break;
    case 4:
      digitalWrite(BROCHE_LED_BG, HIGH);
      tone(BROCHE_BUZZER, 3520, allumage);
      delay(allumage);
      digitalWrite(BROCHE_LED_BG, LOW);
      break;
  }
  delay(allumage / 2);
}