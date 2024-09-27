const int A1A = PA8;
const int A1B = PA9;
const int A1C = PB10;
const int A1D = PB11;
const int trig = PA6;     // trig pin of HC-SR04
const int echo = PA7;     // echo pin of HC-SR04

String turnRightMessage = "TURN RIGHT";  // variable to store the turn right message
String turnLeftMessage = "TURN LEFT";    // variable to store the turn left message
String currentMessage = turnRightMessage; // variable to store the current message
int rightMessageCount = 0;               // counter for "TURN RIGHT" messages
bool m = false;

void setup() {
  pinMode(PC13, OUTPUT);
  // put your setup code here, to run once:
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(A1C, OUTPUT);
  pinMode(A1D, OUTPUT);
    Serial.begin(9600);     // initialize Serial communication with baudrate 9600
    pinMode(trig, OUTPUT);  // set trig pin as OUTPUT
    pinMode(echo, INPUT);   // set echo pin as INPUT
}


bool checkmate()
{
  digitalWrite(13,LOW);
    unsigned long duration; // variable to store the duration of the pulse
    int distance;           // variable to store the distance

    // Send a pulse from the trig pin
    digitalWrite(trig, LOW);   // turn off the trig pin
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);  // send a pulse from the trig pin
    delayMicroseconds(10);     // pulse length is 10 microseconds
    digitalWrite(trig, LOW);   // turn off the trig pin

    // Calculate the duration
    duration = pulseIn(echo, HIGH);  // measure the duration of the pulse from the echo pin
    distance = int(duration / 2 / 29.412);  // calculate the distance in cm

    // Print the distance and the corresponding result
    Serial.print(distance);
    Serial.print(" cm - ");
    if (distance <= 14) {
        Serial.println("TRUE");
        m = true;
    } else {
        Serial.println("FALSE");
        m = false;
    }
    delay(100);  // wait for 500 milliseconds before the next measurement
    return m;
}

void M1_move()
{
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, HIGH);
}
void M2_move()
{
  digitalWrite(A1C, LOW);
  digitalWrite(A1D, HIGH);
}
void M1_back()
{
  digitalWrite(A1A, HIGH);
  digitalWrite(A1B, LOW);
}
void M2_back()
{
  digitalWrite(A1C, HIGH);
  digitalWrite(A1D, LOW);
}

void Stop()
{
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, LOW);
  digitalWrite(A1C, LOW);
  digitalWrite(A1D, LOW);
}

void loop() {
  if (checkmate()==false)
  {
  }
  else
  {
    M1_back();
    M2_back();
    delay(300);
    Serial.println("Turn left");
    M1_move();
    M2_back();
    delay(750);
    Stop();
    delay(100);
    if (!checkmate())
    {
      return;
    }
    //
    M1_back();
    M2_back();
    delay(600);
    Serial.println("Turn right");
    M2_move();
    M1_back();
    delay(1500);
    Stop();
    delay(100);
    if (checkmate())
    {
      return;
    }
    }
            Serial.println("MOVE");
            M1_move();
            M2_move();
            delay(100);
}
