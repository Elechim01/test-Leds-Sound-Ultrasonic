#include <MeAuriga.h>
#define ALLLEDS 0;
#ifdef MeAuriga_H
// nuero led di auriga
#define LEDNUM 12

// On board Led ring, at Port 0
MeRGBLed led(0, LEDNUM);
#else
#define LEDNUM 14
// Dispositivo esterno
MeRGBLed led(PORT_3)
#endif

#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233

MeUltrasonicSensor ultraSensor(PORT_9);

MeBuzzer buzzer;

float j, f, k;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(1);

// Setto i led
#ifdef MeAuriga_H
  led.setpin(44);
  buzzer.setpin(45);
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Distanza: ");

// Funziona 
//buzzer.tone(45,1047,300);

 delay(300);
  double distance = ultraSensor.distanceCm();
  if (distance < 30) {
    // Cambiare note
      showLed();
    playCustom();
  

  } else {
    clearLed();
  }
  Serial.print(distance);
  Serial.println("cm");
}

int listaNote[] = {
  NOTE_GS3,
  NOTE_A3 ,
  NOTE_AS3,
};

 void playCustom(){
for (int posizioneNota = 0; posizioneNota < 4; posizioneNota++ ){
  Serial.print(listaNote[posizioneNota]);
  Serial.print("\n");
  buzzer.tone(45, listaNote[posizioneNota],100);
  delay(1000);
  buzzer.noTone();
}
 }

void showLed() {
  for (uint8_t t = 0; t < LEDNUM; t++) {
    uint8_t red = 64 * (1 + sin(t / 2.0 + j / 4.0));
    Serial.println(red);
    uint8_t green = 64 * (1 + sin(t / 2.0 + j / 4.0));
    Serial.println(green);
    uint8_t blue = 64 * (1 + sin(t / 2.0 + j / 4.0));
    Serial.println(blue);
    led.setColor(t, 255, 0, 0);
  }
  led.show();

  j += random(1, 6) / 6.0;
  f += random(1, 6) / 6.0;
  k += random(1, 6) / 6.0;
}

void clearLed() {
  for (uint8_t t = 0; t < LEDNUM; t++) {
    led.setColor(t, 0, 0, 0);
  }
  led.show();
}
