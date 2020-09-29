#pragma config(Sensor, S1,     R,              sensorEV3_Touch)
#pragma config(Sensor, S2,     L,              sensorEV3_Touch)
#pragma config(Sensor, S4,     Colour,         sensorEV3_Color, modeEV3Color_Color)



task main()
{
	while(true)
	{


				while(SensorValue[Colour]!=6 && SensorValue[R]==0 && SensorValue[L]==0 && getUSDistance(S3)>50)			//moving forward when the robot is in the circle
					{

            setLEDColor(ledGreenPulse);
						setMotorSpeed(motorA, -50);
			      setMotorSpeed(motorD, -50);
			      resetMotorEncoder(motorA);
            resetMotorEncoder(motorD);
			    }

   			if(SensorValue[Colour]==6)		//Light Sensor detecting white color on the sides [last code was >10 which also includs yellow tapes]
								{
											setLEDColor(ledGreenFlash);
											playTone(100, 10);
											resetMotorEncoder(motorA);
                      resetMotorEncoder(motorD);
											setMotorTarget(motorA, 200, 100);//back up
		  								setMotorTarget(motorD, 200, 100);
 											waitUntilMotorStop(motorA);
											waitUntilMotorStop(motorD);

											resetMotorEncoder(motorA);
                      resetMotorEncoder(motorD);
											setMotorTarget(motorA, 1125, 100); //180 degree turn
		  								setMotorTarget(motorD, -1125, 100);
 											waitUntilMotorStop(motorA);
											waitUntilMotorStop(motorD);
						   	}

   			while (SensorValue[R]==1 || SensorValue[L]==1 )		//Touch sensor- stoping at border line- important if statment for not falling off- Should be in every condition
						   	{

						   				setLEDColor(ledRedPulse);
											setMotorSpeed(motorA, 100);
			      					setMotorSpeed(motorD, 100);
			      					resetMotorEncoder(motorA);
            					resetMotorEncoder(motorD);
						   	}





   	//detecting the other robot and moving towards
   	if(getUSDistance(S3)<60 && SensorValue[Colour]!=6 )	//if you see the enemey
   	{
							setLEDColor(ledOrangeFlash);
              playTone(1000, 10);
   						resetMotorEncoder(motorA);
              resetMotorEncoder(motorD);
              setMotorTarget(motorA, -100, 100);
		  				setMotorTarget(motorD, -100, 100);
							waitUntilMotorStop(motorA);
							waitUntilMotorStop(motorD);


      	while(getUSDistance(S3)<40 && SensorValue[Colour]!=6)		//if you still see the enemey
					{
						setLEDColor(ledRedFlash);
						setMotorSpeed(motorA, -100);
			     	setMotorSpeed(motorD, -100);
			     	resetMotorEncoder(motorA);
            resetMotorEncoder(motorD);
					}

			}
	}
}
