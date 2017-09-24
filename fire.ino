
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "plantech-35083.firebaseio.com"
#define FIREBASE_AUTH "D3yoygPRDIN2U3oJHCvvyc1ZjBzYcybf4ZhIP8nq"
#define WIFI_SSID "Aseem Sharma"
#define WIFI_PASSWORD ""

int sensor_pin = A0; 

int output_value ;

void setup() {
  Serial.begin(9600);

  Serial.println("Reading From the Sensor ...");

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
}

int button = 0;
float light = 0.0;

void loop() {
  
   output_value= analogRead(sensor_pin);
  output_value = map(output_value,955,395,0,100);
  Serial.print("Mositure : ");
  //Serial.print(output_value);
  Serial.println("%");
         // ...for 1 sec
  int out;
out= Firebase.getInt("value");

 int last_value =out-output_value;
 Serial.println(last_value);
 if(out!=output_value){
  Firebase.pushInt("moisture",last_value);
  }
 Firebase.setInt("value", output_value);
 
 delay(1000);
 
}
