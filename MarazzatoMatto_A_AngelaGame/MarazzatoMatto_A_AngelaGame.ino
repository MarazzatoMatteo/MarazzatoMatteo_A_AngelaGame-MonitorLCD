//  Copyright ITT Eugenio Barsanti / Produced by MARAZZATO MATTEO - 4BI  //

#include <LiquidCrystal.h>

int mossa;
int mossaPrec;
int numMeta;
int sommaMosse;
int numTurno;
bool primaGiocata;

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
  numTurno = 1;
  mossa = 0;
  primaGiocata = true;
  
  start = true;
  passaTurno = false;
  
  lcd.setCursor(1,0);
  lcd.print("INIZIO PARTITA");
  delay(2000);
  for(int i = 0; i<16; i++)
  {
    lcd.scrollDisplayLeft();
    delay(120);
  }

}

void loop() 
{
    delay(1000);

  while (start == true)
  {
    printInizio();
    inserisciMeta();
    printMeta(numMeta);
      delay(1000);
  }
  
    lcd.clear();

    mossaPrec = mossa;
    printGame();
  
    while (passaTurno == false)
    {
      game();
    }
  
    printSommaMosse(sommaMosse);
    passaTurno = false;

      delay(1000);

    if (vittoria() == true){}

    else 
    {
      if (numTurno == 1){numTurno = 2;}
      else if (numTurno == 2){numTurno = 1;}
    }
}

void game()
{
  if (primaGiocata == true && digitalRead(buttonSx) == HIGH && mossa > 0)
  {
    mossa--;
    lcd.setCursor(15,0);
    lcd.print(mossa);
    delay(200);
  }


  /*else if (primaGiocata == true && digitalRead(buttonDx) == HIGH && mossa < 6) 
  {
    mossa++;
    lcd.setCursor(15,0);
    lcd.print(mossa);
    delay(200);
  }*/

  if (digitalRead(buttonSx) == HIGH && mossa > 1 || primaGiocata == true && digitalRead(buttonSx) == HIGH && mossa > 0)
  {
    mossa--;
    lcd.setCursor(15,0);
    lcd.print(mossa);
    delay(200);
  }

  else if (digitalRead(buttonDx) == HIGH && mossa < 6) 
  {
    mossa++;
    lcd.setCursor(15,0);
    lcd.print(mossa);
    delay(200);
  }

  else if (digitalRead(buttonC) == HIGH && mossa != mossaPrec && mossa != 7-mossaPrec || primaGiocata == true && digitalRead(buttonC) == HIGH && mossa == 0)
  {
    passaTurno = true;
    primaGiocata = false;
    sommaMosse = sommaMosse + mossa;
  }
}

void printGame()
{
  if (numTurno == 1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Giocatore 1: ");
    lcd.setCursor(15,0);
    lcd.print(mossa);
    lcd.setCursor(0,1);
    lcd.print("Scorsa mossa: ");
    lcd.setCursor(15,1);
    lcd.print(mossaPrec);
  }

  else
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Giocatore 2: ");
    lcd.setCursor(15,0);
    lcd.print(mossa);
    lcd.setCursor(0,1);
    lcd.print("Scorsa mossa: ");
    lcd.setCursor(15,1);
    lcd.print(mossaPrec);
  }
  
}

void printSommaMosse(int displayMossa)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Somma Mosse");
  lcd.setCursor(14,0);
  lcd.print(displayMossa);
}

void inserisciMeta()
{
  bool inizio = false;
  
  while (!inizio)
  {
    if (digitalRead(buttonSx) == HIGH && numMeta > 30)
    {
      numMeta--;
      lcd.setCursor(14,1);
      lcd.print(numMeta);
      delay(100);
    }

    else if (digitalRead(buttonDx) == HIGH && numMeta < 99) 
    {
      numMeta++;
      lcd.setCursor(14,1);
      lcd.print(numMeta);
      delay(100);
    }

    else if (digitalRead(buttonC) == HIGH)
    {
      inizio = true;
      start = false;
    }
  }
}

void printMeta(int displayGiocata)
{
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Numero");
  lcd.setCursor(0,1);
  lcd.print("selezionato: ");
  lcd.setCursor(14,1);
  lcd.print(displayGiocata);
}

void printInizio()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Inserisci la");
  lcd.setCursor(0,1);
  lcd.print("meta finale:");
  lcd.setCursor(14,1);
  lcd.print(numMeta);
}


bool vittoria()
{
  if (sommaMosse == numMeta)
  {
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("GIOCATORE");
    lcd.setCursor(13,0);
    lcd.print(numTurno);
    lcd.setCursor(5,1);
    lcd.print("VINCE");
    reset();

    return true;
  }

  else if (sommaMosse > numMeta)
  {
    if (numTurno == 1)
    {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("GIOCATORE");
      lcd.setCursor(13,0);
      lcd.print(2);
      lcd.setCursor(6,1);
      lcd.print("VINCE");
      reset();

      return true;
    }
    
    else if (numTurno == 2)
    {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("GIOCATORE");
      lcd.setCursor(13,0);
      lcd.print(1);
      lcd.setCursor(6,1);
      lcd.print("VINCE");
      reset();

      return true;
    }
  }

  else{return false;}
}


void reset()
{
  mossa = 0;
  mossaPrec = 0;
  sommaMosse = 0;
  numTurno = 1;
  numMeta = 30;
  start = true;
  primaGiocata = true;
}

//  Copyright ITT Eugenio Barsanti / Produced by MARAZZATO MATTEO - 4BI  //
