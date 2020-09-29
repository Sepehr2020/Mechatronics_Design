//FINAL CODE 1736.072919
const int ScreenHeight =127;
const int ScreenWidth  =177;

typedef struct{//define walls of each cell
int NorthWall;
int EastWall;
int SouthWall;
int WestWall;
}Cell;

Cell Grid[4][6];//make two dimension array for maze map

// Start Facing North
int RobotDirection=0; // 0=North, 1=East, 2=South, 3=West
int count=0;//global variable bacause is used in gofwd function and in simulation
const int size=300;//global variable because its used as size of all our arrays
int MyLocArr[size];
int ShortestPath[size];
int InstantanousDirection[size+1];

int w=0;

// Start in the 0,0 Cell
int StartPosRow=3;//sarting position
int StartPosCol=5;

int CurrentPosRow=StartPosRow; //Set current position to Starting position at the beginning
int CurrentPosCol=StartPosCol;

//GIVE THE CELL OF BASKETS***********************************************RGBW***************************************************************
int TargetPosRow[10]={3,1,2,3,3,1,2,3,3,1};//Location of where we wanna get to (ie baskets coordinates)
int TargetPosCol[10]={2,5,0,3,2,5,0,3,2,5};


void GridInit();//Just make a grid of 4X6 matrix (set all cells with no walls)
void WallGen();//Sets up all walls
void GridDraw();//Display basically
void DrawBot();//Display
void DisplayStartandEnd();//Display

void GoFwd();//updates current pos as we move
void TurnLeft();//updates compass' number as we turn
void TurnRight();//same as left!

//functions we wrote:
void TakeActions();//Will move the robot "physically" through the maze
void EliminatingTwo();//Goes through the array of directions and eliminates difference of two (ie. 3 and 1 OR 2 and 0)
void CleanItUp();//Gets rid off all extra -10 in MyLocArr and saves it in ShoertestPath array. So we have an array to follow in TakeAction function
void GoStraight();//moves the robot straight (also before going straight go back to reallign yourself with wall behind)
void TurningRight();//Turn robot right
void TurningLeft();
void TurnAround();//Turn robot around
void DropBall();//drop the ball when you reach the basket
void GoStraightNoErrorFix();//when there's no wall behind us, just go straight and dont go back for realligning


int Solver();//check Right-Front-Left-Back for walls and if there is no wall it goes that direction
int CheckWall();//checks if there is a wall depending on the direction you face, by comparing to walls asigned before


task main(){
GridInit();
WallGen();

int k=0;

for (k=0; k<size; k++){//initialize array to arbiterary number other than 0,1,2, and 3
 MyLocArr[k]=-10;
}

for(int t=0; t<(size+1); t++){//initialize array to arbiterary number other than 0,1,2, and 3
	InstantanousDirection[t]=-50;
}

for(int f=0; f<size; f++){//initialize array to arbiterary number other than 0,1,2, and 3
	ShortestPath[f]=-70;
}
//_____________________________________START SIMULATION___________________________________________

for(w=0; w<6; w++){//this loop is for simulating and will go through our basket coordinates for as many number as we want for example in here we doing 6 baskets)
	//the reason we chose 6 is because of time limitation

		while( (CurrentPosRow!=TargetPosRow[w]) || (CurrentPosCol!=TargetPosCol[w])){//keep doing right wall follower algorithm till you arrive to basket
				Solver();//turns around until can move to next cell
				GridDraw();
				DisplayStartandEnd();
				DrawBot();
				sleep(50);
				eraseDisplay();
		}

		count=count+2;//if your only path to basket is already shortest path, the MyLocArr will not give us any -10 values between two baskets.
		//That will be a problem because you want a -10 that indicates you are before the basket.
		//So we decided to move the index after each basket simulation to avoid that possible situation.


		//Eliminating Difference of Two
		EliminatingTwo();
		CleanItUp();//fill up ShortestPath array and get rid off extra -10

		//copy ShortestPath in INstantanousDirection (since they arrays are the same)
		int u=1;//start copying from second element

		for (int v=0; v<size; v++){
			InstantanousDirection[u]=ShortestPath[v];
			u++;
		}
		//Also, because all elements are -50, change first one to starting direction (ie zero in our case. because we start facing North)
		InstantanousDirection[0]=0;

		while(true){//Display Maze Solved after each time you reach baskets in simulation
			displayCenteredTextLine(5,"MAZE SOLVED !!");
			sleep(250);
			eraseDisplay();
			sleep(250);
			break;
		}

		//Since we started to fill InstantanousDirection from the second element, we need to shift everything up so it matches with where we want it to turn
		//if we dont do this the -10 in SHortestPath and InstantanousDirection will not be synced
		for(int q=0; q<size; q++){
			if (InstantanousDirection[q+1]==-10){//if next one is -10: swap this elememt's value with next element's value
				int temp=InstantanousDirection[q];
				InstantanousDirection[q]=-10;
				InstantanousDirection[q+1]=temp;
			}
		}

}//________________________________END OF SIMULATION_____________________________


//Start to move the robot:


	TakeActions();
	playTone(300, 200);//after maze is solved, make the noise


}//_____________________________________END OF MAIN_________________________________





//=====================================================================
void GridInit(){
for(int i=0;i<4;i++){
for(int j=0;j<6;j++){
Grid[i][j].NorthWall=0;
Grid[i][j].EastWall=0;
Grid[i][j].WestWall=0;
Grid[i][j].SouthWall=0;
}
}
}
//=====================================================================
void WallGen(){
int i=0;
int j=0;

for(i=0;i<4;i++){
Grid[i][0].WestWall=1;//close left side of square
Grid[i][5].EastWall=1;//close right side of square
}

for(j=0;j<6;j++){
Grid[0][j].SouthWall=1;//close bottom of the squaere
Grid[3][j].NorthWall=1;//close top of the square
}

//hard code the maze's walls
Grid[0][0].NorthWall =1; Grid[1][0].SouthWall =1;
Grid[1][1].NorthWall =1;  Grid[2][1].SouthWall =1;
Grid[0][1].EastWall =1;   Grid[0][2].WestWall =1;
Grid[1][2].EastWall =1;   Grid[1][3].WestWall =1;
Grid[0][2].EastWall =1; Grid[0][3].WestWall =1;
Grid[1][3].EastWall =1;	Grid[1][4].WestWall =1;
Grid[0][3].EastWall =1; Grid[0][4].WestWall =1;
Grid[1][4].EastWall =1; Grid[1][5].WestWall =1;
Grid[1][5].SouthWall =1;  Grid[0][5].NorthWall =1;
Grid[2][0].NorthWall =1; Grid[3][0].SouthWall =1;
Grid[2][0].EastWall =1;   Grid[2][1].WestWall =1;
Grid[3][2].EastWall =1;   Grid[3][3].WestWall =1;
Grid[3][3].EastWall =1;   Grid[3][4].WestWall =1;
Grid[3][5].SouthWall =1;  Grid[2][5].NorthWall =1;
Grid[3][2].SouthWall =1;  Grid[2][2].NorthWall =1;


}

//=====================================================================
void GridDraw(){
int XStart=0;
int YStart=0;
int XEnd  =0;
int YEnd  =0;
for(int i=0;i<4;i++){
for(int j=0;j<6;j++){
if(Grid[i][j].NorthWall==1){
XStart= j   *ScreenWidth/6;
YStart=(i+1)*ScreenHeight/4;
XEnd  =(j+1)*ScreenWidth/6;
YEnd  =(i+1)*ScreenHeight/4;
drawLine(XStart,YStart,XEnd,YEnd);
}
if (Grid[i][j].EastWall==1){
XStart=(j+1)*ScreenWidth/6;
YStart=(i)*ScreenHeight/4;
XEnd  =(j+1)*ScreenWidth/6;
YEnd  =(i+1)*ScreenHeight/4;
drawLine(XStart,YStart,XEnd,YEnd);
}
if (Grid[i][j].WestWall==1){
XStart= j   *ScreenWidth/6;
YStart=(i)*ScreenHeight/4;
XEnd  =(j)*ScreenWidth/6;
YEnd  =(i+1)*ScreenHeight/4;
drawLine(XStart,YStart,XEnd,YEnd);
}
if(Grid[i][j].SouthWall==1){
XStart= j   *ScreenWidth/6;
YStart=(i)*ScreenHeight/4;
XEnd  =(j+1)*ScreenWidth/6;
YEnd  =(i)*ScreenHeight/4;
drawLine(XStart,YStart,XEnd,YEnd);
}
}
}
}
//=====================================================================
void TurnRight(){
RobotDirection++;
if(RobotDirection==4){
RobotDirection=0;
}
}
//=====================================================================
void TurnLeft(){
RobotDirection--;
if(RobotDirection==-1){
RobotDirection=3;
}
}
//=====================================================================
void GoFwd(){
//This function has been called in solver function, and as goes forward in different directions, it increements the position coordinates depending on which direction has been moved.

MyLocArr[count]=RobotDirection;	//COLLECT ALL DATAS OF WHERE WE HAVE BEEN IN THE SIMULATION (the RobotDirection is being updated by TuernLeft and TurnRight functions)
//so unless we turn our robot is facing the same, and depending on which way we turn our direction changes.
count++;//move the index for next element

switch(RobotDirection){
case 0: CurrentPosRow++; break; // Facing North
case 1: CurrentPosCol++; break; // Facing East
case 2: CurrentPosRow--; break; // Facing South
case 3: CurrentPosCol--; break; // Facing West
default: break;
}
}
//=====================================================================
void DrawBot(){
int RobotXpixelPos=0;
int RobotYpixelPos=0;

if(CurrentPosCol==0){
RobotXpixelPos=ScreenWidth/12;
}
else{
RobotXpixelPos=(2*CurrentPosCol+1)*ScreenWidth/12;
}

if(CurrentPosRow==0){
RobotYpixelPos=ScreenHeight/8;
}
else{
RobotYpixelPos=(2*CurrentPosRow+1)*ScreenHeight/8;
}

switch(RobotDirection){
case 0: displayStringAt(RobotXpixelPos,RobotYpixelPos,"^");	break; // Facing North
case 1: displayStringAt(RobotXpixelPos,RobotYpixelPos,">"); break; // Facing East
case 2: displayStringAt(RobotXpixelPos,RobotYpixelPos,"V"); break; // Facing South
case 3: displayStringAt(RobotXpixelPos,RobotYpixelPos,"<"); break; // Facing West
default: break;
}
}
//=====================================================================
int Solver(){
TurnRight();
if(CheckWall()==0){
GoFwd();
return 0; // exit the Solver function
}
TurnLeft();
if(CheckWall()==0){
GoFwd();
return 0; // exit the Solver function
}
TurnLeft();
if(CheckWall()==0){
GoFwd();
return 0; // exit the Solver function
}
TurnLeft();
if(CheckWall()==0){
GoFwd();
return 0; // exit the Solver function
}
return -1; // Should never arrive here
}

//=====================================================================
int CheckWall(){
int WallStatus=0; // 0 = No Wall, 1= Wall

switch(RobotDirection){
case 0:
if(Grid[CurrentPosRow][CurrentPosCol].NorthWall==1){
WallStatus=1;
}
else{
WallStatus=0; // exit the CheckWall function, Indicate Wall
}
break;
case 1:
if(Grid[CurrentPosRow][CurrentPosCol].EastWall==1){
WallStatus=1;
}
else{
WallStatus=0; // exit the CheckWall function, Indicate Wall
}
break;
case 2:
if(Grid[CurrentPosRow][CurrentPosCol].SouthWall==1){
WallStatus=1;
}
else{
WallStatus=0; // exit the CheckWall function, Indicate Wall
}
break;
case 3:
if(Grid[CurrentPosRow][CurrentPosCol].WestWall==1){
WallStatus=1;
}
else{
WallStatus=0; // exit the CheckWall function, Indicate Wall
}
break;
default: break;
}
return WallStatus;
}
//=====================================================================
void DisplayStartandEnd(){
int XpixelPos=0;
int YpixelPos=0;

if(StartPosCol==0){
XpixelPos=ScreenWidth/12;
}
else{
XpixelPos=(2*StartPosCol+1)*ScreenWidth/12;
}

if(StartPosRow==0){
YpixelPos=ScreenHeight/8;
}
else{
YpixelPos=(2*StartPosRow+1)*ScreenHeight/8;
}
displayStringAt(XpixelPos,YpixelPos,"S");

if(TargetPosCol[w]==0){
XpixelPos=ScreenWidth/12;
}
else{
XpixelPos=(2*TargetPosCol[w]+1)*ScreenWidth/12;
}

if(TargetPosRow[w]==0){
YpixelPos=ScreenHeight/8;
}
else{
YpixelPos=(2*TargetPosRow[w]+1)*ScreenHeight/8;
}
displayStringAt(XpixelPos,YpixelPos,"E");
}
//======================================================================
void EliminatingTwo(){

	 	int z=0;
	for (z=0; z<size-1; z++){//go through MyLocArr
			//(using "size" is better standard in coding because you only need to change one number at the top of the code instead of going through code and change numbers)
		if (abs(MyLocArr[z]-MyLocArr[z+1])==2){//if there's two numbers with different of two:
				for (int b=z; b<size-2; b++){//Make elements with difference of two equal -10.
				MyLocArr[b]=MyLocArr[b+2];//Take those elements, and push all elements two index up; so we have the path continously without any difference of two.
				//And check if there's a differnece of 2 ahead.
				}
		z=0;//Then start searching for nex difference of 2 from beginning of the array (This will make sure we have not created a difference of 2 after we eliminated
		}
	}
}
//======================================================================
void CleanItUp(){//we want to go through MyLocArr and eliminate all -10 except one of them (because that will show we have reached the basket)
int a=0;
int b=0;//start from first element of ShortestPath

	for(a=0; a<size; a++)//go througfh MyLocArr
		if(MyLocArr[a]!=-10){//if the values are not -10, just take them
			ShortestPath[b]=MyLocArr[a];
			b++;//increement the index to save the next element in ShortestPath

		}else{//if you reach -10
			if(MyLocArr[a-1]==-10 && MyLocArr[a-2]!=-10){//pick the SECOND time you reach a -10 and do not take any other -10.
				//example MyLocArr={2,-10,-10,-10,-10,3,2,1,...} ===> ShortestPath={2,-10,3,2,1}
			ShortestPath[b]=MyLocArr[a];//will add -10 to ShortestPath
			b++;//increement the index to save the next element in ShortestPath
		}
	}
}
//======================================================================
void GoStraight(){//each time we turn, we have to also move ahead. Because we want to go to next cell!!

	resetMotorEncoder(motorA);//first go back to reallign ourself with wall
	resetMotorEncoder(motorD);
	moveMotorTarget(motorA, 182, -30);
	moveMotorTarget(motorD, 182, -30);
	waitUntilMotorStop(motorA);
	waitUntilMotorStop(motorD);
	wait1Msec(250);

	resetMotorEncoder(motorA);//Now go forward for specific encoder value that will end up at the CENTER of next cell (this encoder value has been calculated depending to the dimension of the cell)
	resetMotorEncoder(motorD);
	moveMotorTarget(motorA, 845, 38);//encoder value from end of one cell to center of next cell
	moveMotorTarget(motorD, 844, 38);
	waitUntilMotorStop(motorA);
	waitUntilMotorStop(motorD);
	wait10Msec(50);//wait for moment of inertia to stabilaze, otherwise we fall
}
//=================================================================
void GoStraightNoErrorFix(){//If we going to go straight for several times without turning, we do not need to go back and reallign because THERE IS NO WALL BEHIND US.

	resetMotorEncoder(motorA);//Just go straight from center of one cell to center of another cell.
	resetMotorEncoder(motorD);
	moveMotorTarget(motorA, 663, 30);//encoder value from center of one cell to center of next cell
	moveMotorTarget(motorD, 662, 30);
	waitUntilMotorStop(motorA);
	waitUntilMotorStop(motorD);
	wait10Msec(65);//wait for moment of inertia to stabilaze, otherwise we fall
}

//======================================================================
void TurningRight(){//turn right until gyro ditects you have turned 90 degrees
	resetGyro(S4);//reset to avoid any mistake
	while(getGyroDegrees(S4)!=80){//by experience 80 degrees in gyro would end up 90 deg in real life!!!
		setMotorSpeed(motorA, -15);
		setMotorSpeed(motorD, 15);
	}
	resetGyro(S4);//reset to avoid any mistake
}
//======================================================================
void TurningLeft(){//turn left until gyro ditects you have turned 90 degrees
	resetGyro(S4);
	while(getGyroDegrees(S4)!=-80){
		setMotorSpeed(motorA, 15);
		setMotorSpeed(motorD, -15);
	 }
	resetGyro(S4);
}
//======================================================================
void TurnAround(){//turn around until gyro ditects you have turned 180 degrees
	resetGyro(S4);
	while(getGyroDegrees(S4)!=165){
		setMotorSpeed(motorA, -15);
		setMotorSpeed(motorD, 15);
	}
	resetGyro(S4);
}
//=====================================================================
void DropBall(){//drop ball (this function will be called when we reach the cell before basket)
	resetMotorEncoder(motorA);
	resetMotorEncoder(motorD);//first go ahead, this will help us reallign ourself with basket
	moveMotorTarget(motorA, 500, 25);
	moveMotorTarget(motorD, 500, 25);
	waitUntilMotorStop(motorA);
	waitUntilMotorStop(motorD);

	playTone(300, 200);//play tone when you are going to drop the ball

	resetMotorEncoder(motorB);
	moveMotorTarget(motorB, 590, -100);//drop the ball
	waitUntilMotorStop(motorB);
	wait10Msec(70);//wait a little for balls on the rack to move again

	resetMotorEncoder(motorA);
	resetMotorEncoder(motorD);
	moveMotorTarget(motorA, 300, -25);
	moveMotorTarget(motorD, 300, -25);//go back to the center of cell again
	waitUntilMotorStop(motorA);
	waitUntilMotorStop(motorD);
}
//======================================================================
void TakeActions(){

 	for (int x=0; x<2; x++){//Runs through the first two elements of ShortestPath and does turning/going straight according to InstantanousDirection

 	//The reason I did a seperate loop for the firsttwo only is:
 	//my robot knows to drop the ball when it reaches -10 in the array. So I had to make an if statement that had to check [x-2]. This is undefined for the first two elements
 	switch(ShortestPath[x]){
 		//goes through ShortestPath array and checks where it has to go
 		//it will decide wheather to turn left, turn right, turn around or go straight depending on InstantanousDirection
 		//for example: ShortestPath=0, if you facing north, you have to go straight; HOWEVER, if you facing east, you have to turn left.
 //This judgement is emplimented by comparing ShortestPath and InstantanousDirection values
 		case 0:
			 		if(InstantanousDirection[x]==0){//Dont turn, Go straight
			 		GoStraightNoErrorFix();
					break; // Turning North Facing North

					}if(InstantanousDirection[x]==1){//Turn left (90 deg)
					TurningLeft();
					wait10Msec(10);
					//Go straight
					GoStraight();

					break; // Turning North Facing East

					}if(InstantanousDirection[x]==2){//Turn around (180 deg)
					TurnAround();
					//Go straight
					GoStraight();
					break; // Turning North Facing South

					}if(InstantanousDirection[x]==3){//Turn Rght (90 deg)
					TurningRight();
					wait10Msec(10);
					//Go straight
					GoStraight();
					break; // Turning North Facing West

					}

		case 1:

					if(InstantanousDirection[x]==0){//Turn right (90 deg)

					TurningRight();
					//Go straight
					GoStraight();
					break; // Turning East Facing North

					}if(InstantanousDirection[x]==1){//Go straight
					 GoStraightNoErrorFix();
					break; // Turning East Facing East

					}if(InstantanousDirection[x]==2){//Turn left (90 deg)
					TurningLeft();
					wait10Msec(10);
					//Go straight
					GoStraight();

					break; // Turning East Facing South

					}if(InstantanousDirection[x]==3){//Turn around (180 deg)
					TurnAround();
					//Go straight
					GoStraight();
					break; // Turning East Facing West

					}

		case 2:

					if(InstantanousDirection[x]==0){//Turn around (180 deg)

					TurnAround();
					//Go straight
					GoStraight();
					break; // Turning South Facing North

					}if(InstantanousDirection[x]==1){//Turning right (90 deg)
					TurningRight();
					//Go straight
					GoStraight();
					break; // Turning South Facing East

					}if(InstantanousDirection[x]==2){//Go Straight
					GoStraightNoErrorFix();
					break; // Turning South Facing South

					}if(InstantanousDirection[x]==3){//Turn left (90 deg)
					TurningLeft();
					wait10Msec(10);
					//Go straight
					GoStraight();
					break; // Turning South Facing West
					}

		case 3:

					if(InstantanousDirection[x]==0){//Turning Left (90 deg)

					TurningLeft();
					wait10Msec(10);
					//Go straight
					GoStraight();
					break; // Turning West Facing North

					}if(InstantanousDirection[x]==1){//Turn around (180 deg)***************encoder value
					TurnAround();
					//Go straight
					GoStraight();
					break; // Turning West Facing East

					}if(InstantanousDirection[x]==2){//Turning right (90 deg)
					TurningRight();
					wait10Msec(10);
					//Go straight
					GoStraight();
					break; // Turning West Facing South

					}if(InstantanousDirection[x]==3){//Go Straight
					 GoStraightNoErrorFix();
					break; // Turning West Facing West

					}
		default: break;//end of switch
		}

}//end of first for loop

//#############################################Act on second to end commands for moving###############################################

for (int s=2; s<size-1 ; s++){//goes through second element till the end of the array

			if(ShortestPath[s+1]!=-10 && ShortestPath[s-2]!=-10){//I do not need to do the command after -10, also I do not want to do -10
				//Other than those elements, move according to ShortestPath and InstantanousDirection values
				switch(ShortestPath[s]){

					case 0:
								if(InstantanousDirection[s]==0){//Dont turn, Go straight
								GoStraightNoErrorFix();
								break; // Turning North Facing North

								}if(InstantanousDirection[s]==1){//Turn left (90 deg)
								TurningLeft();
								wait10Msec(10);
								//Go straight
								GoStraight();
								break; // Turning North Facing East

								}if(InstantanousDirection[s]==2){//Turn around (180 deg)
								TurnAround();
								//Go straight
								GoStraight();
								break; // Turning North Facing South

								}if(InstantanousDirection[s]==3){//Turn Rght (90 deg)
								TurningRight();
								wait10Msec(10);
								//Go straight
								GoStraight();
								break; // Turning North Facing West
								}

					case 1:

								if(InstantanousDirection[s]==0){//Turn right (90 deg)
								TurningRight();
								wait10Msec(10);
								//Go straight
								GoStraight();
								break; // Turning East Facing North

								}if(InstantanousDirection[s]==1){//Go straight
								GoStraightNoErrorFix();
								break; // Turning East Facing East

								}if(InstantanousDirection[s]==2){//Turn left (90 deg)
								TurningLeft();
								wait10Msec(10);
								//Go straight
								GoStraight();
								break; // Turning East Facing South

								}if(InstantanousDirection[s]==3){//Turn around (180 deg)
								TurnAround();
								//Go straight
								GoStraight();
								break; // Turning East Facing West
								}

					case 2:

								if(InstantanousDirection[s]==0){//Turn around (180 deg)
								TurnAround();
								//Go straight
								GoStraight();
								break; // Turning South Facing North

								}if(InstantanousDirection[s]==1){//Turning right (90 deg)
								TurningRight();
								wait10Msec(10);
								//Go straight
								GoStraight();
								break; // Turning South Facing East

								}if(InstantanousDirection[s]==2){//Go Straight
								GoStraightNoErrorFix();
								break; // Turning South Facing South

								}if(InstantanousDirection[s]==3){//Turn left (90 deg)
								TurningLeft();
								wait10Msec(10);
								//Go straight
								GoStraight();
								break; // Turning South Facing West
								}

					case 3:

								if(InstantanousDirection[s]==0){//Turning Left (90 deg)
								TurningLeft();
								wait10Msec(10);
								//Go straight
								GoStraight();
								break; // Turning West Facing North

								}if(InstantanousDirection[s]==1){//Turn around (180 deg)
								TurnAround();
								//Go straight
								GoStraight();
								break; // Turning West Facing East

								}if(InstantanousDirection[s]==2){//Turning right (90 deg)
								TurningRight();
								wait10Msec(10);
								//Go straight
								GoStraight();
								break; // Turning West Facing South

								}if(InstantanousDirection[s]==3){//Go Straight
								GoStraightNoErrorFix();
								break; // Turning West Facing West
								}

					default: break;

				}//end switch
			}//end if

			//still in the for loop that goes through ShortestPath

//***********************************when is right beside the basket*******************************
			if(ShortestPath[s+1]==-10){//the element before basket tells us which side the basket is, so I use those values here
					switch(ShortestPath[s]){

					case 0://The basket is one cell above

								if(InstantanousDirection[s]==0){//You facing the basket, so just drop it
								DropBall();
								break;

								}if(InstantanousDirection[s]==1){//You facing East, so turn left and drop the ball
								TurningLeft();
								wait10Msec(10);
								DropBall();
								TurningRight();
								break;

								}if(InstantanousDirection[s]==3){//You facing West, so turn right and drop the ball
								TurningRight();
								wait10Msec(10);
								DropBall();
								TurningLeft();
								break;
								}

					case 1://The basket is one cell beside (right)

								if(InstantanousDirection[s]==0){//You facing North, so turn right and drop the ball
								TurningRight();
								wait10Msec(10);
								DropBall();
								TurningLeft();
								break;

								}if(InstantanousDirection[s]==1){//You facing the basket, so just drop it
								DropBall();
								break;

								}if(InstantanousDirection[s]==2){//You facing South, so turn left and drop the ball
								TurningLeft();
								wait10Msec(10);
								DropBall();
								TurningRight();
								break;
								}

					case 2://The basket is one cell below

								if(InstantanousDirection[s]==1){//You facing East, so turn right and drop the ball
								TurningRight();
								wait10Msec(10);
								DropBall();
								TurningLeft();
								break;

								}if(InstantanousDirection[s]==2){//You facing the basket, so just drop it
								DropBall();
								break;

								}if(InstantanousDirection[s]==3){//You facing West, so turn left and drop the ball
								TurningLeft();
								wait10Msec(10);
								DropBall();
								//wait
								TurningRight();
								break;
								}

					case 3://The basket is one cell beside (left)

								if(InstantanousDirection[s]==0){//You facing North, so turn left and drop the ball
								TurningLeft();
								wait10Msec(10);
								DropBall();
								TurningRight();
								break;

								}if(InstantanousDirection[s]==2){//You facing South, so turn right and drop the ball
								TurningRight();
								wait10Msec(10);
								DropBall();
								TurningLeft();
								break;

								}if(InstantanousDirection[s]==3){//You facing the basket, so just drop it
								DropBall();
								break;
								}

					default : break;

					}//end of switch
			}//end second if
		}//end for loop

}//end TakeAction function
