#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int porta_sensor = A0;
int porta_buzzer = 11;
int led1 = 5;
int led2 = 6;

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int melody[] = {NOTE_C5, NOTE_F6, NOTE_F6, NOTE_C5, NOTE_F6, NOTE_F6, NOTE_C5, NOTE_F6, NOTE_CS5, NOTE_F6};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

int numReadings = 8;
int sumReadings;
int curReadings = 0;

unsigned long timeout = 60000;
unsigned long starting_time;

void setup() {
    pinMode(porta_sensor, INPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(porta_buzzer, OUTPUT);
    Serial.begin(9600);
    starting_time = millis();
}

void loop() {
    int sensorReading = analogRead(porta_sensor);
    
    if (curReadings < numReadings){ // Sampling
        sumReadings = sumReadings + sensorReading;
        curReadings++;
    } else {
        curReadings = 0;
        sensorReading = sumReadings/numReadings;
        sumReadings = 0;
        
        Serial.println(sensorReading);
        if (sensorReading > 30) { // Presence
            
            int brightness = map(sensorReading, 0, 700, 0, 255);
            int thisPitch = map(sensorReading, 0, 700, 300, 1500);

            analogWrite(led1, brightness);
            analogWrite(led2, brightness);
            
            tone(porta_buzzer, thisPitch, 10);
            delay(10);
            
        } else { // Standby
            fade();
            if ((millis() - starting_time) > timeout){
                playTheme();
                starting_time = millis();
            }
        }
    }
}

void fade(){
    analogWrite(led1, brightness);
    analogWrite(led2, brightness);
    
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;
    
    // reverse the direction of the fading at the ends of the fade:
    if (brightness == 0 || brightness == 255) {
        fadeAmount = -fadeAmount ;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
}

void playTheme(){
    for (int thisNote = 0; thisNote < 11; thisNote++) {
        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000/noteDurations[thisNote];
        tone(porta_buzzer, melody[thisNote],noteDuration);
        
        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.4;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(porta_buzzer);
    }
}
