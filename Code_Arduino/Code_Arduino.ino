#include <Keypad.h> ///Libreria del Teclado
#include <LiquidCrystal.h> ///Libreria del Display
#include <EEPROM.h> ///Libreria de la memoria EEPROM
#include <stdlib.h> ///Liberia Estandar
#include <math.h> ////Libreria para calculos matematicos


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

int i, retardo = 30, idUsuario = 0; /// i: auxiliar. retardo: pausas. idUsuario: 1,2 o 3
char datom, menu;////datom: dato de memoria.
String nom, apel, cargo;/////nom: nombre. apel: apellido. cargo: diseño, analisis....
int clave[4], dato[2];////clave: almacena las claves ingresadas. dato: almacena los datos
                      ///leidos en la EEPROM.

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

void MenuInicio() ///Menu de inicio del Diseñador o Administrador
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BIENVENIDO AL ");
  lcd.setCursor(0, 1);
  lcd.print("MENU DISENO: ");
  delay(retardo);

  do
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DIGITE 1:PERFIL");
    lcd.setCursor(0, 1);
    lcd.print(" DE JOYA ");
    delay(retardo);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DIGITE 2:PERFIL");
    lcd.setCursor(0, 1);
    lcd.print(" DE DIEGO ");
    delay(retardo);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DIGITE 3:PERFIL");
    lcd.setCursor(0, 1);
    lcd.print(" DE ANGELO ");
    delay(retardo);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" DIGITE 4: SALIR");
    lcd.setCursor(0, 1);
    lcd.print(" DEL MENU ");
    delay(retardo);

    teclado(2);// 2: Teclado para escoger la opcion; salir del menu etc...
    delay(retardo);
    menu = clave[0];

    switch (menu)
    {

      case 1:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("MENU DE");
        lcd.setCursor(0, 1);
        lcd.print("WILMER JOYA");
        delay(retardo);
        idUsuario = 0;
        MenuPerfil();
        break;

      case 2:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("MENU DE");
        lcd.setCursor(0, 1);
        lcd.print("DIEGO AREVALO");
        delay(retardo);
        idUsuario = 1;
        MenuPerfil();
        break;

      case 3:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("MENU DE");
        lcd.setCursor(0, 1);
        lcd.print("ANGELLO TRIVINO");
        delay (retardo);
        idUsuario = 2;
        MenuPerfil();
        break;

      case 4:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SALIENDO DEL");
        lcd.setCursor(0, 1);
        lcd.print("MENU PERFIL");
        delay (retardo);
        break;

      default:
        lcd.clear();
        lcd.print("ERROR MARQUE UN");
        lcd.setCursor(0, 1);
        lcd.print("NUMERO, 1 AL 4");
        delay (retardo);
    }

  } while (menu != 4);

  loop();
}

void MenuPerfil () { /////Menú perfil de cada usuario.
  do {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DIGITE 1:NUEVA");  ///Cambio de contraseña del usuario
    lcd.setCursor(0, 1);
    lcd.print(" CONTRASENA ");
    delay (retardo);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DIGITE 2:");
    lcd.setCursor(0, 1);
    lcd.print("SALIR AL MENU");
    delay(retardo);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DIGITE 3:");
    lcd.setCursor(0, 1);
    lcd.print("SALIR AL INICIO ");
    delay(retardo);
    teclado(2);
    delay(retardo);
    menu = clave[0];
    switch (menu)
    {

      case 1: ////Nueva contraseña
        i = 0;
        do {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("DIGITE NEW");
          lcd.setCursor(0, 1);
          lcd.print("CONTRASENA:");
          delay(retardo);
          teclado(1);
          dato[0] = clave[0];
          dato[1] = clave[1];
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("CONFIRME");
          lcd.setCursor(0, 1);
          lcd.print("CONTRASENA:");
          delay(retardo);
          teclado(1);
          if (CompararDatos() == 2) {
            EscribirEEPROM();
            delay(retardo);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("CONTRASENA");
            lcd.setCursor(0, 1);
            lcd.print("GUARDADA");
            delay(retardo);
            i = 1;
          } else
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("CONTRASENAS");
            lcd.setCursor(0, 1);
            lcd.print("NO COINCIDEN");
            delay(retardo);
          }

        } while (i != 1);

        break;

      case 2:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("VOLVIENDO");
        lcd.setCursor(0, 1);
        lcd.print("MENU PERFIL");
        delay (retardo);
        MenuInicio();
        break;

      case 3:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("VOLVIENDO");
        lcd.setCursor(0, 1);
        lcd.print("AL INICIO");
        delay (retardo);
        loop();
        break;

      default:
        lcd.clear();
        lcd.print("ERROR MARQUE UN");
        lcd.setCursor(0, 1);
        lcd.print("NUMERO, 1 AL 3");
        delay (retardo);

    }

  } while (menu != 2 || menu != 3);

}

void MenuUsuario() { /////Menu del usuario.

  if (idUsuario == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BIENVENIDO");
    lcd.setCursor(0, 1);
    lcd.print("WILMER JOYA");
    delay(retardo);
  } else if (idUsuario == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BIENVENIDO");
    lcd.setCursor(0, 1);
    lcd.print("DIEGO AREVALO");
    delay(retardo);
  } else if (idUsuario == 2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BIENVENIDO");
    lcd.setCursor(0, 1);
    lcd.print("ANGELO TRIVINO");
    delay(retardo);
  }

  do {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DIGITE 1:");
    lcd.setCursor(0, 1);
    lcd.print("SALIR ");
    delay(retardo);
    teclado(2);
    delay(retardo);
    menu = clave[0];
    switch (menu)
    {

      case 1:
        i = 0;

        break;

      default:
        lcd.clear();
        lcd.print("ERROR MARQUE UN");
        lcd.setCursor(0, 1);
        lcd.print("NUMERO, 1 SALIR");
        delay (retardo);
        break;
    }

  } while (menu != 1);

  loop();
}

void EscribirEEPROM() ///Escribir EEPROM interna del Arduino
{
  int i = 0;
  if (idUsuario == 0)
    i = 0;
  else if (idUsuario == 1)
    i = 2;
  else if (idUsuario == 2)
    i = 4;

  int k = 0;
  for (int j = i; j < i + 2; j++)
  {
    EEPROM.write(j, clave[k]);
    k++;
  }

}

void LeerEEPROM() ///Leer EEPROM Interna del Arduino
{
  int i = 0;
  if (idUsuario == 0)
    i = 0;
  else if (idUsuario == 1)
    i = 2;
  else if (idUsuario == 2)
    i = 4;


  int k = 0;
  for (int j = i; j < i + 2; j++)
  {
    dato[k] = EEPROM.read(j);
    k++;
  }

}

bool ComprobarUsuario() {//Comprueba el usuario
  bool comp = false;

  for (int i = 0; i < 3; i++) { ////Lee la EEPROM cuatro veces por ser 4 digitos de la clave
    idUsuario = i;
    LeerEEPROM();

    if ((clave[0] == dato[0]) && (clave[1] == dato[1])) {

      comp = true;
      break;
    }
  }

  return comp;

}

int CompararDatos() ////Compara los datos ingresados con los almacenados en la EEPROM 
{
  int auxComp = 0;
  for (int i = 0; i < 2; i++) {
    if (dato[i] == clave[i])
      auxComp++;
  }

  return auxComp;
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
  lcd.print("PROGRAMA ARDUINO");
  delay(retardo);
  lcd.clear();//limpialcd
  lcd.setCursor(0, 0);
  lcd.print(" ANGELO  ");
  lcd.setCursor(0, 1);
  lcd.print(" TRIVINO ");
  delay(retardo);
  lcd.clear();//limpialcd
  lcd.setCursor(0, 0);
  lcd.print(" DIEGO ");
  lcd.setCursor(0, 1);
  lcd.print(" AREVALO ");
  lcd.setCursor(0, 1);
  delay(retardo);
  lcd.clear();//limpialcd
  lcd.setCursor(0, 0);
  lcd.print(" WILMER ");
  lcd.setCursor(0, 1);
  lcd.print(" JOYA ");
  lcd.setCursor(0, 1);
  delay(retardo);
  lcd.clear();//limpialcd
  teclado(1); // 1: Teclado para el password
  delay(retardo);

  if ((clave[0] == 0) && (clave[1] == 0))
  {
    ///Menu del Diseñador o Administrador, se encarga de cambiar los Passwords
    MenuInicio();

  } else {
    
    LeerEEPROM(); ///Si el anterior es incorrecto, busca las contraseñas de los usuarios.
    
    if (ComprobarUsuario()) {
      MenuUsuario();

    } else { //// Si no encuentra ninguna en la EEPROM,la contraseña es incorrecta.
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" PASSWORD");
      lcd.setCursor(0, 1);
      lcd.print(" INCORRECTO");
      delay (retardo);
    }
  }
  
}
