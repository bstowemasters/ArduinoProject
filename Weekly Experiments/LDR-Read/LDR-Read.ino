int PIN = A0; // Saves pin incase it's needed multiple times.

int Resistance = 0; // Stores the value read from the LDR

void setup()
{
  Serial.begin(9600);   // Set serial port
}
void loop()
{
  Resistance = analogRead(PIN); // Read the resistance from the arduinos output Pin
  Serial.println(Resistance);   // Prints the result to the serial monitor.

  // Added delay to make the resistance easier to read.
  delay(100);
}