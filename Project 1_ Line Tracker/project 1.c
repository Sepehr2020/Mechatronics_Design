task main()
{
//	int MotorLeft = motorA;
//	int MotorRight = motorD;

//	setMotorSpeed(motorA, 2);
//  setMotorSpeed(motorD, 4);

  while (true)
  	{
  		setMotorSpeed(motorC, -5);
      	displayBigTextLine(3, "ROBOT AAS 2.6");
      	displayBigTextLine(7, "LINE FOLLOWER");
  		if (getColorReflected(S1)>1 && getColorReflected(S1)<30)
			{
  				setMotorSpeed(motorA, 45);  //Sees black and takes a sharp turn-BLACK
      			setMotorSpeed(motorD,0);
    		}
   	 	else
    		{
    			setMotorSpeed(motorA, 1);   //doesn't see it, takes a counter clockwise curve-GREY
  				setMotorSpeed(motorD, 25);
  			}


  	if (getUSDistance(S4)<5)  //when its close to the object
  		{
  			playTone(300, 100);
  			displayBigTextLine(3, "OBSTRUCTION");
      		displayBigTextLine(7, "AHEAD!!!!");
  			setMotorSpeed(motorA, 0);
      		setMotorSpeed(motorD, 0);
      		delay(1000);
			setMotorSpeed(motorC, 30);
			delay(1000);
			setMotorSpeed(motorA, 20);
      		setMotorSpeed(motorD, -20);
     	 	delay(1000);
     	 	setMotorSpeed(motorA, 0);
      		setMotorSpeed(motorD, 0);
      		delay(300);
     	 	setMotorSpeed(motorA, 40);
     	 	setMotorSpeed(motorD, 40);
     		delay(500);
     	 	setMotorSpeed(motorA, 0);
     	 	setMotorSpeed(motorD, 0);
     		delay(1000);
     		
      	setMotorSpeed(motorC, -30);
      	delay(1000);
      	setMotorSpeed(motorA, 0);
      	setMotorSpeed(motorD, 0);
      	delay(300);
      	setMotorSpeed(motorA, -40);
      	setMotorSpeed(motorD, -40);
      	delay(500);
      	setMotorSpeed(motorA, 0);
      	setMotorSpeed(motorD, 0);
      	delay(300);
      	setMotorSpeed(motorA, -19);
      	setMotorSpeed(motorD, 17);
      	delay(1000);
      	setMotorSpeed(motorA, 0);
      	setMotorSpeed(motorD, 0);
      	delay(100);
      	playTone(100, 50);
    	playTone(500, 50);
    	
      	displayBigTextLine(3, "MISSION ");
    		displayBigTextLine(7, "ACCOMPLISHED!!!");
    		delay(1000);
    		
    	}
  	}

}