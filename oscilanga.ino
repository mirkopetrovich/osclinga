

int estorbo_on = 0;
int estorbo_on2 = 0;
int estorbo_on_back = 0;

int fin = 0;


int preset = 1;

int new_frec = 40;
unsigned long previous = 0;
unsigned long previous2 = 0;
unsigned long previous_back = 0;



unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;

unsigned long previousMillis7 = 0;
unsigned long previousMillis8 = 0;

unsigned long pasado = 0;



const uint8_t ADDRESS = 0x01;
const uint8_t ADDRESS2 = 0x02;
const uint8_t FUNCTION = 0x06;
unsigned char frame[8] = { ADDRESS, FUNCTION, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char frame2[8] = { ADDRESS2, FUNCTION, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


void setup() {

  Serial2.begin(115200, SERIAL_8N1, 16, 17); // Inicia UART2 Rx=16 Tx=17
  delay(10);
  ledcAttachPin(27, 1);
  ledcAttachPin(4, 2);
  ledcAttachPin(32, 3);
  ledcAttachPin(25, 4);
  ledcSetup(1, 1000, 8);
  ledcSetup(2, 1000, 8);
  ledcSetup(3, 1000, 8);
  ledcSetup(4, 1000, 8);
  delay(500);
  STOP();
  delay(10);
  STOP2();
  delay(10);
  RUN();
  delay(10);
  RUN2();
 

  
}

void loop() {

unsigned long tiempo = millis()-pasado;



//if (tiempo<180000) {   // 3 MIN

if (tiempo<10000) {   // 10 SEG

  preset1(); // RUN FREC(8) RUN2 FREC2(8)
  estorbo(1,40,80,60);
  }

  
//if ((tiempo>180000)&&(tiempo<190000)) {
if ((tiempo>10000)&&(tiempo<30000)) {

  estorbo(0,20,30,30);
  preset2();
  
  }

if ((tiempo>30000)&&(tiempo<90000)) {
  delay((random(2000))+2000);
  preset3();
}


if ((tiempo>90000)&&(tiempo<110000)) {

  preset20();
}




if ((tiempo>110000)&&(tiempo<170000)) {

  delay((random(1000))+2000);
  preset4();
}

if ((tiempo>170000)&&(tiempo<180000)) {
  preset5();
  estorbo(1,40,80,60);
}


if ((tiempo>180000)&&(tiempo<300000)) {

  estorbo(0,20,30,30);
  preset6();
  estorbo2(1,70,60);
}

if ((tiempo>300000)&&(tiempo<310000)) {

  
  estorbo2(0,70,60);
  preset50();
  estorbo(1,40,80,60);
 
  
}

if ((tiempo>310000)&&(tiempo<370000)) {

  apaga();
  preset7();
  estorback(1,100,2500,100);
  
}

if ((tiempo>370000)&&(tiempo<380000)) {

  
  estorback(0,100,2500,100);
  preset500();
  estorbo(1,40,80,60);
 
  
}

if ((tiempo>380000)&&(tiempo<410000)) {

  
  estorbackfin(1,100,2500,100);
  
  
 
  
}



if (tiempo>550000)  {
  
  preset0();
  delay(300000);
  preset = 1;
  fin = 0;
  pasado = millis();
}
/*
if ((tiempo>40000)&&(tiempo<600000)) {
  delay((random(5000))+1000);
  preset4();
  }

  if ((tiempo>60000)&&(tiempo<80000)) {
  delay((random(3000))+3000);
  preset5();
  }

  if ((tiempo>180000)&&(tiempo<240000)) {
  estorbo2(1, 40,40,40);
  preset6();
  } */


}

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

void preset0() {

  delay(10);
  STOP();
  delay(10);
  STOP2();
  delay(10);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
  ledcWrite(4,0);
 
}




void preset1() {
  
  if (preset == 1) {
  RUN();
  delay(10);
  FREC(8);
  delay(10);
  RUN2();
  delay(10);
  FREC2(8);
  delay(10);
  preset= 2;
  }
}

void preset2() {

  if (preset == 2) {
  FREC(1);
  delay(10);    //10
  FREC2(1);
  delay(7000);  //7010

  FREC2(30);
  delay(1000);
  ledcWrite(3, 100); //9010 luz front
  delay(50);
  ledcWrite(3, 0);   //9060 luz R
  ledcWrite(4,100);
  delay(2000);
  ledcWrite(4,0);    //9560 apaga luz R
  FREC2(1);          //11060 1Hz

  delay(2940); //14000
  
  FREC(30);
  delay(1000);
  ledcWrite(3, 100); //16000 luz front
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(1,100); //16050 luz L
  FREC(1);
  delay(500);
  ledcWrite(1,0); //16550 luz off

  //delay(450); // 17000
  FREC2(33);
  delay(1000);
  ledcWrite(3, 100); //19000 luz front
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(4,100); //19050 luz R
  
  delay(2000);
  ledcWrite(4,0);    //19550 luz off
  FREC2(1);         //21050 1Hz 




  
  preset= 3;
  }
}

void preset20() {

  if (preset == 20) {
  FREC(1);
  delay(10);    //10
  FREC2(1);
  delay(7000);  //7010

 

 
  
  FREC(30);
  delay(1000);
  ledcWrite(3, 100); //16000 luz front
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(1,100); //16050 luz L
  FREC(1);
  delay(500);
  ledcWrite(1,0); //16550 luz off

   delay(2940); //14000

  //delay(450); // 17000
  FREC2(33);
  delay(1000);
  ledcWrite(3, 100); //19000 luz front
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(4,100); //19050 luz R
  
  delay(2000);
  ledcWrite(4,0);    //19550 luz off
  FREC2(1);         //21050 1Hz 

  delay(1000);

  FREC(30);
  delay(1000);
  ledcWrite(3, 100); //16000 luz front
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(1,100); //16050 luz L
  FREC(1);
  delay(500);
  ledcWrite(1,0); //16550 luz off




  
  preset= 4;
  }
}

void preset3 () {

int zap = random(2);
if (zap==0) 
{
  FREC((random(13)+15));
  delay(2500);
  FREC(14);
 }

if (zap==1) {
  FREC2((random(13)+11));
  delay(2500);
  FREC2(7);
  
  }

  preset=20;
}

void preset4 () {

int randomcito;


int zap = random(2);
if (zap==0) 
{
  randomcito = (random(14)+15);
  FREC(randomcito);

  if (randomcito>=22) {
  
  ledcWrite(3, 100);
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(1,100);
  delay(2000);
   FREC(12);
  delay(500);
  ledcWrite(1,0);
 
 }

}

if (zap==1) {

  randomcito = (random(13)+15);
  FREC2(randomcito);

   if (randomcito>=22) {

  ledcWrite(3, 100);
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(4,100);
  delay(2000);
  FREC2(8);
  delay(500);
  ledcWrite(4,0);

   }
  
}


}

/*void preset5 () {

int zap = random(4);
if (zap==0) 
{
  FREC(30);
  delay(2000);
  ledcWrite(3, 100);
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(1,100);
  FREC(6);
  delay(500);
  ledcWrite(1,0);
  
 }

if (zap==1) {
  FREC(15);
  
  
}

if (zap==2) {
  FREC2(17);

}

if (zap==3) {
  FREC2(20);
  delay(2000);
  ledcWrite(3, 100);
  delay(50);
  ledcWrite(3, 0);
  ledcWrite(4,100);
  FREC2(6);
  delay(500);
  ledcWrite(4,0);
  }
} */

void preset5() {
   
  
  delay(10);
  FREC(10);
  delay(10);
  FREC2(10);
  delay(10);
  preset= 6;
  
}

void preset50() {
   
  
  delay(10);
  FREC(10);
  delay(10);
  FREC2(10);
  delay(10);
  preset= 7;
  
}

void preset500() {
   
  
  delay(10);
  FREC(10);
  delay(10);
  FREC2(10);
  delay(10);
  preset= 8;
  
}

void preset6() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 5000) {
    previousMillis = currentMillis;
    FREC((random(17)+16));
    }

   if (currentMillis - previousMillis2 >= 6000) {
    previousMillis2 = currentMillis;
    FREC2((random(30)+10));
   }
}

void preset7() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis7 >= 5000) {
    previousMillis7 = currentMillis;
    FREC((random(17)+16));
    }

   if (currentMillis - previousMillis8 >= 6000) {
    previousMillis8 = currentMillis;
    FREC2((random(30)+10));
   }
}


void estorback(int run, int pwm, int int1, int int2) {

  unsigned long currentMillis = millis();

  if (run)
  {
    if (estorbo_on_back == 0)
    {
      if (currentMillis - previous_back >= (int1+random(1000)))
      {
        previous_back = currentMillis;
        ledcWrite(2, pwm);
        estorbo_on_back = 1;
      }
    }
    else
    {
      if (currentMillis - previous_back >= int2)
      {
        previous_back = currentMillis;
        ledcWrite(2, 0);
        estorbo_on_back = 0;
      }
    }
  }
  else
  {
    ledcWrite(2, 0);
    estorbo_on_back = 0;
  }
} 

void estorbackfin(int run, int pwm, int int1, int int2) {

  unsigned long currentMillis = millis();

  if (run)
  {
    if (estorbo_on_back == 0)
    {
      if (currentMillis - previous_back >= (int1+random(1000)))
      {
        previous_back = currentMillis;
        FREC(30);
        ledcWrite(2, pwm);
        estorbo_on_back = 1;
      }
    }
    else
    {
      if (currentMillis - previous_back >= int2)
      {
        previous_back = currentMillis;
        FREC(1);
        ledcWrite(2, 0);
        estorbo_on_back = 0;
      }
    }
  }
  else
  {
    ledcWrite(2, 0);
    estorbo_on_back = 0;
  }
} 



void estorbo(int run, int pwm, int int1, int int2) {

  unsigned long currentMillis = millis();

  if (run)
  {
    if (estorbo_on == 0)
    {
      if (currentMillis - previous >= int1)
      {
        previous = currentMillis;
        ledcWrite(3, pwm);
        estorbo_on = 1;
      }
    }
    else
    {
      if (currentMillis - previous >= int2)
      {
        previous = currentMillis;
        ledcWrite(3, 0);
        estorbo_on = 0;
      }
    }
  }
  else
  {
    ledcWrite(3, 0);
    estorbo_on = 0;
  }
} 


void estorbo2(int run, int pwm, int int1) {

  unsigned long currentMillis = millis();

  if (run)
  {
    if (estorbo_on2 == 0)
    {
      if (currentMillis - previous2 >= int1)
      {
        previous2 = currentMillis;
        ledcWrite(1, pwm);
        ledcWrite(4, 0);

        
        estorbo_on2 = 1;
      }
    }
    else
    {
      if (currentMillis - previous2 >= int1)
      {
        previous2 = currentMillis;
        ledcWrite(1, 0);
        ledcWrite(4, pwm);
        estorbo_on2 = 0;
      }
    }
  }
  else
  {
    ledcWrite(1, 0);
    ledcWrite(4, 0);
    estorbo_on2 = 0;
  }
} 

void STOP() {
  frame[3] = 0x00;
  frame[4] = 0x00;
  frame[5] = 0x00;
  CRC();
  Serial2.write(frame, 8);
}

void RUN() {
  frame[3] = 0x00;
  frame[4] = 0x00;
  frame[5] = 0x01;
  CRC();
  Serial2.write(frame, 8);
}

void FREC(float frecuencia) {
  int frec_int = frecuencia * 10.;
  if (frec_int < 0) frec_int += 0xFFFF + 1;
  frame[3] = 0x01;
  frame[4] = (frec_int >> 8) & 0xFF;
  frame[5] = frec_int & 0xFF;
  CRC();
  Serial2.write(frame, 8);
}

void STOP2() {
  frame2[3] = 0x00;
  frame2[4] = 0x00;
  frame2[5] = 0x00;
  CRC2();
  Serial2.write(frame2, 8);
}

void RUN2() {
  frame2[3] = 0x00;
  frame2[4] = 0x00;
  frame2[5] = 0x01;
  CRC2();
  Serial2.write(frame2, 8);
}

void FREC2(float frecuencia) {
  int frec_int = frecuencia * 10.;
  if (frec_int < 0) frec_int += 0xFFFF + 1;
  frame2[3] = 0x01;
  frame2[4] = (frec_int >> 8) & 0xFF;
  frame2[5] = frec_int & 0xFF;
  CRC2();
  Serial2.write(frame2, 8);
}

void CRC()
{
  unsigned int temp, temp2, flag;
  temp = 0xFFFF;
  for (unsigned char i = 0; i < 6; i++)
  {
    temp = temp ^ frame[i];
    for (unsigned char j = 1; j <= 8 ; j++)
    {
      flag = temp & 0x0001;
      temp >>= 1;
      if (flag)
        temp ^= 0xA001;
    }
  }

  frame[6] = temp & 0xFF;
  frame[7] = (temp >> 8) & 0xFF;
}

void CRC2()
{
  unsigned int temp, temp2, flag;
  temp = 0xFFFF;
  for (unsigned char i = 0; i < 6; i++)
  {
    temp = temp ^ frame2[i];
    for (unsigned char j = 1; j <= 8 ; j++)
    {
      flag = temp & 0x0001;
      temp >>= 1;
      if (flag)
        temp ^= 0xA001;
    }
  }

  frame2[6] = temp & 0xFF;
  frame2[7] = (temp >> 8) & 0xFF;
}
