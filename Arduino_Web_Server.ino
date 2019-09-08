//Code Written By RAJDEEP BARUAH

#include <SPI.h>
#include <Ethernet.h>



byte mac[] = {
  0x48, 0xC2, 0xA1, 0xF3, 0x8D, 0xB7};
byte ip[] = {169,254,239,99};

EthernetServer server = EthernetServer(80);

void setup()
{
  Serial.begin(9600);
  
  Ethernet.begin(mac, ip);
  server.begin();

  pinMode(2,INPUT);
  
}

void loop() 
{

  int val=digitalRead(2);
  Serial.println(val);
  delay(100);
 
  EthernetClient client = server.available();
  if(client)
  {
    boolean BlankLine = true;
    while(client.connected())
    {
      if(client.available())
      {
        char c = client.read();

        if(c == '\n' && BlankLine)
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html\n");
          client.println("<html><head><META HTTP-EQUIV=""refresh"" CONTENT=""1"">\n");
          client.println("<title>RAILWAY SERVER ROOM</title></head>");
          client.println("<body style=\"background-color:#5EA084\">\n");
          client.println("<h1>RAILWAY SERVER ROOM</h1>");
          client.println("<h3>SENSOR LEVELS</h3>");

          if(val==0)
          {
          client.println("<h5>TRAIN COMING</h5>");
          }
          else if(val==1)
          {                           
          client.println("<h5>TRACK CLEAR</h5>");          
          }                 
         
          break;
        }
        if(c == '\n')
        {
          BlankLine = true;
        }
        else if(c != '\r')
        {
          BlankLine = false;
        }
      }
    }
    delay(10);
    client.stop();
  }
}
