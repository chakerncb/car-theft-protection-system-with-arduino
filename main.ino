//////////////INTRUDECTION////////////////////
//*-car theft protection system.            //
//*-writed by chaker necibi.                //
//*-using Arduino ide 1.8.13 .              //
//*-using:(keyped-+LiquidCrystal+-MFRC522.  //
//*-Tested on 15 feb 2022.                  //
//////////////////////////////////////////////

///// Include required libraries//////////
#include <MFRC522.h>                    //
#include <LiquidCrystal_I2C.h>          //  
#include <Keypad.h>                     //                      
#include <SPI.h>                        //
//////////////////////////////////////////
// Create instances///////////////////////////////////////////////////////////////////////////////
LiquidCrystal_I2C lcd(0x27, 16, 2);                                                             //
MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)                                     //
// Initialize Pins for led's, servo and buzzer                                                  //
// Blue LED is connected to 5V                                                                  //
constexpr uint8_t relay1 = 7;//for open and close the dore.                                                                  //
constexpr uint8_t relay2 = 6;//for turn on\off the car.
constexpr uint8_t relay3 = 5;//wen the car is in danger.
constexpr uint8_t buzzer = 4;//buzzer for the danger.
char initial_password[4] = {'9', '2', '7', '3'};  // Variable to store initial password
String tagUID = "89 5E 33 E8";  // String to store UID of tag. Change it with your tag's UID
char password[4];   // Variable to store users password
boolean RFIDMode = true; // boolean to change modes
char key_pressed = 0; // Variable to store incoming keys
uint8_t i = 0;  // Variable used for counter
int error = 0;
// defining how many rows and columns our keypad have
const byte rows = 4;
const byte columns = 4;

///////////////////////////// Keypad pin map////////////////////////////////////////////////////
char hexaKeys[rows][columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Initializing pins for keypad
byte row_pins[rows] = {A0, A1, A2, A3};
byte column_pins[columns] = {2, 1, 0};

/////////////////////// Create instance for keypad////////////////////////////////////////////////
Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);

void setup() {
  // Arduino Pin configuration
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin();   // LCD screen
  //  lcd.backlight();
  lcd.clear(); // Clear LCD screen
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  //////////////////////////////////////////////////////////////////////////////////////////////
}

void loop() {
  /////////////////////////System will first look for mode/////////////////////////////////////
  if (RFIDMode == true) {
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }
////////////////////////////////////////Checking the card////////////////////////////////////////////////
    //Reading from the card
    String tag = "";
    for (byte j = 0; j < mfrc522.uid.size; j++)
    {
      tag.concat(String(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " "));
      tag.concat(String(mfrc522.uid.uidByte[j], HEX));
    }
    tag.toUpperCase();
    ////////////////////////////////////////if tag is matched////////////////////////////////////////////////
    if (tag.substring(1) == tagUID)
    {
      lcd.begin();   // LCD screen
      lcd.backlight();
      digitalWrite(relay1, HIGH);
      // If UID of tag is matched.
      lcd.clear();
      tone (buzzer, 500);
      delay (300);
      noTone(buzzer);
      ////////////////////////////////////////////////PASSWORD////////////////////////////////////////////////
      lcd.clear();
      lcd.print("Enter Password:");
      lcd.setCursor(0, 1);
      RFIDMode = false; // Make RFID mode false
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    else
    {
      /////////////////////////////// If  is not matched.////////////////////////////////////
    }
  }
  tone(buzzer, 300);
  delay(600);
  noTone(buzzer);
  digitalWrite(relay3, HIGH);
  //**+++++//   digitalWrite(relay3, LOW);
  lcd.clear();


  ////////////////////////////////////////////////////////////////////////////////////////////////
  // If RFID mode is false, it will look for keys from keypad
  if (RFIDMode == false) {
    key_pressed = keypad_key.getKey(); // Storing keys
    if (key_pressed)
    {
      password[i++] = key_pressed; // Storing in password variable
      lcd.print("*");
    }
    if (i == 4) // If 4 keys are completed
    {
      delay(200);
      if (!(strncmp(password, initial_password, 4))) // If password is matched
      {
        ////////////////////////////////////IF PASSWORD TRUE//////////////////////////////////////////
        tone(buzzer, 500);
        delay(300);
        noTone(buzzer);
        lcd.clear();
        lcd.print(" hello mr.chaker ");
        lcd.begin();   // LCD screen
        lcd.backlight();
        lcd.print(" YOU CAN TURN ");
        lcd.setCursor(0, 1);
        lcd.print("      ON THE CAR ");
        digitalWrite(relay2, HIGH);
        delay(3000);
        lcd.clear();
        lcd.print(" MR.CHAKER is ");
        lcd.setCursor(0, 1);
        lcd.print("      in THE CAR ");
        i = 0;
        RFIDMode = true; // Make RFID mode true
      }
      /////////////////////////////////////////IF PASSWOD FALSE////////////////////////////////////////
      else
      {

        lcd.clear();
        lcd.print("Wrong Password");
        tone(buzzer, 300);
        delay(3000);
        noTone(buzzer);
        digitalWrite(relay3, HIGH);
        digitalWrite(relay1, LOW);
        lcd.clear();
        RFIDMode = true;  // Make RFID mode true

      }
    }
  }
}
