// import servo library
#include <Servo.h>

// setup pin constants for 4 photoresistors
const int upperLeftPhotoresistor = A0;
const int upperRightPhotoresistor = A1;
const int lowerLeftPhotoresistor = A2;
const int lowerRightPhotoresistor = A3;

// setup pin constants for 2 servros
const int verticalServoPin = 9;
const int horizontalServoPin = 10;

// setup servos
Servo verticalServo;
Servo horizontalServo;

// setup servo positions
int verticalServoPosition = 90;
int horizontalServoPosition = 90;

// setup constant servo steps
const int verticalServoStep = 10;
const int horizontalServoStep = 10;

// setup minimum servo positions
const int verticalServoMin = 0;
const int horizontalServoMin = 0;

// setup maximum servo positions
const int verticalServoMax = 180;
const int horizontalServoMax = 180;

// setup servo delay duration
const int servoDelay = 50;

void setup()
{
	Serial.begin(9600);
	Serial.println("Starting...");
	// set photoresistor pins to analog input
	pinMode(upperLeftPhotoresistor, INPUT);
	pinMode(upperRightPhotoresistor, INPUT);
	pinMode(lowerLeftPhotoresistor, INPUT);
	pinMode(lowerRightPhotoresistor, INPUT);

	// set servo pins to output
	pinMode(verticalServoPin, OUTPUT);
	pinMode(horizontalServoPin, OUTPUT);

	// initialize servos
	verticalServo.attach(verticalServoPin);
	horizontalServo.attach(horizontalServoPin);

	// move servos to starting positions
	verticalServo.write(verticalServoPosition);
	horizontalServo.write(horizontalServoPosition);
}

int main()
{
	showDeviations();
}

void showDeviations()
{
	showVerticalDeviation();
	showHorizontalDeviation();
}

void showVerticalDeviation()
{
	moveVerticalServo();
}

void showHorizontalDeviation()
{
	moveHorizontalServo();
}

void setVerticalServoPosition(int position)
{
	// make sure that position is between min and max servo positions
	if (position < verticalServoMin)
	{
		position = verticalServoMin;
	}
	else if (position > verticalServoMax)
	{
		position = verticalServoMax;
	}

	verticalServoPosition = position;
}

void setHorizontalServoPosition(int position)
{
	// make sure that position is between min and max servo positions
	if (position < horizontalServoMin)
	{
		position = horizontalServoMin;
	}
	else if (position > horizontalServoMax)
	{
		position = horizontalServoMax;
	}

	horizontalServoPosition = position;
}

void moveVerticalServo()
{
	calculateVerticalServoPosition();

	verticalServo.write(verticalServoPosition);
}

void moveHorizontalServo()
{
	calculateHorizontalServoPosition();

	horizontalServo.write(horizontalServoPosition);
}

void calculateVerticalServoPosition()
{
	setVerticalServoPosition(getUpperPhotoresistorTotal() > getLowerPhotoresistorTotal() ? verticalServoPosition + verticalServoStep : verticalServoPosition - verticalServoStep);
}

void calculateHorizontalServoPosition()
{
	setHorizontalServoPosition(getLeftPhotoresistorTotal() > getRightPhotoresistorTotal() ? horizontalServoPosition - horizontalServoStep : horizontalServoPosition + horizontalServoStep);
}

// create a function to set vertical servo position based on the difference of the upper and lower photoresistors
void setVerticalServoPosition()
{
	// if the upper photoresistors are greater than the lower photoresistors, then set vertical indicator position higher, else set vertical indicator position lower
	verticalServoPosition = getUpperPhotoresistorTotal() > getLowerPhotoresistorTotal() ? verticalServoPosition + verticalServoStep : verticalServoPosition - verticalServoStep;
}

void setHorizontalServoPosition()
{
	horizontalServoPosition = getLeftPhotoresistorTotal() > getRightPhotoresistorTotal() ? horizontalServoPosition + horizontalServoStep : horizontalServoPosition - horizontalServoStep;
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
