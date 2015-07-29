#define E1 6  // Enable Pin for motor 1
#define E2 10  // Enable Pin for motor 2
 
#define I1 8  // Control pin 1 for motor 1
#define I2 9  // Control pin 2 for motor 1
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2
 
void setup() {
    Serial.begin(115200); 

    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
 
    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);
}
 
void readSpeed(int speed[]) {
  int i = 0;
  int d = 0;
  char digits[4] = {0,0,0,0};

  while(true) {
    while(!Serial.available()) {}
    d = Serial.read();
    if(d == ':')
      break;
    if(!isdigit(d) && d != '-')
      return;

    if(i > 3) 
      break;
    digits[i] = d; 
    ++i;
  }

  speed[0] = atoi(digits);

  i = 0;
  d = 0;
  memset(digits,0,sizeof(digits));
  
  while(true) {
    while(!Serial.available()) {}
    d = Serial.read();
    Serial.println(d);
    if(d == '\n')
      break;

    if(!isdigit((char)d) && d != '-')
      return;
  
    if(i > 3) 
      break;
    digits[i] = (char)d;
    ++i;
  }

  speed[1] = atoi(digits);
}

void drive(int speed[]) {
    if(speed[1] < 0) {
      digitalWrite(I3, HIGH);
      digitalWrite(I4, LOW);
    } else if(speed[1] > 0) {
      digitalWrite(I3, LOW);
      digitalWrite(I4, HIGH);
    } else {
      digitalWrite(E2, LOW);
    }

    if(speed[0] < 0) {
      digitalWrite(I1, HIGH);
      digitalWrite(I2, LOW);
    } else if(speed[0] > 0) {
      digitalWrite(I1, LOW);
      digitalWrite(I2, HIGH);
    } else {
      digitalWrite(E1, LOW);
    }

    analogWrite(E1, abs(speed[0]) * 2);
    analogWrite(E2, abs(speed[1]) * 2);
}

int speed[2] = {0,0};

void loop() {
  readSpeed(speed);
  drive(speed);
}
