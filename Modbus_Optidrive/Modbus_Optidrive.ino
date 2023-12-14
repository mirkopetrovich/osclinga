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

// Function Code : 06 (0x06)

// Register Number : (0x00 0x00) 1 !!!!!
// Function        : (0x00 0x00) Stop
//                 : (0x00 0x01) Run

// Register Number : (0x00 0x01) 2
// Function        : (0x00 0x00 - 0x13 0x88) Frequency x10 (0 - 500Hz)      

            
//paket[8] = { Address, Function Code, Register HIGH Byte, Register LOW Byte, Param HIGH Byte, Param LOW Byte, CRC LOW Byte, CRC HIGH Byte } 

//CRC-16/MODBUS  0x010600000000 -> 0xCA89
//               0x010600000001 -> 0x0A48

uint8_t paket_STOP[8] = { 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x89, 0xCA };
uint8_t paket_RUN[8]  = { 0x01, 0x06, 0x00, 0x00, 0x00, 0x01, 0x48, 0x0A };


//CRC-16/MODBUS   0x01060001015E -> 0x6258
//                0x010600010032 -> 0xDF59

uint8_t paket_35Hz[8] = { 0x01, 0x06, 0x00, 0x01, 0x01, 0x5E, 0x58, 0x62 };
uint8_t paket_5Hz[8] =  { 0x01, 0x06, 0x00, 0x01, 0x00, 0x32, 0x59, 0xDF };


void setup() {
  Serial.begin(115200,SERIAL_8N1);
}

void loop() {
 Serial.write(paket_RUN,8);
 delay(3000);
 Serial.write(paket_35Hz,8);
 delay(10000);
  Serial.write(paket_5Hz,8);
 delay(10000);
 Serial.write(paket_STOP,8);
 delay(3000);
}

void RUN() {
  int i;
  for (i=0; i<8; i++) Serial.write(paket_RUN[i]);
}

void STOP() {
  int i;
  for (i=0; i<8; i++) Serial.write(paket_STOP[i]);
}
