/*
   Répéter une séquence de X étapes visuelle et sonore (LEDs et buzzer)
   Version simplifiée du jeu Simon

   Quimper, Flux, 18 déc. 2025, pierre@lesporteslogiques.net
   Debian 12 @ tenko / arduino 2.3.6

   Positionnement des leds et boutons

   1 2             jaune (HG)   bleu (HD)
   4 3             rouge (BG)   vert (BD)
  
   Une fonction d'autotest permet de confirmer que le circuit est correct 
     pour l'utiliser, passer la variable TESTMODE à true

   La longueur de séquence est modifiable par la variable longueur (défaut = 4)

   Versions
   000 : protocole d'autotest et c'est tout
   001 : structure de jeu
   002 : version finale

   Modifications possibles
     * niveau de difficulté variable selon le bouton qui démarre la partie : 4, 6, 8, 8 rapide
     * modifier la longueur de séquence à chaque bonne séquence trouvée
       commencer à 1 puis 2, etc. (C'est le principe du Simon original)
      pour cela, il faut 
        * définir une longueur indépassable (64)
        * choisir une longueur variable, modifiée à chaque tour

*/




/* ********************************************* */
/* Liste des broches utilisées par le cicuit     */

#define BROCHE_BOUTON_HG 2  // Haut gauche
#define BROCHE_BOUTON_HD 3  // Haut droite
#define BROCHE_BOUTON_BD 4  // Bas droite
#define BROCHE_BOUTON_BG 5  // Bas gauche
#define BROCHE_LED_HG 7     // Haut gauche = jaune
#define BROCHE_LED_HD 8     // Haut droite = bleu
#define BROCHE_LED_BD 9     // Bas droite = vert
#define BROCHE_LED_BG 10    // Bas gauche = rouge
#define BROCHE_BUZZER 12



/* ********************************************* */
/* Variables utilisées par l'autotest            */

bool TESTMODE = false;  // Mettre à true pour lancer le programme en mode autotest et vérifier les composants
bool test_led = true;   // Pour n'effectuer qu'un seul test des LEDs et du buzzer


/* ******************************************** */
/* Variables utilisées par le jeu               */

int GAMEMODE = 0;
bool hg, hd, bd, bg;        // Les évènements boutons seront stockées dans ces variables

// Séquence à deviner
const int longueur = 4;     // longueur de la séquence à deviner
int sequence[longueur];     // tableau d'entiers à x cases : ex. de sequence : 1, 3, 4, 2

// Réponses joueurs
int sequence_reponse[longueur];           // tableau qui contiendra la réponse du joueur
int etape = 0;                            // Où en est on dans la répétition de la séquence
long last_pressed;                        // Enregistrer le moment du dernier bouton pressé pour la réponse
int duree_reponse = 3500;                 // (ms) temps maximum autorisé entre chaque appui
bool nouvelle_reponse = false;            // Utilisé pour tester le bouton appuyé

// Timings
int allumage = 400;         // (ms) temps d'affichage des LEDs et activation buzzer


void setup() {

  pinMode(BROCHE_BOUTON_HG, INPUT);
  pinMode(BROCHE_BOUTON_HD, INPUT);
  pinMode(BROCHE_BOUTON_BD, INPUT);
  pinMode(BROCHE_BOUTON_BG, INPUT);
  pinMode(BROCHE_LED_HG, OUTPUT);
  pinMode(BROCHE_LED_HD, OUTPUT);
  pinMode(BROCHE_LED_BD, OUTPUT);
  pinMode(BROCHE_LED_BG, OUTPUT);
  pinMode(BROCHE_BUZZER, OUTPUT);

  randomSeed(analogRead(A0));  // initialiser le hasard par niveau de tension capté sur la broche A0!

  Serial.begin(9600);          // (Debug) Démarrer une communication série avec l'ordi à 9600 bauds
}



void loop() {


  if (TESTMODE) {
    while (true) {
      testerComposants();
    }
  }


  /* En attente d'une interaction  *************************   */

  if (GAMEMODE == 0) {
    testerEtatBoutons();                     // Checker l'état des boutons
    if (hg || hd || bd || bg) GAMEMODE = 1;  // si on appuie sur un bouton -> initialiser une nouvelle partie
  }


  /* Initialisation d'une nouvelle partie  ******************** */

  if (GAMEMODE == 1) {
    
    Serial.println("Nouvelle partie déclenchée");
    animIntro();             // jouer l'anim d'intro        
    definirSequence();       // Définir la séquence qu'il faudra découvrir

    // Jouer la séquence afin de la mémoriser
    for (int i = 0; i < longueur; i = i + 1) {
      playCouleur(sequence[i]);
    }

    last_pressed = millis();
    etape = 0;
    GAMEMODE = 2;  // Se placer dans le mode d'attente du joueur (GAMEMODE = 2)
  }


  /* Attente de la réponse et vérification            **************          */

  if (GAMEMODE == 2) {
    
    if (millis() - last_pressed >= duree_reponse) { // Temps imparti dépassé, c'est perdu
      GAMEMODE = 8;

    } else {                                        // On est dans le temps imparti

      // Y a t'il eu un appui bouton ?
      testerEtatBoutons();     // Mettre à jour l'état des boutons
      nouvelle_reponse = false;
      if (hg || hd || bd || bg) nouvelle_reponse = true;

      // Quel bouton ?
      if (hg) sequence_reponse[etape] = 1;
      if (hd) sequence_reponse[etape] = 2;
      if (bd) sequence_reponse[etape] = 3;
      if (bg) sequence_reponse[etape] = 4;

      if (nouvelle_reponse) {  // Il y a eu un appui bouton, on vérifie la réponse

        playCouleur(sequence_reponse[etape]); // Afficher la couleur
        
        // Comparer la réponse à la séquence préétablie
        bool resultat = comparerSequences(sequence, sequence_reponse, etape);      

        if (resultat == false) {   // Mauvaise réponse
          GAMEMODE = 8;
        } else {                   // Bonne réponse

          // A t'on complété la séquence, si c'est le cas fin de partie
          if (etape == longueur - 1) {  // La séquence est complète et correcte
            GAMEMODE = 9;
          } else {                      // Sinon, on attend la réponse suivante
            etape = etape + 1;
            last_pressed = millis();    // Remettre le compteur à zéro
          }
        }
      }
    }
  }

  /* Game Over :/                        **************          */
  if (GAMEMODE == 8) {
    animGaveOver();  // Animation, musique
    GAMEMODE = 0;  // On repasse en mode 0
  }

  /* C'est gagné :)                      **************          */
  if (GAMEMODE == 9) {
    animWin();  // Animation, musique
    GAMEMODE = 0;
  }
}
