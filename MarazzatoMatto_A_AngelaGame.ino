//  Copyright ITT Eugenio Barsanti / Produced by MARAZZATO MATTEO - 4BI  //

int mossa1;
int mossa2;
int nummeta;
int sommamosse;
bool start = true;
//char convertitore[2];
int giocvincitore;
int numturno;

void setup() 
{
  Serial.begin(9600);
  nummeta = 0;
  sommamosse = 0;
  giocvincitore = 2;
  numturno = 0;
  Serial.println("INIZIO PARTITA");
  Serial.println(" ");
}

void loop() 
{
    delay(200);

  while (start == true)
  {
    inserisciGiocata();
      delay(1000);
  }

  cambiaTurno();

  if (sommamosse != nummeta && sommamosse < nummeta)
  {
    giocatore1();
      delay(1000);
  }
  
  if (sommamosse != nummeta && sommamosse < nummeta)
  {
    giocatore2();
      delay(1000);
  }

  vittoria();
    delay(1000);
}


void giocatore1()
{
  Serial.println("GIOCATORE 1");
  while (giocvincitore == 2)
  {
    while (Serial.available() == 0){} //indica quanti byte sono presenti nella casella di inserimento del monitor seriale (attraverso la codifica ASCII, null=0, 0=48, ...)
    mossa1 = Serial.parseInt(); //o Serial.read();
    if (numturno == 1 && mossa1 >= 0 && mossa1 < 7)
    {
      sommamosse = sommamosse + mossa1;
      Serial.println("Mossa GIOCATORE 1: " + String(mossa1));
      delay(500);
      Serial.println("La somma totale è: " + String(sommamosse));
      giocvincitore = 1;
    }

    else if (mossa1 != mossa2 && mossa1 > 0 && mossa1 < 7 && mossa1 != (7 - mossa2))
    {
      sommamosse = sommamosse + mossa1;
      Serial.println("Mossa GIOCATORE 1: " + String(mossa1));
      delay(500);
      Serial.println("La somma totale è: " + String(sommamosse));
      giocvincitore = 1;
    }

    else 
    {
      Serial.println("Mossa non valida, inserisci un altro valore");
    }
  }
}

void giocatore2()
{
  Serial.println("GIOCATORE 2");
  while (giocvincitore == 1)
  {
    while (Serial.available() == 0){}
    mossa2 = Serial.parseInt();
    if (mossa2 != mossa1 && mossa2 >= 0 && mossa2 < 7 && mossa2 != (7 - mossa1))
    {
      sommamosse = sommamosse + mossa2;
      Serial.println("Mossa GIOCATORE 2: " + String(mossa2));
      delay(500);
      Serial.println("La somma totale è: " + String(sommamosse));
      giocvincitore = 2;
      Serial.println(" ");
    }

    else 
    {
      Serial.println("Mossa non valida, inserisci un altro valore");
    } 
  }
}

void inserisciGiocata()
{
  Serial.println("Inserisci il numero da raggiungere (compreso tra 30 e 99)");
  while (Serial.available() == 0){}
  delay(500);
  nummeta = Serial.parseInt();
  if (nummeta < 30 || nummeta > 99)
  {
    nummeta = 0;
    Serial.println("Numero non valido");
  }

  else 
  {
    start = false;
    Serial.println("Il numero da raggiungere è: " + String(nummeta));
      delay(500);
    Serial.println(" ");
  }
  //itoa(nummeta,convertitore, 10); //permette di convertire un numero in stringa itoa(n,c,b) n=numero da convertire - c=grandezza array o buffer (maggiore del numero di cifre del numero) - b=base in cui è scritto il numero (2 binaria, 10 decimale, 16 esadecimale)
  delay(1000);
}

void vittoria()
{
  if (sommamosse == nummeta)
  {
    Serial.println("Ha vinto il GIOCATORE: " + String(giocvincitore));
    Serial.println(" ");
    reset();
  }

  else if (sommamosse > nummeta)
  {
    if (giocvincitore == 1)
    {
      giocvincitore = 2;
      Serial.println("Ha vinto il GIOCATORE: " + String(giocvincitore));
      Serial.println(" ");
      reset();
    }
    
    else if (giocvincitore == 2)
    {
      giocvincitore = 1;
      Serial.println("Ha vinto il GIOCATORE: " + String(giocvincitore));
      Serial.println(" ");
      reset();
    }
  }

  else{}
}

void cambiaTurno()
{
  numturno++;
  Serial.println("TURNO " + String(numturno));
}

void reset()
{
  sommamosse = 0;
  giocvincitore = 2;
  numturno = 0;
  nummeta = 0;
  start = true;
}

//  Copyright ITT Eugenio Barsanti / Produced by MARAZZATO MATTEO - 4BI  //
