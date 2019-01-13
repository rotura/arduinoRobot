
int IN1 = 7; 
int IN2 = 6;
int IN3 = A5; 
int IN4 = 4;
int ENB = 10; 
int ENA = 11;
int lightP = 5;

/*
2-  horizontal stick       <1000, 1450-1470 (0), >1900
3-  vertical stick         <1000, 1450-1470 (0) 
8-  3 pos Switch           <1000, 1460-1470, >1900
9-  left middle Switch     <1600, >1600
12- left bottom Switch     <1600, >1600
13- Pot Aux 2 (left)       967-1468
*/
float chValue[6] = {1460,1460,1465,1400,1400,967};
int rcPins[6] = {2,3,8,9,12,13};

int vel = 255;
int up = 0;
int right = 0;
int lightV = 0;
boolean light = false;

void setup()
{
  pinMode (lightP, OUTPUT); // Light pwm 
  pinMode (IN4, OUTPUT);    // Input4 connected to pin 4 
  pinMode (IN3, OUTPUT);    // Input3 connected to pin 1
  pinMode (IN2, OUTPUT);    // Input2 connected to pin 6 
  pinMode (IN1, OUTPUT);    // Input1 connected to pin 7
  pinMode (ENB, OUTPUT);    // EnB connected to pin 10 
  pinMode (ENA, OUTPUT);    // EnA connected to pin 11

  pinMode (2, INPUT);    
  pinMode (3, INPUT);    
  pinMode (8, INPUT);    
  pinMode (9, INPUT);    
  pinMode (12, INPUT);
  pinMode (13, INPUT);
   
  //Serial.begin(9600);
}
void loop()
{
  for(int iChannel = 0; iChannel < 6; iChannel++)
  {
    readChannel(iChannel);
  }
  runRobot();
}
 
void readChannel(int channel)
{
  chValue[channel] = pulseIn(rcPins[channel],HIGH);
  processChannel(rcPins[channel], chValue[channel]);
}

void processChannel(int channel, float val){
  switch(channel){
     case 2:
      changeRight(val);
      break;
     case 3:
      changeUp(val);
      break;
     case 8:
      // Uncomment if you like to use variable velocity
      //changeSpeed(val);
      break;
     case 9:
      break;
     case 12:
      changeLight(val);
      break;
     case 13:
      lightV = map(val, 967, 1468, 20, 255);
      break;
     
    }
  }

// Change Light luminous
void changeLight(int val){
    if(val > 1600)
      analogWrite(lightP, lightV);
    else
      analogWrite(lightP, 0);
  }

//Change speed of the robot
void changeSpeed(int val){
    if(val < 1000)
      vel = 200;
    else if (val > 1900)
      vel = 255;
    else
      vel = 230;
  }

//Determine if the robot go back, fordward or dont move
void changeUp(int val){
    if(val < 1400)
      up = -1;
    else if (val > 1500)
      up = 1;
    else
      up = 0;
  }

//Determine if the robot is tuning left, right or none
void changeRight(int val){
    if(val < 1400)
      right = -1;
    else if (val > 1500)
      right = 1;
    else
      right = 0;
  }

//Execute actions in function of the values stored in "proccessChannel"
void runRobot(){
  if(up == 1){
    if(right == 1)
      turnRight();
    else if (right == -1)
      turnLeft();
    else
      fordward();
    }
  else if(up == -1){
    if(right == 1)
      turnRightBehind();
    else if (right == -1)
      turnLeftBehind();
    else
      behind();
    }
  else{
    if(right == 1)
      rotateRight();
    else if (right == -1)
      rotateLeft();
    else
      stopR();
    }
  }


// Methods to control the robot.
// The "-50" is because of the difference in power of the 2 motors used

  void stopR(){
    //Left
    analogWrite(ENA, 0);
    digitalWrite (IN2, LOW);
    digitalWrite (IN1, LOW);
    //Right
    analogWrite(ENB, 0);
    digitalWrite (IN4, LOW);
    digitalWrite (IN3, LOW);
  }

  void fordward(){
    //Left
    analogWrite(ENA, vel-50);
    digitalWrite (IN2, HIGH);
    digitalWrite (IN1, LOW);
    //Right
    analogWrite(ENB, vel);
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW);
    }

  void behind(){
    //Left
    analogWrite(ENA, vel-50);
    digitalWrite (IN2, LOW);
    digitalWrite (IN1, HIGH);
    //Right
    analogWrite(ENB, vel);
    digitalWrite (IN4, LOW);
    digitalWrite (IN3, HIGH);
    }

  void turnRight(){
    //Left
    analogWrite(ENA, vel);
    digitalWrite (IN2, HIGH);
    digitalWrite (IN1, LOW);
    //Right
    analogWrite(ENB, vel-50);
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW);
    }

  void turnLeft(){
    //Left
    analogWrite(ENA, vel-125);
    digitalWrite (IN2, HIGH);
    digitalWrite (IN1, LOW);
    //Right
    analogWrite(ENB, vel);
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW);
    }

   void turnRightBehind(){
    //Left
    analogWrite(ENA, vel);
    digitalWrite (IN2, LOW);
    digitalWrite (IN1, HIGH);
    //Right
    analogWrite(ENB, vel-50);
    digitalWrite (IN4, LOW);
    digitalWrite (IN3, HIGH);
    }

  void turnLeftBehind(){
    //Left
    analogWrite(ENA, vel-125);
    digitalWrite (IN2, LOW);
    digitalWrite (IN1, HIGH);
    //Right
    analogWrite(ENB, vel);
    digitalWrite (IN4, LOW);
    digitalWrite (IN3, HIGH);
    }

void rotateRight(){
    //Left
    analogWrite(ENA, vel-50);
    digitalWrite (IN2, HIGH);
    digitalWrite (IN1, LOW);
    //Right
    analogWrite(ENB, vel);
    digitalWrite (IN4, LOW);
    digitalWrite (IN3, HIGH);
    }

  void rotateLeft(){
    //Left
    analogWrite(ENA, vel-50);
    digitalWrite (IN2, LOW);
    digitalWrite (IN1, HIGH);
    //Right
    analogWrite(ENB, vel);
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW);
    }

