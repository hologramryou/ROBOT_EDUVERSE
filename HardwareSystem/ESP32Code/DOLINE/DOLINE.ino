const int trig = 13;     // trig pin of HC-SR04
const int echo = 12;     // echo pin of HC-SR04
#define IN1 27
#define IN2 26
#define IN3 33
#define IN4 25
#define MAX_SPEED 255
#define MIN_SPEED 0
String turnRightMessage = "TURN RIGHT";  // variable to store the turn right message
String turnLeftMessage = "TURN LEFT";    // variable to store the turn left message
String currentMessage = turnRightMessage; // variable to store the current message
int rightMessageCount = 0;               // counter for "TURN RIGHT" messages
bool m = false;

void setup()
{
    Serial.begin(9600);     // initialize Serial communication with baudrate 9600
    pinMode(trig, OUTPUT);  // set trig pin as OUTPUT
    pinMode(echo, INPUT);   // set echo pin as INPUT
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

bool checkmate()
{
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
    if (distance <= 20) {
        Serial.println("TRUE");
        m = true;
    } else {
        Serial.println("FALSE");
        m = false;
    }
    delay(100);  // wait for 500 milliseconds before the next measurement
    return m;
}

void motor_1_stop() 
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}

void motor_2_stop() 
{
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void motor_1_move() 
{
    digitalWrite(IN1, HIGH); // this pin does not have PWM
    digitalWrite(IN2, LOW);
}

void motor_1_back() 
{
    digitalWrite(IN1, LOW); // this pin does not have PWM
    digitalWrite(IN2, HIGH);
}

void motor_2_move() 
{
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW); // this pin does not have PWM
}

void motor_2_back() 
{
    digitalWrite(IN4, HIGH);
    digitalWrite(IN3, LOW); // this pin does not have PWM
}

void loop()
{
    int n = 2;
    while (true)
    {
        if (checkmate())
        {
                motor_1_back();
                motor_2_back();
                delay(100);
            bool breaking = false;
            for (int i = 0; i < n; i++)
            {
                Serial.println("Turn left");
                motor_1_move();
                motor_2_back();
                delay(200);
                motor_1_stop();
                motor_2_stop();
                delay(100);
                if (!checkmate())
                {
                    breaking = true;
                    break;
                }
            }
            if (breaking) break;

            for (int i = 0; i < n; i++)
            {
                Serial.println("Turn right");
                motor_2_move();
                motor_1_back();
                delay(400);
                motor_1_stop();
                motor_2_stop();
                delay(100);
                if (!checkmate())
                {
                    breaking = true;
                    break;
                }
            }
            n += 1;
        }
        else
        {
            Serial.println("MOVE");
            motor_1_move();
            motor_2_move();
        }
    }
}
