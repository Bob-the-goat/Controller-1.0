
const int Button1 = 1;
const int Button2 = 2;
const int Button3 = 3;

const int LED1 = 4;
const int LED2 = 5;
const int LED3 = 6;
const int LED4 = 7;


unsigned long moleStartTime = 0;     
const unsigned long moleDuration = 500; 

unsigned long hitStartTime = 0;        
const unsigned long hitDuration = 1000; 

int currentMole = -1;   
bool moleActive = false;
bool hitActive = false;

void setup() {
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  randomSeed(analogRead(0)); 
}

void loop() {
  unsigned long currentTime = millis();


  if (!moleActive) {
    currentMole = random(0, 3); // 0 or 1 or 2
    moleActive = true;
    moleStartTime = currentTime;

    if (currentMole == 0) digitalWrite(LED1, HIGH);
    else if (currentMole == 1) digitalWrite(LED2, HIGH);
    else if (currentMole == 2) digitalWrite(LED3, HIGH);
  }


  int button1State = digitalRead(Button1);
  int button2State = digitalRead(Button2);
  int button3State = digitalRead(Button3);

  if (moleActive && !hitActive) {
    if ((currentMole == 0 && button3State == LOW) || 
        (currentMole == 1 && button1State == LOW) ||
        (currentMole == 2 && button2State == LOW)) {
      digitalWrite(LED4, HIGH); // hit led lights
      hitStartTime = currentTime;
      hitActive = true;
    }
  }

  if (moleActive && currentTime - moleStartTime >= moleDuration) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    moleActive = false;
  }


  if (hitActive && currentTime - hitStartTime >= hitDuration) {
    digitalWrite(LED4, LOW);
    hitActive = false;
  }
}
