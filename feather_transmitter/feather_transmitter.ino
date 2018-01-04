#include <SPI.h>
#include <RH_RF95.h>

//SoftwareSerial mySerial(8, 7); // RX, TX
#define LED 13                            // Blink on receipt

////RFM95 RADIO
//#define RFM95_CS 10
//#define RFM95_RST 9
//#define RFM95_INT 2


// for feather m0
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
#define RF95_FREQ 915.0

RH_RF95 rf95(RFM95_CS, RFM95_INT);


int incomingByte = 0;   // for incoming serial data

void setup() {

  while (!Serial) {
    Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
   Serial1.begin(9600); // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(LED, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(100);
  Serial.println("Feather LoRa RX Test!");
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
  // Defaults after init are 915.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {

    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: ");
  Serial.println(RF95_FREQ);
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}


void loop() {
static  int j =1;
static int k =1;
  String i;
  if (Serial1.available()) {

    i = Serial1.readString();
   // delay(100);
    Serial.println("got");
    Serial.println(i);

    const char *a = i.c_str();
    uint8_t s = atoi(a);
    //delay(100);
 
   
    Serial.print("sensor");
     Serial.print(k);
     Serial.print(" ");
    //Serial.print(j);
    Serial.println(" value : ");
   // Serial.println("data:");
    Serial.println(s);
       k++;
    if(k==5)
    {

      k=1;
    }
  
    char dataToSend[10];
    sprintf(dataToSend, "value %d", s);
    Serial.println(dataToSend);
  
        rf95.send((uint8_t*)dataToSend, 10);
        delay(10);
       /* rf95.waitPacketSent();
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);
        delay(10);
        if (rf95.waitAvailableTimeout(1000))
        {
          // Should be a reply message for us now
          if (rf95.recv(buf, &len))
          {
            Serial.print("Got reply: ");
            Serial.println((char*)buf);
          }

          else
          {
            Serial.println("recieve failed");
          }
        }
        else
        {
          Serial.println("No reply, is there a listener around?");
        }
        delay(1000);
 
 */
  }
}

