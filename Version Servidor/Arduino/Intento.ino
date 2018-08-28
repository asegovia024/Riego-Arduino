/*Repeating Web client
 This sketch connects to a a web server and makes a request
 using a Wiznet Ethernet shield. You can use the Arduino Ethernet shield, or
 the Adafruit Ethernet shield, either one will work, as long as it's got
 a Wiznet Ethernet module on board.
 This example uses DNS, by assigning the Ethernet client with a MAC address,
 IP address, and DNS address.
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 created 19 Apr 2012
 by Tom Igoe
 modified 21 Jan 2014
 by Federico Vanzati
 http://www.arduino.cc/en/Tutorial/WebClientRepeating
 This code is in the public domain.
 */
#include <SPI.h>
#include <Ethernet.h>
// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192, 168, 1, 177);
// fill in your Domain Name Server address here:
IPAddress myDns(1, 1, 1, 1);
// initialize the library instance:
EthernetClient client;
char server[] = "localhost/p1ia/add2.php";
EthernetClient client2;
char server2[] = "192.168.1.100/p1ia/acc.php";
//IPAddress server(64,131,82,241);
unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds
unsigned long lastConnectionTime2 = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval2 = 10L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers
int t = 0;  // TEMPERATURE VAR
int h = 0;  // HUMIDITY VAR
String codigo;
String palabra1;
String palabra2;
void setup() {
  // start serial port:
  Serial.begin(9600);
  /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // give the ethernet module time to boot up:
  delay(1000);
  */
  
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip, myDns);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());


/*

    if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
//    client2.println("GET http://www.pandorasoft.com/arduino/index.php?var=100 HTTP/1.0");
  //  client2.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  */
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
/*if (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
*/
  
  
  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }
  if (millis() - lastConnectionTime2 > postingInterval2) {
    escuchaActuador();
  }
}
// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /p1ia/add2.php?temp1=");
    client.println(t);
    client.println("&hum1=");
    client.println(h);
    client.println(" HTTP/1.1");
    client.println("Host: ");
    client.println(server);
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();
    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}
void escuchaActuador(){


  if (client2.available()) {
    char c = client2.read();
    codigo = codigo + c; /// genero el string con el código completo
    //Serial.print(myPins[0]);
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client2.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client2.stop();
    //Serial.print(codigo);

    int posicion1 = codigo.indexOf("<p1>"); /// en la web la primera palabra empieza por <p1> a partir de aquí esta la primera palabra
    int posicion2 = codigo.indexOf("<p2>");/// en la web la segunda palabra empieza por <p2> a partir de aquí esta la segunda palabra
    palabra1 = codigo.substring ( posicion1 + 4, posicion1 + 14 ); // el +4 es porque <p1> no me vale y mostrare a partir de que termine ----- el + catorce es para contar hasta 10 dígitos que no va a contener mas de 10 dígitos
    palabra2 = codigo.substring ( posicion2 + 4, posicion2 + 14 );
      Serial.println(posicion1); // muestra donde empieza la 1 posición
      Serial.println(posicion2); // muestra donde empieza la 2 posición
      Serial.println(palabra1); // ya tengo la primera palabra metida en la variable palabra1
      Serial.println(palabra2); // ya tengo la segunda palabra metida en la variable palabra2
    
   
  }
}

