#define DEBUG //uncomment for debug
#define BLYNK_PRINT Serial    // Comment this out to disable printsand save space
#define BLYNK_DEBUG

#include <IRremoteESP8266.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClientSecure.h>
#include <ESP8266TelegramBOT.h>
#include <SimpleTimer.h>

//#define PanasonicAddress      0x4004     // Panasonic address (Pre data) 
//#define PanasonicPower        0x100BCBD  // Panasonic Power button
//#define JVCPower              0xC5E8
#define BOTtoken "165672905:AAFhk3XgHITZGDA_M2XEoxAhFaOdxl1Wf6Q"
#define BOTname "Neato"
#define BOTusername "neatobot"
#define SERBAUD 9600

char auth[]  = "b92e451545454a85b3602e7f432aeb66";
//char auth1[] = "dac663bea5ae4b26b165d8d2d02e5969"; //Auth Tokens for any additional projects

const char* ssid = "Xiaomi2G";          //your wifi ssid
const char* password = "panatorium";  //your wifi password

IRsend irsend(5); //an IR led is connected to GPIO pin 0
TelegramBOT bot(BOTtoken, BOTname, BOTusername);
SimpleTimer timer;

unsigned int t_16 [230]={3250,2800,3250,4150,800,1400,800,350,750,1450,750,300,800,350,750,1400,800,1400,750,350,800,300,800,350,750,350,750,350,750,350,750,350,750,1450,750,350,750,350,800,300,800,300,800,300,750,350,800,1400,800,300,800,1400,750,350,750,350,700,450,650,450,650,450,650,450,650,450,650,450,650,500,600,1600,550,550,550,550,550,550,550,550,550,1650,550,1600,600,1600,600,500,600,1600,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,600,500,600,500,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,1600,600,1600,600,500,600,1600,550,1650,550,550,550,550,550,550,550,1650,550};
unsigned int t_17 [230]={3200,2850,3200,4200,750,1450,750,350,750,1450,650,450,700,400,700,1500,650,1550,650,450,650,500,600,500,600,500,600,1600,550,550,550,550,550,1650,550,550,550,550,550,550,600,500,600,500,550,600,500,1700,500,550,550,1650,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,1650,550,1650,550,1650,550,550,550,1650,550,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,1600,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,600,500,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,500,600,500,600,1600,600,1600,600,500,600,550,550,550,550,550,550,550,550,550,550};
unsigned int t_18 [230]={3200,2850,3150,4300,650,1500,650,500,600,1550,650,450,650,500,600,1600,600,1600,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,600,500,600,500,600,550,550,1650,550,550,550,1600,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,600,500,600,500,550,1650,550,1650,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,500,600,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,1650,550,1600,600,500,600,1600,600,550,550,550,550,550,550,550,550};
unsigned int t_19 [230]={3250,2800,3150,4300,650,1550,600,500,600,1600,600,500,600,500,600,1600,600,1600,550,550,550,550,550,550,550,1650,550,1650,550,550,550,550,600,1600,550,550,600,500,550,600,550,550,550,550,550,550,550,1600,600,500,600,1600,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,1600,550,550,550,550,550,550,600,500,600,1600,550,1650,550,1650,550,550,550,1600,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,600,500,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,500,600,500,600,550,550,550,550,550,550,1650,550,1650,550,1650,550,550,550,550,550,550,550,550,550,550,550};
unsigned int t_20 [230]={3250,2800,3150,4250,700,1500,650,450,650,1550,650,500,600,500,550,1650,550,1600,600,550,550,550,550,1650,550,550,550,550,550,550,550,550,600,1600,550,550,550,550,550,550,550,600,500,550,600,500,600,1600,600,500,600,1600,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,600,1600,550,1650,550,1600,600,500,600,1600,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,500,600,500,600,500,600,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,550,550,550,600,500,600,500,600,500,600,550,550,1650,550,1650,550,1650,550,1600,550,550,600,500,600,500,600,500,600};
unsigned int t_21 [230]={3200,2850,3150,4250,700,1500,650,450,650,1550,650,500,600,500,550,1650,550,1600,600,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,1600,600,550,550,550,550,550,550,550,550,550,550,550,600,1600,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,1650,550,550,550,550,550,550,550,550,550,1600,600,1600,600,1600,550,550,600,1600,600,500,600,500,600,550,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,1650,550,550,550,550,550,550,550,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,500,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550};
unsigned int t_22 [230]={3200,2850,3100,4300,650,1550,650,500,600,1600,550,550,550,550,550,1650,550,1600,600,550,550,550,550,1650,550,1650,500,600,550,550,550,550,550,1600,600,550,550,550,550,550,550,550,550,550,550,550,600,1600,600,500,550,1650,550,550,550,550,550,550,600,500,550,550,550,550,600,500,600,500,600,550,550,1650,550,550,550,550,550,550,550,550,550,1650,550,1600,600,1600,600,500,600,1600,600,500,600,500,600,550,550,550,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,1600,600,550,550,550,550,550,550,550,550};
unsigned int t_23 [230]={3200,2850,3100,4350,600,1600,600,500,600,1600,600,500,550,550,550,1650,550,1650,550,550,550,550,550,1650,550,1650,550,1650,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,600,500,550,600,500,550,550,550,600,500,600,1600,600,500,600,550,550,550,550,550,550,1650,550,1600,550,1650,550,550,550,1650,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,550,550,600,500,600,1600,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,600,500,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,600,500,600,550,550,550,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,600,500,600,550,550,1650,550,550,550,550,550,550,550,550,550,550,550};
unsigned int t_24 [230]={3200,2850,3100,4350,600,1600,600,500,600,1600,550,550,550,550,550,1650,550,1600,600,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,600,500,550,600,500,600,1600,600,500,600,1600,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,600,1600,550,1650,550,1600,600,500,600,1600,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,500,600,550,500,600,500,600,500,600,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,1650,550,1650,550,550,550,550,550,550,550,550,550};
unsigned int t_25 [230]={3250,2850,3100,4300,650,1550,650,450,650,1550,600,500,600,550,550,1650,550,1600,600,550,550,1650,500,600,550,550,550,1650,550,500,600,550,550,1600,600,550,550,550,550,550,550,550,550,550,550,550,600,1600,550,550,550,1600,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,1650,500,600,550,550,550,550,550,550,550,1600,600,1600,600,1600,550,550,600,1600,600,500,600,500,600,550,550,500,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,1650,550,500,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,500,600,550,1600,550,550,600,500,600,500,600,550,550,550,550,550,550};
unsigned int t_26 [230]={3250,2800,3150,4300,600,1600,600,500,600,1600,600,500,600,500,600,1600,600,1600,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,600,1600,550,550,600,500,600,550,500,600,550,550,550,550,550,1600,600,500,600,1600,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,600,500,550,550,550,550,600,500,600,1600,550,1650,550,1650,550,550,550,1600,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,600,500,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,600,500,600,550,500,600,500,600,550,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,600,500,600,500,600};
unsigned int t_27 [230]={3200,2850,3100,4350,600,1600,600,500,600,1600,550,550,550,550,550,1650,550,1650,550,550,550,1650,550,550,550,1650,550,1650,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,600,500,600,550,550,550,500,550,600,500,600,1600,600,500,600,550,550,550,550,550,550,1650,550,1600,600,1600,550,550,550,1650,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,1600,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,600,500,550,550,600,500,600,1600,600,1600,600,550,500,600,550,550,550,500,600,500,600};
unsigned int t_28 [230]={3200,2850,3100,4350,600,1600,600,500,550,1650,550,550,550,550,550,1650,550,1650,550,550,550,1650,550,1650,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,600,500,600,500,600,1600,600,500,550,1650,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,1650,550,550,550,550,550,550,550,550,600,1600,550,1600,600,1600,600,550,550,1600,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,600,550,550,550,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,1600,600,1600,600,1600,600,500,600,550,550,550,550,550,550};
unsigned int t_29 [230]={3250,2800,3150,4300,650,1550,650,450,600,1600,600,500,600,500,600,1600,600,1600,550,550,600,1600,600,1600,600,500,600,1600,550,550,550,550,550,1650,550,550,550,550,600,500,600,500,600,550,550,550,550,1650,550,550,550,1600,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,600,500,550,550,550,550,550,1650,550,1650,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,600,500,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600};
unsigned int t_30 [230]={3200,2850,3100,4350,650,1550,600,500,600,1600,600,500,550,550,550,1650,550,1650,550,550,550,1650,550,1650,550,1600,600,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,600,500,550,600,500,1650,550,550,550,1650,550,550,550,550,550,550,600,500,600,500,600,550,500,600,500,600,550,550,550,1600,600,500,600,550,550,550,550,550,550,1650,550,1600,550,1650,550,600,500,1650,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,600,500,550,600,500,600,1600,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,500,600,550,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,600,500,600,500,600,1600,600,500,600,550,550,1650,550,550,550,550,550,550,550,550,550};
unsigned int fan_1 [230]={3350,2700,3300,4100,850,1350,850,250,850,1350,850,250,850,300,850,1300,850,1350,850,250,850,250,800,1400,750,1450,750,1450,750,350,750,350,850,1350,750,350,800,300,800,350,700,350,800,350,750,350,750,1400,800,350,750,1400,750,400,650,450,650,450,650,450,650,450,650,500,600,500,600,500,600,500,600,1600,550,550,550,550,550,550,600,1600,600,1600,550,550,600,500,550,1650,550,1650,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,600,550,500,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,1650,550,1650,550,1650,550,550,550,550,550,1650,550,1600,600,1600,550};
unsigned int fan_2 [230]={3250,2800,3150,4300,650,1550,650,450,600,1600,600,500,600,500,600,1600,600,1600,550,550,600,500,600,1600,550,1650,550,1650,550,550,550,550,550,1650,550,550,550,550,600,500,600,500,600,550,550,550,550,1650,550,550,550,1600,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,600,500,550,550,550,1650,550,1650,550,550,550,550,550,1650,550,550,600,500,600,500,600,550,550,550,500,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,1600,600,550,550,550,550,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,500,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,600,1600,550,550,550,550,550,1650,550,1650,550,550,550,550,550,550,550,1650,550,1650,550,1650,550};
unsigned int fan_3 [230]={3250,2800,3150,4300,650,1550,650,450,650,1550,600,500,600,500,600,1600,600,1600,550,550,550,550,600,1600,550,1650,550,1650,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,600,500,600,550,550,1600,600,500,600,1600,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,1650,550,1650,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,1600,600,500,550,550,550,550,600,500,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,1650,550,1650,550,1600,600};
unsigned int fan_a [230]={3250,2800,3150,4300,650,1550,650,450,650,1550,650,450,600,500,600,1600,600,1600,600,500,550,550,600,1600,550,1650,550,1650,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,600,500,600,550,550,1600,600,500,550,1650,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,1650,550,1650,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,550,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,1650,550,1650,550,1600,600};
unsigned int sleep_on [230]={3200,2850,3250,4150,750,1400,850,300,800,1400,800,300,750,350,800,1400,800,1400,750,350,750,350,750,1450,750,1450,750,1400,800,300,800,350,750,1400,800,350,750,350,750,350,750,350,750,350,750,350,800,1400,750,350,750,1450,750,350,750,350,700,400,700,450,650,450,650,450,650,450,650,450,600,500,600,1600,600,500,600,500,600,1600,600,500,600,500,600,550,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,1600,600,500,550,1650,550,1650,550,1650,550,550,550,1650,550,1650,550,550,550,550,550,550,550,550,550};
unsigned int sleep_off [230]={3250,2850,3200,4200,850,1350,800,300,800,1350,850,250,850,300,750,1450,800,1350,800,350,750,350,750,1450,750,1450,750,1400,800,300,800,300,800,1400,750,350,800,300,800,350,750,350,750,350,700,450,650,1500,650,450,650,1550,650,450,650,450,650,500,600,500,600,500,550,550,550,550,550,550,600,500,600,1600,550,550,550,550,550,1650,550,550,600,500,600,500,600,1600,600,500,600,1600,600,550,550,550,550,550,550,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,500,600,550,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,1600,600,500,600,1600,550,1600,600,550,550,550,550,1650,550,1650,550,550,550,550,550,550,550,550,550};
unsigned int fresh_on [230]={3250,2800,3200,4200,750,1450,750,350,800,1400,800,300,750,350,750,1450,750,1400,800,350,750,350,750,1450,750,1450,750,1450,750,350,750,350,750,1400,750,400,750,350,750,350,750,350,750,350,700,450,650,1500,700,400,700,1500,650,450,650,500,600,500,600,500,600,500,600,500,550,550,550,550,600,500,600,1600,600,500,600,550,550,1650,500,600,550,550,550,550,550,1600,600,500,600,1600,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,500,550,600,500,600,500,600,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,600,500,600,550,500,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,1600,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,1650,550,550,550,1650,550,1650,550,1600,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550};
unsigned int fresh_off [230]={3250,2800,3150,4300,650,1550,650,450,650,1500,700,450,600,500,600,1600,600,1600,550,550,550,550,600,1600,550,1650,550,1650,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,600,500,550,600,550,1600,550,550,550,1650,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,1650,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,600,500,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,1600,600,500,550,550,550,550,600,500,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,1650,550,1650,550,550,550,1650,550,1600,550,550,550,1650,550,550,550,550,600,500,600,500,600,500,600,550,550};
unsigned int health_airflow_1 [230]={3250,2800,3250,4150,850,1350,850,250,850,1350,850,250,850,300,750,1450,750,1400,800,300,800,300,850,1350,750,1450,750,1450,750,350,800,300,800,300,800,1400,750,350,800,300,800,300,800,300,750,350,800,1400,800,300,800,1400,750,350,750,400,650,450,650,450,650,450,650,450,650,450,650,500,600,500,600,1600,550,550,550,550,550,1650,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,1650,550,1600,600,1600,600,1600,550,1650,550,550,550,1650,550,550,550,550,600,500,550,550,550,1650,550,1650,550};
unsigned int health_airflow_2 [230]={3250,2800,3250,4150,800,1400,800,350,750,1450,700,400,700,400,700,1500,650,1550,650,450,650,450,650,1550,650,1550,600,1600,600,500,600,550,550,1600,550,1650,550,550,550,550,550,550,550,550,600,500,600,1600,600,500,550,1650,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,1650,550,550,550,550,550,1650,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,600,500,550,550,600,550,500,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,600,500,550,550,600,500,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,550,550,550,600,500,600,500,600,1600,600,1600,600,1600,600,1600,600,1600,550,550,550,1650,550,550,550,550,550,550,550,1650,550,550,550,1650,550};
unsigned int health_airflow_3 [230]={3250,2800,3200,4200,800,1400,750,350,800,1400,800,300,750,350,750,1450,750,1450,700,450,650,450,650,1500,700,1500,650,1550,650,450,650,500,600,1600,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,600,500,600,500,600,550,550,550,500,600,550,500,600,1600,600,500,600,550,550,1650,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,1600,550,550,550,550,550,550,600,500,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,500,600,550,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,1650,550,1600,550,1650,550,1650,550,1650,550,550,550,1650,550,550,550,550,550,550,550,1650,550,550,550,550,550};
unsigned int health_airflow_4 [230]={3250,2800,3250,4150,800,1400,800,300,800,1400,800,300,750,400,700,1500,650,1500,700,450,650,450,650,1550,650,1550,600,1600,600,500,600,500,600,500,600,1600,550,550,550,550,550,550,550,550,600,500,600,1600,600,500,600,1600,550,550,550,550,600,500,550,550,550,550,600,500,600,500,600,550,550,550,550,1650,550,550,550,550,550,1650,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,1600,600,1600,600,1600,600,1600,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,550,1650,550,1650,550};
unsigned int cold_mode [230]={3250,2800,3200,4200,900,1300,850,250,900,1300,900,200,900,250,750,1400,850,1350,850,250,850,250,800,1400,750,1450,750,1450,750,350,750,350,800,1400,750,350,800,300,800,300,750,350,800,300,800,350,750,1400,800,300,800,1400,750,400,650,450,650,450,650,450,650,450,650,450,650,500,600,500,600,500,600,1600,550,550,550,1650,550,550,550,550,600,500,550,550,600,1600,550,550,550,1650,550,550,550,550,600,500,600,500,600,550,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,1600,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,1650,550,1650,550,550,550,550,550,550,600,1600,550,1650,550,550,600,500,600,1600,550,1600,600};
unsigned int humid_mode [230]={3250,2800,3250,4150,850,1350,850,300,750,1450,750,350,750,350,800,1350,800,1400,800,300,800,1400,800,300,800,350,750,350,700,400,700,400,700,1500,650,450,650,500,600,500,600,500,600,500,600,500,600,1600,550,550,550,1650,550,550,550,550,550,550,600,500,550,600,500,600,550,500,600,500,600,500,600,1600,600,550,550,1650,550,550,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,600,500,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,600,500,600,550,550,550,550,550,550,550,550,1650,550,1600,600,550,550,550,550,1650,550,1650,550,550,550,550,550,550,550,1650,550,1600,550};
unsigned int fan_mode [230]={3250,2800,3200,4200,800,1400,750,400,650,1550,650,450,650,450,650,1550,650,1550,600,500,600,1600,600,500,600,500,600,500,600,550,550,550,550,1600,550,600,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,1600,600,500,600,1600,600,500,600,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,600,500,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,1650,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,600,500,600,550,500,600,550,550,500,600,550,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,1650,550,1650,550,550,550,550,550,1600,600,1600,600,500,600,550,550,550,550,1600,600,1600,600};
unsigned int heater_mode [230]={3250,2800,3250,4200,700,1500,650,450,650,1550,650,450,650,450,650,1550,650,1550,600,500,600,1600,600,500,600,550,550,550,550,1650,550,550,550,1650,500,550,600,500,600,550,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,600,500,550,550,550,550,550,550,600,500,600,1600,600,500,600,1600,600,500,600,550,550,550,550,1600,550,550,550,1650,550,1650,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,500,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,1600,550,1650,550,550,550,550,550,1650,550,1650,550,550,550,1650,550,1650,550,550,550,550,550};
unsigned int auto_mode [230]={3200,2850,3250,4150,800,1400,800,300,750,1450,750,350,750,350,750,1450,700,1500,650,450,700,1500,650,450,650,500,600,500,600,500,600,500,600,1600,550,550,550,550,550,550,600,500,600,500,600,550,550,1650,550,550,500,1650,600,500,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,600,1600,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,550,550,550,600,500,600,550,550,500,600,550,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,1650,550,550,550,550,550,550,550,1650,550,550,550,550,600,1600,550,550,550,550,550};
unsigned int off_mode [230]={3300,2750,3250,4150,850,1350,850,250,750,1450,800,300,850,250,850,1350,850,1350,750,350,850,250,850,1350,850,1350,800,1350,850,250,850,300,750,1400,800,350,750,350,750,350,800,300,800,300,750,350,800,1400,750,350,750,1450,650,450,700,400,700,400,700,450,600,500,650,450,600,500,600,500,600,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,1600,600,1600,600,550,550,1600,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,500,600,500,550,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,1600,600,500,600,1600,600,1600,550,1650,550,1650,550,1650,550,550,550,550,550,1650,550,1600,600};
unsigned int on_mode [230]={3200,2850,3250,4150,800,1400,800,300,800,1400,750,350,800,300,800,1400,750,1500,650,450,650,450,650,1550,650,1550,600,1600,600,500,600,500,600,1600,550,550,550,550,600,500,600,500,600,550,550,550,550,1600,600,500,600,1600,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,600,1600,550,550,550,550,550,550,550,1650,550,1650,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,600,500,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,600,550,500,600,550,550,550,550,550,500,600,550,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,550,550,600,500,600,500,600,550,550,550,550,1650,550,550,550,1650,550,550,550,550,550,1600,600,1600,600,500,600,500,600,1600,600,1600,550};
unsigned int light_on [230]={3250,2800,3250,4150,800,1400,800,300,800,1400,800,300,800,350,800,1400,750,1400,800,350,750,300,800,1400,750,1450,750,1450,750,350,850,250,850,1350,800,300,850,250,850,300,750,300,800,350,750,350,750,1400,800,300,800,1400,800,350,650,450,650,450,700,400,650,450,650,500,600,500,600,500,600,500,600,1600,600,500,550,1650,550,550,550,550,600,1600,550,550,600,1600,550,550,550,1650,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,1650,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,1650,550,550,550,1650,550,550,550,1600,600,500,600,1600,600,550,550,550,550,550,550,1650,550,550,550,550,550};
unsigned int light_off [230]={3250,2800,3150,4300,650,1550,650,450,650,1550,650,450,650,450,650,1550,600,1600,600,500,600,500,600,1600,600,1600,600,1600,600,500,550,600,500,1650,550,550,550,550,600,500,600,500,600,550,550,550,550,1650,550,550,550,1650,550,550,550,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,600,1600,600,500,600,500,600,1600,600,500,550,1650,550,550,550,1650,550,550,600,500,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,550,550,600,500,600,1600,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,500,550,550,600,500,600,500,600,550,550,550,550,550,550,550,550,550,550,550,600,500,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,600,500,600,550,550,550,550,550,550,550,550,550,550,550,550,550,600,1600,600,500,550,1650,550,550,550,1650,550,550,550,1650,550,550,550,550,550,550,550,1650,550,550,550,550,550};


void Bot_ExecMessages(){
  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)      {
     bot.message[i][5]=bot.message[i][5].substring(1,bot.message[i][5].length());
    if (bot.message[i][5] == "\/ac_on") {
      irsend.sendRaw(on_mode,230,38);
      delay(100);
      bot.sendMessage(bot.message[i][4], "Air conditioner is ON!", "");
    }
    if (bot.message[i][5] == "\/ac_off") {
      irsend.sendRaw(off_mode,230,38);
      delay(100);
      bot.sendMessage(bot.message[i][4], "Air conditioner is OFF...", "");
    }
    if (bot.message[i][5] == "\/21") {
    irsend.sendRaw(t_21,230,38);
    delay(1000);
    bot.sendMessage(bot.message[i][4], "Temp sucsessfuly set to +21", "");
    }
    if (bot.message[i][5] == "\/22") {
    irsend.sendRaw(t_22,230,38);
    delay(1000);
    bot.sendMessage(bot.message[i][4], "Temp sucsessfuly set to +22", "");
    }
    if (bot.message[i][5] == "\/23") {
    irsend.sendRaw(t_23,230,38);
    delay(1000);
    bot.sendMessage(bot.message[i][4], "Temp sucsessfuly set to +23", "");
    }
    if (bot.message[i][5] == "\/24") {
    irsend.sendRaw(t_24,230,38);
    delay(1000);
    bot.sendMessage(bot.message[i][4], "Temp sucsessfuly set to +24", "");
    }
    if (bot.message[i][5] == "\/25") {
    irsend.sendRaw(t_25,230,38);
    delay(1000);
    bot.sendMessage(bot.message[i][4], "Temp sucsessfuly set to +25", "");
    }
    if (bot.message[i][5] == "\/fan_mode") {
    irsend.sendRaw(fan_mode,230,38);
    delay(1000);
    bot.sendMessage(bot.message[i][4], "Fan mode has been activated", "");
    }
    if (bot.message[i][5] == "\/cold_mode") {
    irsend.sendRaw(cold_mode,230,38);
    delay(1000);
    bot.sendMessage(bot.message[i][4], "Cooling mode has been activated", "");
    }
    if (bot.message[i][5] == "\/fan_slow") {
    irsend.sendRaw(fan_1,230,38);
    delay(1000);
    bot.sendMessage(bot.message[i][4], "Fan speed set to slow", "");
    }
    if (bot.message[i][5] == "\/fan_medium") {
    irsend.sendRaw(fan_2,230,38);
    delay(1000);
    bot.sendMessage(bot.message[i][4], "Fan speed set to medium", "");
    }
    if (bot.message[i][5] == "\/fan_max") {
    irsend.sendRaw(fan_3,230,38);
    delay(1000);
    bot.sendMessage(bot.message[i][4], "Fan speed set to medium", "");
    }
    if (bot.message[i][5] == "\/fan_auto") {
    irsend.sendRaw(fan_a,230,38);
    delay(1000);
    bot.sendMessage(bot.message[i][4], "Fan speed set to automatic mode", "");
    }    
    if (bot.message[i][5] == "\/reset") {
      bot.sendMessage(bot.message[i][4], "ESP is going to restart...", "");
      bot.message[0][0] = "";   // All messages have been replied - reset new messages
      bot.getUpdates(bot.message[0][1]);
      delay(5000);
      ESP.restart();
    }
//    else {  bot.sendMessage(bot.message[i][4], EchoResponse, "");}
  }
      bot.message[0][0] = "";   // All messages have been replied - reset new messages
}

void TelegramCheck()  {
      bot.getUpdates(bot.message[0][1]);
      Bot_ExecMessages();
}
void setup()
{
  Serial.begin(9600);
  delay(10);
  irsend.begin();
  Blynk.begin(auth, ssid, password);
   while (Blynk.connect() == false) {
    // Wait until connected
  }

   Blynk.notify("Air control has started!");
// bridge1.setAuthToken(auth1);

//############### Define timers ##########

   timer.setInterval(10000L, TelegramCheck);
}
void loop() {
  Blynk.run();
  timer.run();

}

BLYNK_WRITE(0)  // Telegram Check
 {
  int a = param.asInt();
    if (a == 0)
  {
    TelegramCheck();
  }
 }