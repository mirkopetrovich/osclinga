#include <Wire.h>
#include <ds3231.h>

unsigned char frame[8];
unsigned long previous = 0, previous2 = 0, previous_back = 0 ;
unsigned long previousMillis = 0, previousMillis2 = 0, previousMillis7 = 0, previousMillis8 = 0;
unsigned long pasado = 0;
int estorbo_on = 0, estorbo_on2 = 0, estorbo_on_back = 0;
int wait = 0, fin = 0, preset = 1, new_frec = 40;
int dia, militar;
struct ts t; 

//------------------------------------------------------------------------

void setup() {

  Wire.begin();
  Serial2.begin(115200, SERIAL_8N1, 16, 17); // Inicia UART2 Rx=16 Tx=17
  delay(10);

  // (pin, canal)
  ledcAttachPin(27, 1); // IZQUIERDA 
  ledcAttachPin(4, 2);  // ATRÁS
  ledcAttachPin(32, 3); // ADELANTE
  ledcAttachPin(25, 4); // DERECHA

  // (canal,frecuencia,resolución)
  ledcSetup(1, 1000, 8); 
  ledcSetup(2, 1000, 8);
  ledcSetup(3, 1000, 8);
  ledcSetup(4, 1000, 8);

  delay(500);
  STOP(frame,1);
  delay(10);
  STOP(frame,2);
  delay(10);
  RUN(frame,1);
  delay(10);
  RUN(frame,2);
}

//------------------------------------------------------------------------

void loop() {

unsigned long tiempo = millis()-pasado;
if (tiempo<420000) {                      
  preset1();                              
  estorbo(1,40,80,60);
  }

if ((tiempo>420000)&&(tiempo<440000)) {
  estorbo(0,20,30,30);
  preset2();
  }

if ((tiempo>440000)&&(tiempo<500000)) {
  delay((random(2000))+2000);
  preset3();
}

if ((tiempo>500000)&&(tiempo<520000)) {
  preset20();
}

if ((tiempo>520000)&&(tiempo<580000)) {
 delay((random(1000))+2000);
 preset4();
}

if ((tiempo>580000)&&(tiempo<590000)) {
  preset5();
  estorbo(1,40,80,60);
}

if ((tiempo>590000)&&(tiempo<710000)) {
  estorbo(0,20,30,30);
  preset6();
  estorbo2(1,70,60);
}

if ((tiempo>710000)&&(tiempo<720000)) {
  estorbo2(0,70,60);
  preset50();
  estorbo(1,40,80,60);
}

if ((tiempo>720000)&&(tiempo<780000)) {
  apaga();
  preset7();
  estorback(1,100,2500,100);
  estorbo(1,40,80,60);
}

if ((tiempo>780000)&&(tiempo<790000)) {
  estorback(0,100,2500,100);
  preset500();
  estorbo(1,40,80,60);
}

if ((tiempo>790000)&&(tiempo<820000)) {
  estorbackfin(1,100,3000,3000);
}

if (tiempo>820000)  {
  if (!wait) {
    estorbackfin(0,100,3000,3000);
    preset0();
    wait=1;
  }
}

if (wait) {
  DS3231_get(&t);
  militar = t.min+t.hour*100;
  dia = t.mon+t.mday*100;

  if ((dia==406)||(dia==1106)||(dia==1806)||(dia==2506)||(dia==207)||(dia==907)||(dia==1607))  {
    if ((militar==1440)||(militar==1540)||(militar==1640)) {
      reloz();
    } 
  }
  else {
    if ((militar==1140)||(militar==1440)||(militar==1540)) {
      reloz();
      }
    }  
  }
}

// ----------------------- FIN DEL LOOP ----------------------------------

void reloz() {

  preset = 1;
  fin = 0;
  pasado = millis();
  wait = 0;
}

//------------------------------------------------------------------------

void apaga() {

  if (!fin) {
  estorbo2(0,70,60);
  delay(1000);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
  ledcWrite(4,0);
  delay(3000);
  ledcWrite(1,100);
  ledcWrite(2,100);
  ledcWrite(3,100);
  ledcWrite(4,100);
  delay(80);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
  ledcWrite(4,0);
  delay(2000);
  fin = 1;
  }  
}

//------------------------------------------------------------------------

void preset0() {

  delay(10);
  STOP(frame,1);
  delay(10);
  STOP(frame,2);
  delay(10);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
  ledcWrite(4,0);
}

//------------------------------------------------------------------------

void preset1() {
  
  if (preset == 1) {
  RUN(frame,1);
  delay(10);
  FREC(frame,8,1);
  delay(10);
  RUN(frame,2);
  delay(10);
  FREC(frame,8,2);
  delay(10);
  preset= 2;
  }
}

//------------------------------------------------------------------------

void preset2() {

  if (preset == 2) {
  FREC(frame,1,1);
  delay(10);    //10
  FREC(frame,1,2);
  delay(7000);  //7010
  FREC(frame,30,2);
  delay(1000);
  ledcWrite(3, 100); 
  delay(50);
  ledcWrite(3, 0);   
  ledcWrite(4,100);
  delay(2000);
  ledcWrite(4,0);   
  FREC(frame,1,2);          
  delay(2940); 
  FREC(frame,30,1);
  delay(1000);
  ledcWrite(3, 100); 
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(1,100); 
  FREC(frame,1,1);
  delay(500);
  ledcWrite(1,0); 
  FREC(frame,33,2);
  delay(1000);
  ledcWrite(3, 100); 
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(4,100); 
  delay(2000);
  ledcWrite(4,0);    
  FREC(frame,1,2);         
  preset= 3;
  }
}

//------------------------------------------------------------------------

void preset20() {

  if (preset == 20) {
  FREC(frame,1,1);
  delay(10);    
  FREC(frame,1,2);
  delay(7000);  
  FREC(frame,30,1);
  delay(1000);
  ledcWrite(3, 100); 
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(1,100); 
  FREC(frame,1,1);
  delay(500);
  ledcWrite(1,0); 
  delay(2940); 
  FREC(frame,33,2);
  delay(1000);
  ledcWrite(3, 100); 
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(4,100); 
  delay(2000);
  ledcWrite(4,0);    
  FREC(frame,1,2);         
  delay(1000);
  FREC(frame,30,1);
  delay(1000);
  ledcWrite(3, 100); 
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(1,100); 
  FREC(frame,1,1);
  delay(500);
  ledcWrite(1,0); 
  preset= 4;
  }
}

//------------------------------------------------------------------------

void preset3 () {

int zap = random(2);
if (zap==0) {
  FREC(frame,(random(13)+15),1);
  delay(2500);
  FREC(frame,14,1);
 }
if (zap==1) {
  FREC(frame,(random(13)+11),2);
  delay(2500);
  FREC(frame,7,2);
  }
  preset=20;
}

//------------------------------------------------------------------------

void preset4 () {

int randomcito;
int zap = random(2);
if (zap==0) {
  randomcito = (random(14)+15);
  FREC(frame,randomcito,1);
  if (randomcito>=22) {
    ledcWrite(3, 100);
    delay(50);
    ledcWrite(3, 0);
    ledcWrite(1,100);
    delay(2000);
    FREC(frame,12,1);
    delay(500);
    ledcWrite(1,0);
    }
  }

if (zap==1) {
  randomcito = (random(13)+15);
  FREC(frame,randomcito,2);
  if (randomcito>=22) {
    ledcWrite(3, 100);
    delay(50);
    ledcWrite(3, 0);
    ledcWrite(4,100);
    delay(2000);
    FREC(frame,8,2);
    delay(500);
    ledcWrite(4,0);
    }
  }
}

//------------------------------------------------------------------------

void preset5() {
   
  delay(10);
  FREC(frame,10,1);
  delay(10);
  FREC(frame,10,2);
  delay(10);
  preset= 6;
}

//------------------------------------------------------------------------

void preset50() {
   
  delay(10);
  FREC(frame,10,1);
  delay(10);
  FREC(frame,10,2);
  delay(10);
  preset= 7; 
}

//------------------------------------------------------------------------

void preset500() {
   
  delay(10);
  FREC(frame,10,1);
  delay(10);
  FREC(frame,10,2);
  delay(10);
  preset= 8;
}

//------------------------------------------------------------------------

void preset6() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 5000) {
    previousMillis = currentMillis;
    FREC(frame,(random(17)+16),1);
  }

  if (currentMillis - previousMillis2 >= 6000) {
    previousMillis2 = currentMillis;
    FREC(frame,(random(30)+10),2);
  }
}

//------------------------------------------------------------------------

void preset7() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis7 >= 5000) {
    previousMillis7 = currentMillis;
    FREC(frame,(random(17)+16),1);
  }

  if (currentMillis - previousMillis8 >= 6000) {
    previousMillis8 = currentMillis;
    FREC(frame(random(30)+10),2);
  }
}

//------------------------------------------------------------------------

void estorback(int run, int pwm, int int1, int int2) {

  unsigned long currentMillis = millis();

  if (run) {
    if (estorbo_on_back == 0) {
      if (currentMillis - previous_back >= (int1+random(1000))) {
        previous_back = currentMillis;
        ledcWrite(2, pwm);
        estorbo_on_back = 1;
      }
    }
    else {
      if (currentMillis - previous_back >= int2) {
        previous_back = currentMillis;
        ledcWrite(2, 0);
        estorbo_on_back = 0;
      }
    }
  }
  else {
    ledcWrite(2, 0);
    estorbo_on_back = 0;
  }
} 

//------------------------------------------------------------------------

void estorbackfin(int run, int pwm, int int1, int int2) {

  unsigned long currentMillis = millis();

  if (run) {
    if (estorbo_on_back == 0) {
      if (currentMillis - previous_back >= (int1+random(1000))) {
        previous_back = currentMillis;
        FREC(frame,30,1);
        delay(1000);
        ledcWrite(2, pwm);
        estorbo_on_back = 1;
      }
    }
    else {
      if (currentMillis - previous_back >= int2) {
        previous_back = currentMillis;
        ledcWrite(2, 0);
        FREC(frame,1,1);
        estorbo_on_back = 0;
      }
    }
  }
  else {
    ledcWrite(2, 0);
    estorbo_on_back = 0;
  }
} 

//------------------------------------------------------------------------

void estorbo(int run, int pwm, int int1, int int2) {

  unsigned long currentMillis = millis();

  if (run) {
    if (estorbo_on == 0) {
      if (currentMillis - previous >= int1) {
        previous = currentMillis;
        ledcWrite(3, pwm);
        estorbo_on = 1;
      }
    }
    else {
      if (currentMillis - previous >= int2) {
        previous = currentMillis;
        ledcWrite(3, 0);
        estorbo_on = 0;
      }
    }
  }
  else {
    ledcWrite(3, 0);
    estorbo_on = 0;
  }
} 

//------------------------------------------------------------------------

void estorbo2(int run, int pwm, int int1) {

  unsigned long currentMillis = millis();

  if (run) {
    if (estorbo_on2 == 0) {
      if (currentMillis - previous2 >= int1) {
        previous2 = currentMillis;
        ledcWrite(1, pwm);
        ledcWrite(4, 0); 
        estorbo_on2 = 1;
      }
    }
    else {
      if (currentMillis - previous2 >= int1) {
        previous2 = currentMillis;
        ledcWrite(1, 0);
        ledcWrite(4, pwm);
        estorbo_on2 = 0;
      }
    }
  }
  else {
    ledcWrite(1, 0);
    ledcWrite(4, 0);
    estorbo_on2 = 0;
  }
} 

//------------------------------------------------------------------------

// Protocol                 : Modbus RTU
// Error check              : CRC
// Baud rate                : 9600bps, 19200bps, 38400bps, 57600bps, 115200bps(default)
// Data format              : 1 start bit, 8 data bits, 1 stop bits, no parity
// Physical signal          : RS 485 (2-wire)
// User interface           : RJ45
// Supported Function Codes : 03 Read Multiple Holding Registers 
//                            06 Write Single Holding Register
//                            16 Write Multiple Holding Registers (Supported for registers 1-4 only)

// P-36 Serial Communications Configuration
//      Index 1 : Address = 1 (0x01)
//      Index 2 : Baud Rate = 115.2kbps 

// Function Code.  : (0x06) 06

// Register Number : (0x00 0x00) 1 
// Parameter       : (0x00 0x00) Stop
//                 : (0x00 0x01) Run

// Register Number : (0x00 0x01) 2
// Parameter       : (0x00 0x00 - 0x13 0x88) Frequency x10 (0 - 500Hz)    

//------------------------------------------------------------------------

void STOP(unsigned char *frame, int address) {
    
  frame[0] = address;    // Address
  frame[1] = 0x06;       // Function Code
  frame[2] = 0x00;       // Register HIGH Byte
  frame[3] = 0x00;       // Register LOW Byte
  frame[4] = 0x00;       // Param HIGH Byte
  frame[5] = 0x00;       // Param LOW Byte
  CRC(frame);
  Serial2.write(frame,8);
}

void RUN(unsigned char *frame, int address) {
    
  frame[0] = address;    
  frame[1] = 0x06;      
  frame[2] = 0x00;       
  frame[3] = 0x00;
  frame[4] = 0x00;       
  frame[5] = 0x01;
  CRC(frame);
  Serial2.write(frame,8);
}

void FREC(unsigned char *frame, int address, float frecuencia) {
    
  int frec_int = frecuencia * 10.;
  if (frec_int < 0) frec_int += 0xFFFF + 1;
    
  frame[0] = address;    
  frame[1] = 0x06;      
  frame[2] = 0x00;       
  frame[3] = 0x01;
  frame[4] = (frec_int >> 8) & 0xFF;
  frame[5] = frec_int & 0xFF;
  CRC(frame);
  Serial2.write(frame,8);
}

void CRC(unsigned char *frame) {
    
  unsigned int temp, flag;
  temp = 0xFFFF;

  for (int i = 0; i < 6; i++) {
    temp ^=frame[i];
    for (int j = 1; j <= 8 ; j++) {
      flag = temp & 0x0001;
      temp >>= 1;
      if (flag) temp ^= 0xA001;
    }
  }
  frame[6] = temp & 0xFF;         // CRC LOW Byte
  frame[7] = (temp >> 8) & 0xFF;  // CRC HIGH Byte  
}

//------------------------------------------------------------------------

//TORPEDO

//paket[8] = { Address, Function Code, Register HIGH Byte, Register LOW Byte, Param HIGH Byte, Param LOW Byte, CRC LOW Byte, CRC HIGH Byte } 

//CRC-16/MODBUS  0x010600000000 -> 0xCA89
//               0x010600000001 -> 0x0A48

//uint8_t paket_STOP[8] = { 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x89, 0xCA };
//uint8_t paket_RUN[8]  = { 0x01, 0x06, 0x00, 0x00, 0x00, 0x01, 0x48, 0x0A };


//CRC-16/MODBUS   0x01060001015E -> 0x6258
//                0x010600010032 -> 0xDF59

//uint8_t paket_35Hz[8] = { 0x01, 0x06, 0x00, 0x01, 0x01, 0x5E, 0x58, 0x62 };
//uint8_t paket_5Hz[8] =  { 0x01, 0x06, 0x00, 0x01, 0x00, 0x32, 0x59, 0xDF };

//------------------------------------------------------------------------

