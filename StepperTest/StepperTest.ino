#define DIST 10000
#define Z_DIST 25000
#define X_DIST 25000
#define STEP_DELAY 500

//Y Axis
int dirpin1 = 2;
int steppin1 = 3;
int dirpin2 = 4;
int steppin2 = 5;
int dirpin3 = 6;
int steppin3 = 7;
int dirpin4 = 8;
int steppin4 = 9;

//X Axis
int dirpin5 = 10;
int steppin5 = 11;

enum Z_test_enum {Z_NONE, Z_UP, Z_DOWN, Z_SWAY_UPDOWN, Z_SWAY_DOWNUP} Z_test_action;
enum X_test_enum {X_NONE, X_LEFT, X_RIGHT, X_SWAY_LEFTRIGHT, X_SWAY_RIGHTLEFT} X_test_action;

void setup()
{
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

  Z_test_action = Z_NONE;
  X_test_action = X_SWAY_RIGHTLEFT;

}

void loop()
{

  //Set Z direction based on Z_test_action
  switch (Z_test_action) {
    case Z_UP:
      digitalWrite(dirpin1, LOW);
      digitalWrite(dirpin2, LOW);
      digitalWrite(dirpin3, LOW);
      digitalWrite(dirpin4, LOW);
      break;
    case Z_DOWN:
      digitalWrite(dirpin1, HIGH);
      digitalWrite(dirpin2, HIGH);
      digitalWrite(dirpin3, HIGH);
      digitalWrite(dirpin4, HIGH);
      break;
    case Z_SWAY_UPDOWN:
      digitalWrite(dirpin1, LOW);
      digitalWrite(dirpin2, LOW);
      digitalWrite(dirpin3, LOW);
      digitalWrite(dirpin4, LOW);
      break;
    case Z_SWAY_DOWNUP:
      digitalWrite(dirpin1, HIGH);
      digitalWrite(dirpin2, HIGH);
      digitalWrite(dirpin3, HIGH);
      digitalWrite(dirpin4, HIGH);
      break;
    default:
      digitalWrite(dirpin1, HIGH);
      digitalWrite(dirpin2, HIGH);
      digitalWrite(dirpin3, HIGH);
      digitalWrite(dirpin4, HIGH);
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
    case X_SWAY_LEFTRIGHT:
      digitalWrite(dirpin5, HIGH);
      break;
    case X_SWAY_RIGHTLEFT:
      digitalWrite(dirpin5, LOW);
      break;
    default:
      digitalWrite(dirpin5, LOW);
      break;
  }

  delay(100);

  drive_steppers();

  //Set Z direction based on Z_test_action
  switch (Z_test_action) {
    case Z_UP:
      digitalWrite(dirpin1, LOW);
      digitalWrite(dirpin2, LOW);
      digitalWrite(dirpin3, LOW);
      digitalWrite(dirpin4, LOW);
      break;
    case Z_DOWN:
      digitalWrite(dirpin1, HIGH);
      digitalWrite(dirpin2, HIGH);
      digitalWrite(dirpin3, HIGH);
      digitalWrite(dirpin4, HIGH);
      break;
    case Z_SWAY_UPDOWN:
      digitalWrite(dirpin1, HIGH);
      digitalWrite(dirpin2, HIGH);
      digitalWrite(dirpin3, HIGH);
      digitalWrite(dirpin4, HIGH);
      break;
    case Z_SWAY_DOWNUP:
      digitalWrite(dirpin1, LOW);
      digitalWrite(dirpin2, LOW);
      digitalWrite(dirpin3, LOW);
      digitalWrite(dirpin4, LOW);
      break;
    default:
      digitalWrite(dirpin1, HIGH);
      digitalWrite(dirpin2, HIGH);
      digitalWrite(dirpin3, HIGH);
      digitalWrite(dirpin4, HIGH);
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
    case X_SWAY_LEFTRIGHT:
      digitalWrite(dirpin5, LOW);
      break;
    case X_SWAY_RIGHTLEFT:
      digitalWrite(dirpin5, HIGH);
      break;
    default:
      digitalWrite(dirpin5, LOW);
      break;
  }
  delay(100);

  drive_steppers();
}


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

