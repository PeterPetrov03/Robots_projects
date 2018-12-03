/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fade
*/

#define LEFT_MOTOR 5 /*сетваме кой порт ще използваме*/
#define RIGHT_MOTOR 6 /*сетваме кой порт ще използваме*/
#define LEFT_MOTOR_DIR 4 /*сетваме кой порт ще използваме*/
#define RIGHT_MOTOR_DIR 7 /*сетваме кой порт ще използваме*/
#define encoder0PinA  2
#define encoder0PinB  3

unsigned int encoder0Pos=0;
int newposition;
int oldposition;
int newtime;
int oldtime;
int process_time=5000;/*правим си променлижа за цялото време или с други думи тожа ни е променливата която ни държи цялото време*/
int max_speed=255;/*определяме колко е маскималната ни светлина(в случая иначе може да бъде всичко) до която може да стигне обекта*/
float vel;
uint16_t prtime;

uint16_t toSpeed(uint16_t path, uint16_t timee) 
{
  //uint16_t prtime=path/velocity;
  return (path/timee)/2; 
}

uint16_t toPath(uint16_t timee, uint16_t sped)
{
  return sped*timee;
}

uint16_t moove(uint16_t velocity)
{
  analogWrite(LEFT_MOTOR, 0);
  analogWrite(RIGHT_MOTOR, 0);

  if(velocity>0)
  {
    digitalWrite(LEFT_MOTOR_DIR, HIGH);
    digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  } else if(velocity<0) {
    velocity = velocity*-1;
    digitalWrite(LEFT_MOTOR_DIR, LOW);
    digitalWrite(RIGHT_MOTOR_DIR, LOW);
    
  } else {
    analogWrite(LEFT_MOTOR, 0);
    analogWrite(RIGHT_MOTOR, 0);
  }
  

  analogWrite(LEFT_MOTOR, velocity);
  analogWrite(RIGHT_MOTOR, velocity);
}

uint16_t cross_moove(uint16_t velocity, uint16_t velocity_2)
{
  analogWrite(LEFT_MOTOR, 0);
  analogWrite(RIGHT_MOTOR, 0);

  if(velocity>0 && velocity_2<0)
  {
    digitalWrite(LEFT_MOTOR_DIR, HIGH);
    digitalWrite(RIGHT_MOTOR_DIR, LOW);
  } else if(velocity>0 && velocity_2==0) {
    velocity = velocity*-1;
    digitalWrite(LEFT_MOTOR_DIR, HIGH);
    digitalWrite(RIGHT_MOTOR_DIR, 0);
    
  } else if(velocity<0 && velocity_2>0) {
    velocity = velocity*-1;
    digitalWrite(LEFT_MOTOR_DIR, LOW);
    digitalWrite(RIGHT_MOTOR_DIR, HIGH);
    
  } else if(velocity==0 && velocity_2>0) {
    velocity = velocity*-1;
    digitalWrite(LEFT_MOTOR_DIR, 0);
    digitalWrite(RIGHT_MOTOR_DIR, HIGH);
    
  } else {
    analogWrite(LEFT_MOTOR, 0);
    analogWrite(RIGHT_MOTOR, 0);
  }
  
  analogWrite(LEFT_MOTOR, velocity);
  analogWrite(RIGHT_MOTOR, velocity);
  delay(prtime);
}

void doEncoder() 
{
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }

  Serial.println (encoder0Pos, DEC);
}

void setup() /*В този случай пищем задачата в сетъпа защото искаме да се изпълни само веднъж кода ни; ако искахме да се изпълняжа много пъти или безкрайно го пишем във луупа защото той е нещо като безкраен цикъл, като стигне до последния ред започва отножо от първия в луупа*/
{
  pinMode(LEFT_MOTOR_DIR, OUTPUT); 
  pinMode(RIGHT_MOTOR_DIR, OUTPUT); 
  pinMode(LEFT_MOTOR, OUTPUT); 
  pinMode(RIGHT_MOTOR, OUTPUT); 
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor
  attachInterrupt(0, doEncoder, RISING);  // encoDER ON PIN 2
  Serial.begin (9600);
  Serial.println("start"); 
}

void loop() 
{
  for(int i=0; i<process_time; i++)
  {
    moove(200);
  }
}
