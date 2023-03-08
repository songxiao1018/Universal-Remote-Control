#include "U8glib.h"
#include <IRremote.h>

U8GLIB_SSD1309_128X64 u8g(8, 9, 12, 11, 10);    // SPI Com: SCK/SCL = 13, MOSI/SDA = 11, CS = 10, A0/D\C = 9, RST=2

// OLED 初始化
void draw4on (void) {u8g.drawStr( 0, 45, "Pin4 ON  3 UP");}
void draw4off(void) {u8g.drawStr( 0, 45, "Pin4 OFF 3 UP");}
void draw5on (void) {u8g.drawStr( 0, 30, "Pin5 ON  2 DOWN");}
void draw5off(void) {u8g.drawStr( 0, 30, "Pin5 OFF 2 DOWN");}
void draw6on (void) {u8g.drawStr( 0, 15, "Pin6 ON  1 OK");}
void draw6off(void) {u8g.drawStr( 0, 15, "Pin6 OFF 1 OK");}

// 按键 初始化
int button4 = 0;
int button5 = 0;
int button6 = 0;

//红外 初始化
int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

IRsend irsend;

void setup(void) {
  // OLED 初始化
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);

  // 按键 初始化
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);  

  //红外 初始化
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop(void) {
  button4 = digitalRead(4);
  button5 = digitalRead(5);
  button6 = digitalRead(6);
  
  u8g.firstPage();
  do {
    if (button4 == HIGH) {
      draw4on();
    } else {
      draw4off();
    }

    if (button5 == HIGH) {
      draw5on();
    } else {
      draw5off();
    }

    if (button6 == HIGH) {
      draw6on();
    } else {
      draw6off();
    }
  } while( u8g.nextPage() );

  if (button4 == HIGH) {
    irsend.sendNEC(0xFFE21D, 32);
    delay(100);
  }

  if (button5 == HIGH) {
    irsend.sendNEC(0xFFD22D, 32);
    delay(100);
  }

  if (button6 == HIGH) {
    irsend.sendNEC(0xFF926D, 32);
    delay(500);
  }

  
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}

    // u8g.firstPage();
    // do {
    //   draw7off();
    // } while( u8g.nextPage() );
