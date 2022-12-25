#include <Keypad.h>
#include <Servo.h>
#define Password_size 6 // Give enough room for six chars + NULL char
#define ledRed    3
#define ledGreen  2
Servo myservo;

int pos = 0;    // variable to store the servo position
char Insert[Password_size]; // 6 is the number of chars it can hold + the null char = 7
char Unlocked[Password_size] = "24681";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {4,5,6,7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8,9,10,11}; //connect to the column pinouts of the keypad
bool door = true;
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
void setup()
{
  Serial.begin(9600);
  pinMode(ledRed,OUTPUT);
  pinMode(ledGreen, OUTPUT);
  myservo.attach(A1);
  ServoClose();
  
}
void loop()
{
  if (door == 0)
  {
    customKey = customKeypad.getKey();

    if (customKey == '#')

    {
      digitalWrite(ledGreen, LOW);
      Serial.println("Door is Close");
      ServoClose();
      delay(3000);
      door = 1;
    }
  }
 
  else 
   Open();
}

void clearData()
{
  while (data_count != 0)
  { 
    Insert[data_count--] = 0; 
  }
  return;
}

void ServoOpen()
{
  for (pos = 180; pos >= 0; pos -= 5) {
    myservo.write(pos);               
    delay(15);                       
  }
}

void ServoClose()
{
  for (pos = 0; pos <= 180; pos += 5) { 
    myservo.write(pos);              
    delay(15);                       
  }
  Serial.println("Enter Password");
}

void Open()
{
  customKey = customKeypad.getKey();
  if (customKey) 
  {
    Insert[data_count] = customKey; 
    
    Serial.print(Insert[data_count]); 
    data_count++; 
  }

  if (data_count == Password_size - 1) 
  {
    Serial.println();
    if (!strcmp(Insert, Unlocked)) 
    {
      
      ServoOpen();
      Serial.println("Door is Open");
      digitalWrite(ledGreen, HIGH);
      door = 0;
    }
    else
    {
      
      Serial.println("Wrong Password");
      digitalWrite(ledRed, HIGH);
      delay(1000);
      door = 1;
     
      digitalWrite(ledRed, LOW);
    }
    clearData();
  }
}
