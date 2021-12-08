// setup pin constants for 4 photoresistors
const int upperLeftPhotoresistor = A0;
const int upperRightPhotoresistor = A1;
const int lowerLeftPhotoresistor = A2;
const int lowerRightPhotoresistor = A3;

// setup pin constants for 2 servros
const int verticalIndicatorServoPin = 9;
const int horizontalIndicatorServoPin = 10;

// import servo library
#include <Servo.h>

// setup servos
Servo verticalIndicatorServo;
Servo horizontalIndicatorServo;

// setup servo positions
int verticalIndicatorServoPosition = 90;
int horizontalIndicatorServoPosition = 90;

// setup constant servo steps
const int verticalIndicatorServoStep = 10;
const int horizontalIndicatorServoStep = 10;

void setup()
{
	// set photoresistor pins to analog input
	pinMode(upperLeftPhotoresistor, INPUT);
	pinMode(upperRightPhotoresistor, INPUT);
	pinMode(lowerLeftPhotoresistor, INPUT);
	pinMode(lowerRightPhotoresistor, INPUT);

	// initialize servos
	verticalIndicatorServo.attach(verticalIndicatorServoPin);
	horizontalIndicatorServo.attach(horizontalIndicatorServoPin);

	// move servos to starting positions
	verticalIndicatorServo.write(verticalIndicatorServoPosition);
	horizontalIndicatorServo.write(horizontalIndicatorServoPosition);
}

void main()
{
	setVerticalIndicatorServoPosition();
	setHorizontalIndicatorServoPosition();
	indicateDeviations();
	delay(1000);
}

// create a function to set vertical servo position based on the difference of the upper and lower photoresistors
void setVerticalIndicatorServoPosition()
{
	// if the upper photoresistors are greater than the lower photoresistors, then set vertical indicator position higher, else set vertical indicator position lower
	verticalIndicatorServoPosition = getUpperPhotoresistorTotal() > getLowerPhotoresistorTotal() ? verticalIndicatorServoPosition + verticalIndicatorServoStep : verticalIndicatorServoPosition - verticalIndicatorServoStep;
}

void setHorizontalIndicatorServoPosition()
{
	horizontalIndicatorServoPosition = getLeftPhotoresistorTotal() > getRightPhotoresistorTotal() ? horizontalIndicatorServoPosition + horizontalIndicatorServoStep : horizontalIndicatorServoPosition - horizontalIndicatorServoStep;
}

void indicateDeviations()
{
	// move servos to new positions
	verticalIndicatorServo.write(verticalIndicatorServoPosition);
	horizontalIndicatorServo.write(horizontalIndicatorServoPosition);
}

// create a function to get the total of the upper photoresistors
int getUpperPhotoresistorTotal()
{
	return analogRead(upperLeftPhotoresistor) + analogRead(upperRightPhotoresistor);
}

// create a function to get the total of the lower photoresistors
int getLowerPhotoresistorTotal()
{
	return analogRead(lowerLeftPhotoresistor) + analogRead(lowerRightPhotoresistor);
}

int getLeftPhotoresistorTotal()
{
	return analogRead(upperLeftPhotoresistor) + analogRead(lowerLeftPhotoresistor);
}

int getRightPhotoresistorTotal()
{
	return analogRead(upperRightPhotoresistor) + analogRead(lowerRightPhotoresistor);
}
