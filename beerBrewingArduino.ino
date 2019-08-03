
#include <Wire.h>
#include <LiquidCrystal.h>
#include <math.h>







#define I2C_ADDR  0x20

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);// 0x20 is the address with all jumpers removed
int valC;

float currentTemp, setpoint = 20, hysteresis = 18;

boolean heating;




double ThermistorC(int RawADC)
{
	double Temp;
	Temp = log(10000.0*((1024.0 / RawADC - 1)));
	Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp))* Temp);
	Temp = Temp - 273.15;
	return Temp;
}

void sendValueToLatch(int latchValue)
{
	Wire.beginTransmission(I2C_ADDR);
	Wire.write(0x12);        // Select GPIOA
	Wire.write(latchValue);  // Send value to bank A
	Wire.endTransmission();
}


void setup()
{
	

	

	Wire.begin(); // Wake up I2C bus

				  // Set I/O bank A to outputs
	Wire.beginTransmission(I2C_ADDR);
	lcd.begin(16, 2);
	Wire.write(0x00); // IODIRA register
	Wire.write(0x00); // Set all of bank A to outputs
	Wire.endTransmission();
	heating = false;

}

void loop()
{
	
	
	valC = analogRead(1);
	currentTemp = ThermistorC(valC);
	

	int command = 0;
	delay(500);

	
		
		if (currentTemp <= hysteresis)
		{
			//lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Temp ");
			lcd.print(currentTemp, 2);
			lcd.setCursor(0, 1);
			lcd.print("Heater on ");
			sendValueToLatch(1);//heater on	
			heating = true;
		}

		else if (heating == true && currentTemp <= setpoint)
		{
			//lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Temp ");
			lcd.print(currentTemp, 2);
			lcd.setCursor(0, 1);
			lcd.print("Heater on ");
			sendValueToLatch(1);//heater on	

		}

		else if (currentTemp >= setpoint)
		{
			//lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("Temp ");
			lcd.print(currentTemp, 2);
			lcd.setCursor(0, 1);
			lcd.print("Heater off ");
			sendValueToLatch(0);//heater off
			heating = false;
		}

		else
		{
			if (heating == true)
			{
				lcd.setCursor(0, 0);
				lcd.print("Temp ");
				lcd.print(currentTemp, 2);
				lcd.setCursor(0, 1);
				lcd.print("Heater on ");

			}
			if (heating == false)
			{
				lcd.setCursor(0, 0);
				lcd.print("Temp ");
				lcd.print(currentTemp, 2);
				lcd.setCursor(0, 1);
				lcd.print("Heater off");
			}
		}
		
		
		
		
	
}











