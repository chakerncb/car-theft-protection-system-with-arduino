# car-theft-protection-system-with-arduino 

***
## Used Libraies :

+ MFRC522.h
+ LiquidCrystal_I2C.h
+ Keypad.h
+ SPI.h

***
## Description :
   
   + This project is an Arduino-based security system that uses an RFID reader and a password mechanism to control access. The system features an LCD display for user interaction, a buzzer for audio feedback, and relays to control external devices.

## Features :

  + ***RFID Authentication***: Users can authenticate using RFID cards.

  + ***Password Protection***: A secondary layer of security with password input.

  + ***LCD Display***: Provides real-time feedback to the user.

  + ***Buzzer Alerts***: Audio feedback for successful or failed authentication.

  + ***Relay Control***: Manages external devices based on authentication status.

## Components :

  + ***LCD Display*** : Used to display messages to the user.

  + ***Buzzer***: Provides audio feedback.

  + ***Relays***: Control external devices.

  + ***RFID reader***: Reads RFID cards for authentication.

  + ***Keypad***: Input device for password entry.

  + ***Arduino Uno***: The main microcontroller.

## Circuit Diagram :
  
   + go to circuit diagram in the file `circuit.png`.

## How It Works :

  + ***RFID Mode***: The system starts in RFID mode, waiting for a card to be scanned.
  + ***Password Entry***: If the RFID card is recognized, the user is prompted to enter a password.
  + ***Authentication***: If the password is correct, the system activates the relays to allow access.
   If the password is incorrect, an error message is displayed, and the buzzer sounds.

## Applications :

  + ***Home Security***: Protect your home with a multi-layer security system.
  + ***Office Access Control***: Manage access to restricted areas.
  + ***Vehicle Security***: Secure your car with RFID and password protection.

## Setup :

  + ***Hardware***: Connect the components as shown in the circuit diagram.
  + ***Libraries***: Install the required libraries using the Arduino IDE.
  + ***Code***: Upload the code to the Arduino board using arduino ide.

## Usage :

  + ***RFID Card***: Scan an RFID card to start the authentication process.
  + ***Password Entry***: Enter the correct password to activate the relays.
  + ***Access Granted***: The system will provide access if the authentication is successful.
  + ***Access Denied***: An error message will be displayed if the authentication fails.

## Conclusion :
  
  + This project demonstrates how to create a security system using RFID and password authentication. By combining these two methods, the system provides a robust security solution for various applications.
