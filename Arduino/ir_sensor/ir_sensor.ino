//hold button logic

//inisialisasi infrared
int ir = 2;

//inisialisasi led
int r = 5;
int y = 6;
int g = 7;

//button ir 1 led 1
int laststate = 0;
int newstate = 0;
int ledstate = 0;

//button logic 2 led 2
int laststate2 = 0;
int newstate2 = 0;
int ledstate2 = 0;

//button logic 3 led 3
int laststate3 = 0;
int newstate3 = 0;
int ledstate3 = 0;

void setup() {
  // serial setup
  Serial.begin(9600);

  //led as output
  pinMode(r, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(g, OUTPUT);

  //button as input
  pinMode(ir, INPUT);
  
}

void loop() {
  // pembacaan button
newstate = digitalRead(ir);

Serial.println(newstate);

//button 1 untuk led 1
  if(laststate == 0 && newstate == 1){
    if(ledstate == 1){
       digitalWrite(r, LOW);
       ledstate = 0;
    } else{
        digitalWrite(r, HIGH);
        ledstate = 1;
    }
  }
  laststate = newstate;
  

/*
//button2 untuk led 2
  if(laststate2 == 0 && newstate2 == 1){
    if(ledstate2 == 1){
       digitalWrite(y, HIGH);
       ledstate2 = 0;
    } else{
        digitalWrite(y, LOW);
        ledstate2 = 1;
    }
  }
  laststate2 = newstate2;

//button 3 untuk led 3
  if(laststate3 == 0 && newstate3 == 1){
    if(ledstate3 == 1){
       digitalWrite(g, HIGH);
       ledstate3 = 0;
    } else{
        digitalWrite(g, LOW);
        ledstate3 = 1;
    }
  }
  laststate3 = newstate3;
*/  
}
