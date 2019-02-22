//  Copyright ITT Eugenio Barsanti / Produced by MARAZZATO MATTEO - 4BI  //

#include <LiquidCrystal.h>

int mossa;
int mossaPrec;
int numMeta;
int sommaMosse;
int giocVincitore;
int numTurno;
int newMossa;

bool start;
bool passaTurno;

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
  mossa = 0;
  
  start = true;
  passaTurno = false;
  
  lcd.setCursor(1,0);
  delay(1000);
  lcd.print("INIZIO PARTITA");
  for(int i = 0; i<15; i++)
  {
    lcd.scrollDisplayLeft();
    delay(100);
  }

}

void loop() 
{
    delay(1000);

  while (start == true)
  {
    inserisciGiocata();
    printGiocata(numMeta);
      delay(1000);
  }

  lcd.clear();

  mossaPrec = mossa;
  while (passaTurno == false)
  {
    game();
  }
  
  printMossa(newMossa);
  passaTurno = false;

  delay(1000);

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

int game()
{
  
  if (digitalRead(buttonSx) == HIGH && mossa > 1)
    {
      mossa--;
      lcd.setCursor(7,0);
      lcd.print(mossa);
      delay(200);
    }

    else if (digitalRead(buttonDx) == HIGH && mossa < 6) 
    {
      mossa++;
      lcd.setCursor(7,0);
      lcd.print(mossa);
      delay(200);
    }

    else if (digitalRead(buttonC) == HIGH && mossa != mossaPrec && mossa != 7-mossaPrec)
    {
      passaTurno = true;
      delay(500);
      newMossa = mossa;
    }
}

void printMossa(int displayMossa)
{
  if (displayMossa > 0)
  {
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Numero");
    lcd.setCursor(0,1);
    lcd.print("selezionato: ");
    lcd.setCursor(14,1);
    lcd.print(displayMossa);
  }
}


/*void giocatore2()
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
}*/

void inserisciGiocata()
{
  bool inizio = false;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Inserisci il");
  lcd.setCursor(0,1);
  lcd.print("numero finale");
  lcd.setCursor(14,1);
  lcd.print(numMeta);
  
  while (!inizio)
  {
    if (digitalRead(buttonSx) == HIGH && numMeta > 30)
    {
      numMeta--;
      lcd.setCursor(14,1);
      lcd.print(numMeta);
      delay(200);
    }

    else if (digitalRead(buttonDx) == HIGH && numMeta < 99) 
    {
      numMeta++;
      lcd.setCursor(14,1);
      lcd.print(numMeta);
      delay(200);
    }

    else if (digitalRead(buttonC) == HIGH)
    {
      inizio = true;
      start = false;
    }
  }
}

void printGiocata(int displayGiocata)
{
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Numero");
  lcd.setCursor(0,1);
  lcd.print("selezionato: ");
  lcd.setCursor(14,1);
  lcd.print(displayGiocata);
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
