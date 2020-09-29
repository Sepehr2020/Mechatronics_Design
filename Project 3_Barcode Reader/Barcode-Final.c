//#pragma config(Sensor, S3,     Colour,         sensorEV3_Color, modeEV3Color_Reflected)


task main()
{

int ColorData = 0;//initialize value for color's data

resetMotorEncoder(motorA);
int encoder = getMotorEncoder(motorA);


	while(getMotorEncoder(motorA)<=5400)//Move until we reach 5400 degrees (which with our gear ratios it is after half of the circle)
		{
			datalogDataGroupStart();//coloct data
			setMotorSpeed(motorA, 80);
		  int ColorData =  getColorReflected(S3);//get datas from the color sensor
		  datalogAddValue(1, ColorData);//save the data on computer
			datalogDataGroupEnd();//end data collecting
		}
  setMotorTarget(motorA, 0, 100);//Go back to where you start, so it's ready for next data collecting
  waitUntilMotorStop(motorA);

}
