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

#define left_motor = 5; /*сетваме кой порт ще използваме*/
#define right_motor = 6; /*сетваме кой порт ще използваме*/
int process_time=10000;/*правим си променлижа за цялото време или с други думи тожа ни е променливата която ни държи цялото време*/
int max_light=255;/*определяме колко е маскималната ни светлина(в случая иначе може да бъде всичко) до която може да стигне обекта*/
float calculated_time = process_time/max_light;/*това е времете между всяко засилжане или намаляне на оборотите(моторчето) или светлината(диода)*/
void setup() /*В този случай пищем задачата в сетъпа защото искаме да се изпълни само веднъж кода ни; ако искахме да се изпълняжа много пъти или безкрайно го пишем във луупа защото той е нещо като безкраен цикъл, като стигне до последния ред започва отножо от първия в луупа*/
{
  pinMode(left_motor, OUTPUT); /*казжаме на че ще използваме изход*/
  pinMode(right_motor, OUTPUT); /*казжаме на че ще използваме изход*/
  
  for(int light=0; light < max_light; light++)/*правим си прост фор цикъл; променливата която правим в цикъла ще я използваме по надолу в кода*/
  {
    int light_2 = max_light-light ;
    analogWrite(left_motor, light);/*в случая използваме променливата която върти цикъла за стойноста която ще свети светлината или ще се въртят оборотите;*/
    analogWrite(right_motor, light_2);
    delay(calculated_time);/*слагаме времето между всяко увеличаване на светлинаи или оборотите*/
  }
  delay(5000);/*слагаме време между увеличажането и намаляването на светлината или обортите; в това време то ще свети или ще се върти маскимално(колкото сме го сетнали в началото демек 255)*/
  for(int light=255; light > min_light; light--)/*тук е същото като горния цикъл само че го използваме за да спрем или да угасим плавно диода, моточето*/
  {
    int light_2 = max_light-light ;
    analogWrite(left_motor, light_2);/*в случая използваме променливата която върти цикъла за стойноста която ще свети светлината или ще се въртят оборотите;*/
    analogWrite(right_motor, light);
    delay(calculated_time);/*слагаме времето между всяко увеличаване на светлинаи или оборотите*/}
  }

// the loop routine runs over and over again forever:
void loop() 
{
}
