#include "pitches.h"

int LED = 9;
int piezoSpeaker = 6;
int button = 2;

//Variables for button debouncing
volatile int pressed = 0;
volatile int pressed_conf = 0;
volatile int release_conf = 0;

volatile int note_duration = 1000;


void setup()
{
	Serial.begin(9600);
	pinMode(LED, OUTPUT);
	pinMode(button, INPUT);
}

void loop()
{
	//Button Pressed
	if (digitalRead(button) == HIGH)
	{
		note_duration += note_duration + 100;
		pressed_conf++;
		release_conf = 0;
		if (pressed_conf > 10) {
			if (pressed == 0) {
				digitalWrite(LED, HIGH);
				tone(piezoSpeaker, NOTE_D8, note_duration);
				Serial.print("Button Pressed:");
				pressed = 1;
			}
			pressed_conf = 0;
		}
	}
	else {
		release_conf++;
		pressed_conf = 0;
		if (release_conf > 1)
		{
			if (pressed == 1) {
				digitalWrite(LED, LOW);
				noTone(piezoSpeaker);
				Serial.print("Button Released");
				pressed = 0;
				note_duration = 1000;
			}
			release_conf = 0;
		}
	}
}