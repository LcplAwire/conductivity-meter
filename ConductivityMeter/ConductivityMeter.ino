#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define A_PIN 0
#define TdsSensorPin 8
#define TdsButton 1
#define VREF 5.0      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point

int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;
int buttonState = 0;
int TDSDisplay = 0;
// Replace 0x27 with whatever your scanner reported
LiquidCrystal_I2C lcd(0x27, 16, 3);

void setup() {
  Serial.begin(115200);
  
  pinMode(TdsSensorPin,INPUT);

  pinMode(TdsButton,INPUT);

  delay(500);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello!");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);

  Serial.print("\n\n\n\n\n\n\n\n");
}

void loop()
{
  buttonState = digitalRead(TdsButton);

  if (buttonState == LOW)   // Button pressed (active LOW)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Measuring...");
    Serial.println("Button pressed → starting measurement");

    unsigned long startTime = millis();
    unsigned long duration = 10000;  // measure for 10 seconds

    // reset buffer index
    analogBufferIndex = 0;

    while (millis() - startTime < duration)
    {
      // collect analog samples every 40 ms
      static unsigned long sampleTime = millis();
      if (millis() - sampleTime > 40U)
      {
        sampleTime = millis();
        analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);
        analogBufferIndex++;
        if (analogBufferIndex == SCOUNT)
          analogBufferIndex = 0;
      }
    }

    // After sampling for 10 seconds, process data
    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];

    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0;
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
    float compensationVoltage = averageVoltage / compensationCoefficient;
    tdsValue = (133.42 * pow(compensationVoltage, 3)
              - 255.86 * pow(compensationVoltage, 2)
              + 857.39 * compensationVoltage) * 0.5;

    float f = 0.5;  // conversion factor
    float conductivity = tdsValue / f;

    // Display results
    Serial.print("Voltage: "); Serial.print(averageVoltage, 2);
    Serial.print(" V  TDS: "); Serial.print(tdsValue, 0);
    Serial.print(" ppm  Conductivity: "); Serial.print(conductivity, 0);
    Serial.println(" uS/cm");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printf("TDS: %d ppm", (int)tdsValue);
    lcd.setCursor(0, 1);
    lcd.printf("Cond: %d uS/cm", (int)conductivity);

    delay(2000);  // hold reading for 2 seconds

    // Wait for button release before next reading
    while (digitalRead(TdsButton) == LOW);
    delay(300);
  }
}


int getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
	  bTab[i] = bArray[i];
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
	  for (i = 0; i < iFilterLen - j - 1; i++) 
          {
	    if (bTab[i] > bTab[i + 1]) 
            {
		bTemp = bTab[i];
	        bTab[i] = bTab[i + 1];
		bTab[i + 1] = bTemp;
	     }
	  }
      }
      if ((iFilterLen & 1) > 0)
	bTemp = bTab[(iFilterLen - 1) / 2];
      else
	bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}