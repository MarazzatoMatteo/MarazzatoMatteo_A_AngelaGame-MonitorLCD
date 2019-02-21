//  Copyright ITT Eugenio Barsanti / Produced by MARAZZATO MATTEO - 4BI  //

#include <LiquidCrystal.h>

int mossa1;
int mossa2;
int numMeta;
int sommaMosse;
bool start = true;
//char convertitore[2];
int giocVincitore;
int numTurno;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int buttonSx = 8;
int buttonC = 9;
int buttonDx = 10;

void setup() 
{
  lcd.begin(16,2);
  numMeta = 30;
  sommaMosse = 0;
  giocVincitore = 2;
  numTurno = 0;
  lcd.setCursor(1,0);
  lcd.print("INIZIO PARTITA");
}

void loop() 
{
    delay(500);

  while (start == true)
  {
    inserisciGiocata();
      delay(1000);
  }

  /*cambiaTurno();

  if (sommaMosse != numMeta && sommaMosse < numMeta)
  {
    giocatore1();
      delay(1000);
  }
  
  if (sommaMosse != numMeta && sommaMosse < numMeta)
  {
    giocatore2();
      delay(1000);
  }

  vittoria();
    delay(1000);*/
}


void giocatore1()
{
  Serial.println("GIOCATORE 1");
  while (giocVincitore == 2)
  {
    while (Serial.available() == 0){} //indica quanti byte sono presenti nella casella di inserimento del monitor seriale (attraverso la codifica ASCII, null=0, 0=48, ...)
    mossa1 = Serial.parseInt(); //o Serial.read();
    if (numTurno == 1 && mossa1 >= 0 && mossa1 < 7)
    {
      sommaMosse = sommaMosse + mossa1;
      Serial.println("Mossa GIOCATORE 1: " + String(mossa1));
      delay(500);
      Serial.println("La somma totale è: " + String(sommaMosse));
      giocVincitore = 1;
    }

    else if (mossa1 != mossa2 && mossa1 > 0 && mossa1 < 7 && mossa1 != (7 - mossa2))
    {
      sommaMosse = sommaMosse + mossa1;
      Serial.println("Mossa GIOCATORE 1: " + String(mossa1));
      delay(500);
      Serial.println("La somma totale è: " + String(sommaMosse));
      giocVincitore = 1;
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
  while (giocVincitore == 1)
  {
    while (Serial.available() == 0){}
    mossa2 = Serial.parseInt();
    if (mossa2 != mossa1 && mossa2 >= 0 && mossa2 < 7 && mossa2 != (7 - mossa1))
    {
      sommaMosse = sommaMosse + mossa2;
      Serial.println("Mossa GIOCATORE 2: " + String(mossa2));
      delay(500);
      Serial.println("La somma totale è: " + String(sommaMosse));
      giocVincitore = 2;
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
  bool inizio = false;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Inserisci il N");
  lcd.setCursor(0,1);
  lcd.print("compreso 30 e 99");
  
  while (!inizio)
  {
    if (digitalRead(buttonSx) == HIGH && numMeta > 30)
    {
      numMeta--;
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print(numMeta);
      delay(200);
    }

    else if (digitalRead(buttonDx) == HIGH && numMeta < 99) 
    {
      numMeta++;
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print(numMeta);
      delay(200);
    }

    else if (digitalRead(buttonC) == HIGH)
    {
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print("OK");
      inizio = true;
      start = false;
    }
  }

/*  while (Serial.available() == 0){}
  delay(500);
  numMeta = Serial.parseInt();
  if (numMeta < 30 || numMeta > 99)
  {
    numMeta = 0;
    Serial.println("Numero non valido");
  }

  else 
  {
    start = false;
    Serial.println("Il numero da raggiungere è: " + String(numMeta));
      delay(500);
    Serial.println(" ");
  }
  //itoa(nummeta,convertitore, 10); //permette di convertire un numero in stringa itoa(n,c,b) n=numero da convertire - c=grandezza array o buffer (maggiore del numero di cifre del numero) - b=base in cui è scritto il numero (2 binaria, 10 decimale, 16 esadecimale)
  delay(1000);*/
}

void vittoria()
{
  if (sommaMosse == numMeta)
  {
    Serial.println("Ha vinto il GIOCATORE: " + String(giocVincitore));
    Serial.println(" ");
    reset();
  }

  else if (sommaMosse > numMeta)
  {
    if (giocVincitore == 1)
    {
      giocVincitore = 2;
      Serial.println("Ha vinto il GIOCATORE: " + String(giocVincitore));
      Serial.println(" ");
      reset();
    }
    
    else if (giocVincitore == 2)
    {
      giocVincitore = 1;
      Serial.println("Ha vinto il GIOCATORE: " + String(giocVincitore));
      Serial.println(" ");
      reset();
    }
  }

  else{}
}

void cambiaTurno()
{
  numTurno++;
  Serial.println("TURNO " + String(numTurno));
}

void reset()
{
  sommaMosse = 0;
  giocVincitore = 2;
  numTurno = 0;
  numMeta = 0;
  start = true;
}

//  Copyright ITT Eugenio Barsanti / Produced by MARAZZATO MATTEO - 4BI  //
