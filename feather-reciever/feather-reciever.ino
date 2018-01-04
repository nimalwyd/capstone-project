 //reciever

#include <SPI.h>
#include <RH_RF95.h>

// for feather m0
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
#define RF95_FREQ 915.0

RH_RF95 rf95(RFM95_CS, RFM95_INT);
#define LED 13                                    // Blink on receipt

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  while (!Serial);
  Serial.begin(9600);
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
  // Defaults after init are 868.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {

    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}


void loop()
{
  if (rf95.available())
  {
    static  int j =1;

    uint8_t buf[4];                              // Should be a message for us now
    uint8_t len = sizeof(buf);
    //uint8_t a[];
    //uint8_t len = sizeof(a);
    uint32_t temp = 0;
    uint32_t temp1 = 0;
    if (rf95.recv(buf, &len))
    {
     // Serial.print("Got a: ");
     // Serial.println(buf[0]);
      delay(100);
      temp = temp | buf[0];
      //Serial.print("Got b: ");
      //Serial.println(buf[1]);
      temp1 = buf[1];
      temp1 = temp1 << 8 ;
      temp = temp |temp1;

    }
    /*
        else if (rf95.recv(buf[1], &len)
      {
        Serial.print("Got b: ");
          Serial.println(buf[1]);
          buf[1] = buf[1] << 8 ;
          temp = temp | buf[1];
        }*/
    else
    {
      Serial.println("Receive failed");
    }
    Serial.println("value recieved");

     Serial.print("sensor ");
    Serial.print(j);
    Serial.println(" value : ");
   // Serial.println("data:");
  //  Serial.println(s);
    Serial.println(temp);
      j++;
    if(j==5){
    j=1;
    }

    
  }
}

