#include <Keypad.h>
#include <LiquidCrystal.h>
#include <stdlib.h>
#include <math.h>


LiquidCrystal lcd (8, 9, 10, 11, 12, 13); ///Se asigna los puertos que va a utilizar el display.


const byte ROWS = 4;
const byte COLS = 4;

char keys [ROWS] [COLS] =  ///Crea la matriz del KeyPad.
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},

};

//configurar los pines del KeyPad segun la posición de la matriz ej: 0,0 (pines 30,22) número:0.
//filas             1   2   3   4
byte rowPins[ROWS] = {30, 32, 34, 36};
//columnas          1   2   3   4
byte colPins[COLS] = {22, 24, 26, 28};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int i, auxAcceso;
char datom, menu;
String nom, apel, cargo;
int clave[4];

void teclado(int auxTeclado)
{

  if (auxTeclado == 1) ///Pide el password de cuatro números.
  {
    ////lcd llamada de la funcion del Dispĺay.
    lcd.clear(); ///Limpia el Display
    lcd.setCursor(0, 0); ///Posiciona el cursor en las cordenadas (x,y)
    lcd.print("DIGITE PASSWORD");///Imprime el texto "DIGITE PASSWORD"

    i = 0;
    do
    {
      datom = keypad.getKey(); ////Llamada a la función Teclado o la tecla que ha digitado.
      delay(30);

      if (datom != '\0')
      {
        switch (i + 1)
        {
          case 1:
            clave[0] = datom - 0X30; //quitar assci //Guarda el número ingresado por el KEYPAD
            lcd.setCursor(5, 1);
            lcd.print(clave[0]);
            delay (10);
            break;

          case 2:
            clave[1] = datom - 0X30;//Guarda el segundo número ingresado por el KEYPAD
            clave[0] = clave[0]*10 + clave[1];//Guarda el primer y segundo valor ingresado por el KEYPAD
            lcd.setCursor(6, 1);
            lcd.print(clave[1]);
            delay (10);
            break;

          case 3:
            clave[2] = datom - 0X30; //Guarda el tercer número ingresado por el KEYPAD
            lcd.setCursor(7, 1);
            lcd.print(clave[2]);
            delay (10);
            break;

          case 4:
            clave[3] = datom - 0X30; //Guarda el cuarto número ingresado por el KEYPAD
            clave[1] = clave[2]*10 + clave[3];//Guarda el tercer y cuarto valor ingresado por el KEYPAD
            lcd.setCursor(8, 1);
            lcd.print(clave[3]);
            delay (10);
            break;
        }
        i++;
      }

    } while (i < 4);

  } else ///Pide la opción de un digito
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DIGITE OPCION");

    i = 0;
    do {
      datom = keypad.getKey();
      delay(10);

      if (datom != '\0')
      {
        switch (i + 1)
        {
          case 1:
            clave[0] = datom - 0X30; //quitar assci
            lcd.setCursor(5, 1);
            lcd.print(clave[0]);
            delay (10);
            break;
        }
        i++;
      }
    } while (i < 1);

  }
}

void setup() {
  // put your setup code here, to run once:

  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  BIENVENIDOS A");

  lcd.setCursor(0, 1);
  lcd.print("PROGRAMACION ARDUINO");
  delay(1000);

  teclado(1); // 1: Teclado para el password
  delay(100);
  auxAcceso = 0;

  if ((clave[0] == 0) && (clave[1] == 0)) ///Si el valor ingresado es igual al password almacenado entra en Analisis
  {
    nom = "ANGELLO"; apel = "TRIVINO"; cargo = "ANALISIS";
    auxAcceso = 1;
  } else if ((clave[0] == 12) && (clave[1] == 34)) ///Entra en Diseño
  {
    nom = "DIEGO"; apel = "AREVALO"; cargo = "DISENIO";
    auxAcceso = 1;
  } else if ((clave[0] == 12) && (clave[1] == 35)) ///entra en Desarrollo
  {
    nom = "WILMER"; apel = "JOYA"; cargo = "DESARROLLO";
    auxAcceso = 1;
  }

  if (auxAcceso == 1) ///si es correcto el password entra.
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BIENVENIDO AL ");
    lcd.setCursor(0, 1);
    lcd.print("MENU: " + cargo);
    delay(1500);

    do
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" DIGITE 1: MENU");
      lcd.setCursor(0, 1);
      lcd.print(" DE " + nom + " O");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" 2: PARA SALIR");
      delay(1000);


      teclado(2);// 2: Teclado para escoger la opcion; salir del menu etc...
      delay(100);
      menu = clave[0];

      switch (menu)
      {
        case 1:
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("BIENVENIDO");
          lcd.setCursor(0, 1);
          lcd.print(nom + " " + apel);
          delay(1000);
          break;

        case 2:
          lcd.clear();
          lcd.print("  SALIENDO");
          lcd.setCursor(0, 1);
          lcd.print("  DEL MENU");
          delay(1000);
          break;

        default:
          lcd.clear();
          lcd.print("ERROR MARQUE UN");
          lcd.setCursor(0, 1);
          lcd.print("NUMERO, 1 O 2");
          delay(1000);
      }

    } while (menu != 2);

  } else {  ////si no es correcto el password, da mensaje de error.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" PASSWORD");
    lcd.setCursor(0, 1);
    lcd.print(" INCORRECTO");
    delay(1000);
  }
}
