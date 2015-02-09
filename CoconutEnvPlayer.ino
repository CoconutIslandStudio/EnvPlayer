
#include <MP3.h>
#include <SoftwareSerial.h>

/** define mp3 class */
MP3 mp3(true);
int buttonRed = 13;
int buttonGreen = 3;
int buttonYellow = 4;
int buttonBlue = 5;
int buttonWhite = 6;
char tcpbuffer[64];
int bufferlen = 64;

void setup()
{
  /** begin function */
  mp3.begin();
  /** set volum to the MAX */
  mp3.volume(0x1F);
  /** set MP3 Shield CYCLE mode */
  mp3.set_mode(MP3::SINGLE);
  
  //stop all first
  mp3.stop();
  digitalWrite(buttonRed,HIGH);
  digitalWrite(buttonGreen,HIGH);
  digitalWrite(buttonYellow,HIGH);
  digitalWrite(buttonBlue,HIGH);
  digitalWrite(buttonWhite,HIGH);
  /** play music in USB-disk */ 
  //mp3.play_usb_disk(0x0001);
  
  /** play music in SPI FLASH */ 
  mp3.play_spi_flash(0x0003);
  
  //wifi shield
  Serial1.begin(115200);
  Serial.begin(115200);
}

void loop()
{
  /** function code here */
  
  int RedTcp = HIGH;
  int GreenTcp = HIGH;
  int YellowTcp = HIGH;
  int BlueTcp = HIGH;
  int WhiteTcp = HIGH;
  
  if(Serial1.available() > 0)
  {
    for(int i=0; i<bufferlen; i++)
      tcpbuffer[i] = 0;
    
    int reallen = Serial1.readBytes(tcpbuffer, 64);
    Serial.write(tcpbuffer, reallen);
    //outup bytes to console window
    if(strcmp(tcpbuffer, "RedButton") == 0)
    {
      Serial.write("Tcp:Red Button");
      RedTcp = LOW;
    }
    
    if(strcmp(tcpbuffer, "GreenButton") == 0)
    {
      Serial.write("Tcp:Green Button");
      GreenTcp = LOW;
    }   

    if(strcmp(tcpbuffer, "YellowButton") == 0)
    {
      Serial.write("Tcp:Yellow Button");
      YellowTcp = LOW;
    }   
    
    if(strcmp(tcpbuffer, "BlueButton") == 0)
    {
      Serial.write("Tcp:Blue Button");
      BlueTcp = LOW;
    }   
    
    if(strcmp(tcpbuffer, "WhiteButton") == 0)
    {
      Serial.write("Tcp:White Button");
      WhiteTcp = LOW;
    }   
    
  }
  /** play music in sd */
  int RedValue = digitalRead(buttonRed);
  int GreenValue = digitalRead(buttonGreen);
  int YellowValue = digitalRead(buttonYellow);
  int BlueValue = digitalRead(buttonBlue);
  int WhiteValue = digitalRead(buttonWhite);
  
  if(RedValue == LOW || RedTcp == LOW)
  {
    mp3.stop();
  }
  
  if(GreenValue == LOW || GreenTcp == LOW)
  {
    mp3.play_spi_flash(0x0002);
  }

  if(YellowValue == LOW || YellowTcp == LOW)
  {
    mp3.play_spi_flash(0x0001);
  }
 
  if(BlueValue == LOW || BlueTcp == LOW)
  {
    mp3.play_spi_flash(0x0004);
  }
 
  if(WhiteValue == LOW || WhiteTcp == LOW)
  {
    mp3.play_spi_flash(0x0005);
  }
  
  
}
