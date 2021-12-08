// import servo library
#include <Servo.h>

// setup pin constants for 4 photoresistors
const int upperLeftPhotoresistor = A0;
const int upperRightPhotoresistor = A1;
const int lowerLeftPhotoresistor = A2;
const int lowerRightPhotoresistor = A3;

// setup pin constants for 2 servros
const int verticalDeviationIndicatorServoPin = 9;
const int horizontalDeviationIndicatorServoPin = 10;

// setup servos
Servo verticalIndicatorServo;
Servo horizontalIndicatorServo;

// setup servo positions
int verticalIndicatorServoPosition = 90;
int horizontalIndicatorServoPosition = 90;

// setup constant servo steps
const int verticalIndicatorServoStep = 10;
const int horizontalIndicatorServoStep = 10;

// setup minimum servo positions
const int verticalIndicatorServoMin = 0;
const int horizontalIndicatorServoMin = 0;

// setup maximum servo positions
const int verticalIndicatorServoMax = 180;
const int horizontalIndicatorServoMax = 180;

void setup()
{
	// set photoresistor pins to analog input
	pinMode(upperLeftPhotoresistor, INPUT);
	pinMode(upperRightPhotoresistor, INPUT);
	pinMode(lowerLeftPhotoresistor, INPUT);
	pinMode(lowerRightPhotoresistor, INPUT);

	// initialize servos
	verticalIndicatorServo.attach(verticalDeviationIndicatorServoPin);
	horizontalIndicatorServo.attach(horizontalDeviationIndicatorServoPin);

	// move servos to starting positions
	verticalIndicatorServo.write(verticalIndicatorServoPosition);
	horizontalIndicatorServo.write(horizontalIndicatorServoPosition);
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
	moveVerticalIndicatorServo();
}

void setVerticalIndicatorServoPosition(int position)
{
	// make sure that position is between min and max servo positions
	if (position < verticalIndicatorServoMin)
	{
		position = verticalIndicatorServoMin;
	}
	else if (position > verticalIndicatorServoMax)
	{
		position = verticalIndicatorServoMax;
	}

	verticalIndicatorServoPosition = position;
}

void showHorizontalDeviation()
{
	moveHorizontalIndicatorServo();
}

void setHorizontalIndicatorServoPosition(int position)
{
	// make sure that position is between min and max servo positions
	if (position < horizontalIndicatorServoMin)
	{
		position = horizontalIndicatorServoMin;
	}
	else if (position > horizontalIndicatorServoMax)
	{
		position = horizontalIndicatorServoMax;
	}

	horizontalIndicatorServoPosition = position;
}

void moveVerticalIndicatorServo()
{
	calculateVerticalIndicatorServoPosition();

	verticalIndicatorServo.write(verticalIndicatorServoPosition);
}

void calculateVerticalIndicatorServoPosition()
{
	setVerticalIndicatorServoPosition(getUpperPhotoresistorTotal() > getLowerPhotoresistorTotal() ? verticalIndicatorServoPosition + verticalIndicatorServoStep : verticalIndicatorServoPosition - verticalIndicatorServoStep);
}

void moveHorizontalIndicatorServo()
{
	calculateHorizontalIndicatorServoPosition();

	horizontalIndicatorServo.write(horizontalIndicatorServoPosition);
}

void calculateHorizontalIndicatorServoPosition()
{
	setHorizontalIndicatorServoPosition(getLeftPhotoresistorTotal() > getRightPhotoresistorTotal() ? horizontalIndicatorServoPosition - horizontalIndicatorServoStep : horizontalIndicatorServoPosition + horizontalIndicatorServoStep);
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
