#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 int voltageSensor1 = A0;//initializing pins to sensor,solar voltge
int voltageSensor2 = A1;//wind
unsigned int wp=0;
float AcsValue=0.0,Samples=0.0,AvgAcs=0.0,AcsValueF=0.0; // WIND CURRENT A2

unsigned int m=0;
float AcsValue1=0.0,Samples1=0.0,AvgAcs1=0.0,AcsValueF1=0.0; // SOLAR CURRENT A3
 //windv
float vOUT = 0.0;
float vIN = 0.0;
float R1  = 1000.0;//in voltagesensor using 30k resistor
float R2  = 1000.0;//7.5 k resistor
float Value = 0;
int voltage=0;
float vcal=10;
float vOUT1 = 0.0;//initializing to zero
float vIN1 = 0.0;
float R11  = 1000.0;//in voltage sensor using 30k resistor
float R21  = 1000.0;//in volttage sensor using 7.5k resistor
float value1 = 0;
float Solarvoltage;
float solarcurrent;
float Solarcurrent;
float Windcurrent;
int k;
float I1 = 0;
float I2 = 0;
float power;//inializing the variables
float win;
float sol;
int a;
int b;
int x = 0;
int y = 0;
//int k;
///-------------street light--------------//
int ldr=6;
int ir1=7;
int ir2=8;
int jun=9;
int jun1=10;
int switch1=11;
int t;
int q;

int r=0;
int s;
//--------------------------------------------------------//
 int currentPin = A2;
int sensitivity = 66;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
float currentValue = 0;
//------------------------------INITS----------------------------//
float sv;
void setup()
{
  Serial.begin(115200);//intialize the baud rate
  lcd.init();
 lcd.backlight();
 lcd.clear();
 lcd.clear();
 
 lcd.setCursor(0,0);
 lcd.print("POWER GENERATION");
 lcd.setCursor(0,1);
 lcd.print("USING VWM&SOLAR");
 delay(5000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("WI-FI INITIALIZE");
 lcd.setCursor(0,1);
 lcd.print("TURNON HOTSPOT");
 wifi_init();
 delay(5000);
 lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("WI-FI");
  lcd.setCursor(1, 1);
  lcd.print("INITIALIZATION");
 // wifi_init();//intialize wifi
  //-------------street light---------//
pinMode(ldr,INPUT);
pinMode(switch1,INPUT_PULLUP);
pinMode(ir1,INPUT);
pinMode(ir2,INPUT);
pinMode(jun,OUTPUT);
pinMode(jun1,OUTPUT);
digitalWrite(ldr, LOW);
digitalWrite(ir1, HIGH);
digitalWrite(ir2, HIGH);  
digitalWrite(jun, LOW);
digitalWrite(jun1, LOW);
digitalWrite(switch1, HIGH);
}
//----------------------------MAIN-------------------//
void loop()
{
//  solarV();
//  solarI();
//  solarp();//solar power calucaultion funtion.
//  windV();
//  windI();
 if(digitalRead(switch1)==0)
 {
   street();
 }
 else
 {
  allsen();
 }
// k=k+1;
// if(k==5)
// {
//  Serial.println("sending to server");
//  lcd.clear();
//  lcd.print("SENDING DATA TO");
//  lcd.setCursor(0,1);
//  lcd.print("   SERVER");
//  sendtoserver();
//  k=0;
 //}
}

//----------------------street light funtion------------------------//
void street()
{
lcd.clear();
lcd.print("STREET LIGHT MOD");
Serial.println("street light");
q=digitalRead(ir2);
if(digitalRead(ldr)==1)  //if night time
 {
   analogWrite(jun, 50);
   analogWrite(jun1, 50);
   if(digitalRead(ir1)==0)
  {
   analogWrite(jun, 255);
   Serial.println("LIGHTS ON");
   lcd.setCursor(0,1);
   lcd.print("ZONE-1 LIGHTS ON");
   delay(3000);
 }
 
 if(digitalRead(ir2)==0)
{
 analogWrite(jun1, 255);
 Serial.println("LIGHTS ON");
 lcd.setCursor(0,1);
 lcd.print("ZONE-2 LIGHTS ON");
 delay(3000);    
}
  }
  else
  {
   analogWrite(jun, 0);
     analogWrite(jun1, 0);
  }
 
}



//=======================WIND VOLATAGE FUNTION==========================================//
 void windV()// wind voltage caluculation funtion
{
  voltageSensor2 = analogRead(A1);//reading wind output voltage
  voltageSensor2 = (voltageSensor2/50);  //calibration
//
  if( voltageSensor2<=0)
  {
  voltageSensor2=0;;
 
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WIND VOLTAGE=");
  Serial.print("wind o/p voltage=");
  lcd.print(voltageSensor2);
  Serial.println(voltageSensor2);

  delay(1000);
  lcd.setCursor(15, 0);
  lcd.print("");
  Serial.println("  volts");
 
  delay(2000);
  lcd.clear();

}


//=======================WIND CURRENT FUNTION=================================//
void windI()//wind current caluculation funtion
{
 Windcurrent= voltageSensor2/20.5;
   lcd.setCursor(0, 1);
  lcd.print("CURRENT=");
  lcd.print(Windcurrent);
  lcd.print("A");
  Serial.print("CURRENT=");
  Serial.print(Windcurrent);
  Serial.println("  A");
  delay(2000);
  lcd.clear();

}

//---------------------------------------------------wind power-------------------//
void windp()
{

  win = (voltageSensor2 *Windcurrent);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("wind p=");
  lcd.setCursor(8, 0);
  lcd.print(win);
  lcd.setCursor(14, 0);
  lcd.print("W");
  delay(2000);
}
 
//=======================================SOLAR VOLATGE FUNTION=================================//
void solarV()//solar sensor volatage caluculation funtion
{

  Solarvoltage =analogRead(A0);                    //reading solar panel output
  Solarvoltage = Solarvoltage/23;  //calibration
 
  if( Solarvoltage>1)
  {
  Solarvoltage=Solarvoltage+1;
  sv=Solarvoltage;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SOLAR VOLT=");
  lcd.print(sv);
  lcd.print("V");
 
  Serial.print("solar o/p voltage=");
  Serial.println(sv);  
  Serial.println("V");  
  delay(2000);
 
}
//===============================SOLAR CURRENT FUNTION==============================================//
void solarI()//solar current caluculation funtion
{
  Solarcurrent=sv/12;
   lcd.setCursor(0, 1);
  lcd.print("CURRENT=");
  lcd.print(Solarcurrent);
  lcd.print("A");
  Serial.print("CURRENT=");
  Serial.print(Solarcurrent);
  Serial.println("  A");
  delay(2000);
  lcd.clear();
}

//--------------------------SOLAR POWER----------------//

void solarp()//solar power calucaultion funtion.
{

  sol = (sv* Solarcurrent);
  Serial.print("solar power=");
  Serial.println(sol);
  lcd.setCursor(0, 0);
  lcd.print("solar p=");
  lcd.print(sol);
  lcd.print("W");
  delay(2000);
}
//------------------------TOTAL POWER-----------------//  

void p()//total power caluculation funtion
{
    power = win + sol;
    lcd.setCursor(0, 0);
    lcd.print("total p=");
    lcd.setCursor(9, 0);
    lcd.print(power);
    lcd.setCursor(15, 0);
    lcd.print("W");
    delay(2000);
 }


 //--------------------------POWER CALCULATION--------------//
void allsen()
{
   Serial.println("power caluculation");
  //Serial.println("sensor funtion running");
  windV();//calling funtion of sensor caluculation
  //Serial.println("--------------");
  windI();// sWIND calling funtion of sensor caluculation
  //Serial.println("--------------");
  delay(2000);
  lcd.clear();
  windp();//calling total wind power caluculation
  delay(200);
  //Serial.println("--------------");
  solarV();//calling funtion of sensor caluculation
  //Serial.println("--------------");
  solarI();//calling funtion of sensor caluculation
  //delay(2000);
  //Serial.println("--------------");
  lcd.clear();
  solarp();//calling total  solar power caluculation
  //Serial.println("--------------");
  p();//calling total power caluculation
  //Serial.println("-------------------------uploadinggg---------------------------------------------");
  //delay(500);
  k = k + 1; //increamenting  loop

  if (k == 5) //loop runn for 10 times
  {
    lcd.clear();
   
  lcd.print("uploading data");
  lcd.setCursor(0, 1);
  lcd.print("   to Cloud");
  sendtoserver();
    // Serial.println("done uploading");
    k = 0;
  }

  //solarro();

}

//----------------------------WIFI------------------//  

void wifi_init()//wifi intialization
{
  Serial.begin(115200);//setting the baud rate
  delay(2000);
  Serial.println("AT");//start command
  delay(2000);
  Serial.println("AT+CWMODE=1");//mode selection
  delay(2000);
  Serial.println("AT+CWLAP");
  delay(2000);  delay(2000);  delay(2000);
  //Serial.println("AT+CWJAP=\"epark\",\"dontaskpassword\"\r\n");//setting the internet connection
  Serial.println("AT+CWJAP=\"Vedanth's iPhone\",\"12345678\"\r\n");
  delay(2000);
}
//------------------------------SENDING TO SERVER----------------------------//

void sendtoserver()
{

//  https://www.thingspeak.com/update?api_key=8JDUGG4X06TNUIWY&field1=0.20&field2=4.25&field3=0.42&field4=0.02&field5=0.00&field6=1.80&field7=1.82&field8=50
  String temp = "GET https://184.106.153.149/update?api_key=JF87H7SHAHQREA8B&field1="; //get the api key
  temp += String(sv); //sending the voltge of wind to the server  voltageSensor2
  //  temp+=500;
  temp += "&field2=";
  temp += String(Solarcurrent); //sending the voltge of solar to the server
  temp += "&field3=";
  //  temp+=50;
  temp += String(sol); ////sending the cuurent of wind to the server
  temp += "&field4=";
  temp += String(sol); //sending the current  of solar to the server
  temp += "&field5=";
  temp += String(win);
  temp += "&field6=";
  temp += String(sol);
  temp += "&field7=";
  temp += String(power);
  temp += "\r\n";
  //temp+="\r\n\r\n\r\n";
  Serial.println("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n");//start the sending to server
  delay(2000);
  //Serial.println("AT+CIPSEND=0,"+String(temp.length()));
  Serial.println("AT+CIPSEND=" + String(temp.length())); //sending the string to server
  Serial.println("\r\n");

  //Serial.println("AT+CIPSEND=87\r\n");
  delay(2000);
  Serial.println(temp);
  //Serial.println("GET https://184.106.153.149/update?api_key=9FUQ5PCW9XIL6A2G&field1=70&field2=90\r\n");
  //Serial.print("GET https://184.106.153.149/update?api_key=9FUQ5PCW9XIL6A2G&field1=");
  //Serial.print(temp);
  Serial.print("\r\n");
  delay(2000);
  Serial.println("\r\n\r\n\r\n\r\n\r\n\r\n");
  delay(2000);
  delay(2000);
  // temp='0';

}
//-----------------------------UPLOADING FUNCTION------------------//

void uploading()//uploading funtion
{
  sendtoserver();
  Serial.println("Sending to IOT");
}
