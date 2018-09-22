int DIST;
#define STEP_DELAY 500

//Y Axis
int dirpin1 = 4;
int steppin1 = 5;
int dirpin2 = 6;
int steppin2 = 7;
int dirpin3 = 8;
int steppin3 = 9;
int dirpin4 = 10;
int steppin4 = 11;

//X Axis
int dirpin5 = 12;
int steppin5 = 13;

enum Z_test_enum {Z_NONE, Z_UP, Z_DOWN} Z_test_action;
enum X_test_enum {X_NONE, X_LEFT, X_RIGHT} X_test_action;


String incomingCommand;

void drive_steppers() {

  for (int i = 0; i < DIST; i++)     // Iterate for DIST microsteps.
  {
    if (Z_test_action != Z_NONE) {
      digitalWrite(steppin1, LOW);  // This LOW to HIGH change is what creates the
      digitalWrite(steppin2, LOW); // "Rising Edge" so the easydriver knows to when to step.
      digitalWrite(steppin3, LOW);
      digitalWrite(steppin4, LOW);
    }
    if (X_test_action != X_NONE) {
      digitalWrite(steppin5, LOW);
    }

    if (Z_test_action != Z_NONE) {
      digitalWrite(steppin1, HIGH);
      digitalWrite(steppin2, HIGH);
      digitalWrite(steppin3, HIGH);
      digitalWrite(steppin4, HIGH);
    }
    if (X_test_action != X_NONE) {
      digitalWrite(steppin5, HIGH);
    }

    delayMicroseconds(STEP_DELAY);      // 500 delay time is close to top speed for this
  }                              // particular motor. Any faster the motor stalls.

}

void setup()
{
  Serial.begin(9600);
  pinMode(dirpin1, OUTPUT);
  pinMode(steppin1, OUTPUT);
  pinMode(dirpin2, OUTPUT);
  pinMode(steppin2, OUTPUT);
  pinMode(dirpin3, OUTPUT);
  pinMode(steppin3, OUTPUT);
  pinMode(dirpin4, OUTPUT);
  pinMode(steppin4, OUTPUT);
  pinMode(dirpin5, OUTPUT);
  pinMode(steppin5, OUTPUT);

}

void loop()
{

  Z_test_action = Z_NONE;
  X_test_action = X_NONE;
  
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingCommand = Serial.readString();

    if (incomingCommand == "down")
    {
      Serial.println("Down");
      DIST = 10000;
      Z_test_action = Z_DOWN;
      
    }

    if (incomingCommand == "up")
    {
      Serial.println("Up");
      DIST = 10000;
      Z_test_action = Z_UP;
      
    }

    if (incomingCommand == "left")
    {
      Serial.println("Left");
      DIST = 2500;
      X_test_action = X_LEFT;
      
    }

    if (incomingCommand == "right")
    {
      Serial.println("Right");
      DIST = 2500;
      X_test_action = X_RIGHT;
      
    }
  
  //Set Z direction based on Z_test_action
  switch (Z_test_action) {
    case Z_UP:
      digitalWrite(dirpin1, HIGH);
      digitalWrite(dirpin2, HIGH);
      digitalWrite(dirpin3, HIGH);
      digitalWrite(dirpin4, HIGH);
      break;
    case Z_DOWN:
      digitalWrite(dirpin1, LOW);
      digitalWrite(dirpin2, LOW);
      digitalWrite(dirpin3, LOW);
      digitalWrite(dirpin4, LOW);
      break;
    default:
      digitalWrite(dirpin1, LOW);
      digitalWrite(dirpin2, LOW);
      digitalWrite(dirpin3, LOW);
      digitalWrite(dirpin4, LOW);
      break;
  }

  //Set X direction based on X_test_action
  switch (X_test_action) {
    case X_LEFT:
      digitalWrite(dirpin5, HIGH);
      break;
    case X_RIGHT:
      digitalWrite(dirpin5, LOW);
      break;
    default:
      digitalWrite(dirpin5, LOW);
      break;
  }

  delay(100);
  
  drive_steppers();
  }
}

