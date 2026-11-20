#define trig 10
#define echo 11

const int RedPinRelay = 4;
const int YellowPinRelay = 5;
const int GreenPinRelay = 9;
const int PumpRelay = 15;
const int StartButton = 7;
const int StopButton = 3;
const int EmergencyButton = 2;

bool isStarted = false;
bool emergencyState = false;
double distanceCM = 0;

void TurnsOff(){

    digitalWrite(RedPinRelay, LOW);
    digitalWrite(YellowPinRelay, LOW);
    digitalWrite(GreenPinRelay, LOW);
    digitalWrite(PumpRelay, HIGH);


}

void updateEmergencyState(){

    emergencyState = (digitalRead(EmergencyButton)==LOW);

}

void updateSystemState(){

    if (digitalRead(StartButton)==LOW){

        isStarted = true;

    }
    if (digitalRead(StopButton)==LOW){

        isStarted = false;

    }

}

double measureDistance(){

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    long duration = pulseIn(echo, HIGH);
    return duration * 0.0343 / 2.0;
    
}

void controlLevel(double distance){

    if (distance >= 20){

        digitalWrite(RedPinRelay, LOW);
        digitalWrite(YellowPinRelay, HIGH);
        digitalWrite(GreenPinRelay, HIGH);
        digitalWrite(PumpRelay, HIGH);
    
    }
    else if(distance > 6){

        digitalWrite(RedPinRelay, HIGH);
        digitalWrite(YellowPinRelay, LOW);
        digitalWrite(GreenPinRelay, HIGH);
        digitalWrite(PumpRelay, LOW);

    }
    else{

        digitalWrite(RedPinRelay, HIGH);
        digitalWrite(YellowPinRelay, HIGH);
        digitalWrite(GreenPinRelay, LOW);
        digitalWrite(PumpRelay, LOW);      

    }

}


void setup (){

    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(RedPinRelay, OUTPUT);
    pinMode(YellowPinRelay, OUTPUT);
    pinMode(GreenPinRelay, OUTPUT);
    pinMode(PumpRelay, OUTPUT);
    pinMode(StartButton, INPUT_PULLUP);
    pinMode(StopButton, INPUT_PULLUP);
    pinMode(EmergencyButton, INPUT_PULLUP);

    digitalWrite(RedPinRelay, LOW);
    digitalWrite(RedPinRelay, LOW);
    digitalWrite(RedPinRelay, LOW);
    digitalWrite(RedPinRelay, LOW);
    
    TurnsOff();
    Serial.begin(9600);
}

void loop(){

    updateEmergencyState();

    if(emergencyState){

        TurnsOff();

        Serial.println("EMERGENCY STOP!");
        delay(100);
        return;

    }

    updateSystemState();

    if(!isStarted){

        TurnsOff();

        Serial.println("System OFF");
        delay(100);
        return;

    }

    distanceCM = measureDistance();
    Serial.print("Distance: ");
    Serial.print(distanceCM);
    Serial.println(" cm"); 

    controlLevel(distanceCM);
    delay(100);

}
