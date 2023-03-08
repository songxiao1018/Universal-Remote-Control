#include <IRremote.h>

// 按键 初始化
int button6 = 0;
int button7 = 0;
int button8 = 0;
int button9 = 0;
int button10 = 0;
int button11 = 0;
int button12 = 0;
int button13 = 0;

//红外 初始化
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

IRsend irsend;

void setup(void) {
  // 按键 初始化
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);  

  //红外 初始化
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop(void) {
  button6  = digitalRead(6);
  button7  = digitalRead(7);
  button8  = digitalRead(8);
  button9  = digitalRead(9);
  button10 = digitalRead(10);
  button11 = digitalRead(11);
  button12 = digitalRead(12);
  
  if (button6  == HIGH) {
    digitalWrite(13, HIGH);
    irsend.sendNEC(0xFF18E7, 32);
    delay(100);
  }else {
    digitalWrite(13, LOW);
  }

  if (button7  == HIGH) {
    digitalWrite(13, HIGH);
    irsend.sendNEC(0xFFA857, 32);
    delay(100);
  }else {
    digitalWrite(13, LOW);
  }

  if (button8  == HIGH) {
    digitalWrite(13, HIGH);
    irsend.sendNEC(0xFF30CF, 32);
    delay(100);
  }else {
    digitalWrite(13, LOW);
  }

  if (button9  == HIGH) {
    digitalWrite(13, HIGH);
    irsend.sendNEC(0xFFD02F, 32);
    delay(100);
  }else {
    digitalWrite(13, LOW);
  }

  if (button10 == HIGH) {
    digitalWrite(13, HIGH);
    irsend.sendNEC(0xFF728D, 32);
    delay(100);
  }else {
    digitalWrite(13, LOW);
  }

  if (button11 == HIGH) {
    digitalWrite(13, HIGH);
    irsend.sendNEC(0xFF926D, 32);
    delay(100);
  }else {
    digitalWrite(13, LOW);
  }

  if (button12 == HIGH) {
    digitalWrite(13, HIGH);
    irsend.sendNEC(0xFF02FD, 32);
    delay(100);
  }else {
    digitalWrite(13, LOW);
  }

  // if (button13 == HIGH) {irsend.sendNEC(0xFF926D, 32);delay(100);}

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}
