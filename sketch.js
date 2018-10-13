var bar1X;
var bar1Y;
var bar2X;
var bar2Y;
var ballX;
var ballY;
var velocity;
var ballDirectionX;
var ballDirectionY;
var canvasX;
var canvasY;
var barW;
var barH;
var ballDiameter;
var ballRadius;
var bar1Score;
var bar2Score;
var scoreSize;
var pause;
var instructionsSize;

function setup() {
	pause=true;

	canvasX=windowWidth*0.6
	canvasY=windowHeight*0.6
//canvasX=600
//canvasY=400
 	 var canvas = createCanvas(canvasX, canvasY);
 
  // Move the canvas so it’s inside our <div id="sketch-holder">.
 	 canvas.parent('canvas');

  	startBarPosition();
	startBallPosition();
	velocity=4

	bar1Score=0
	bar2Score=0

	scoreSize=canvasX*0.05
	instructionsSize=canvasX*0.015

	iterate()
}

function startBarPosition(){
	barW=canvasX*0.02
	barH=canvasY*0.25
	bar1X=0
	bar1Y=0
	bar2X=canvasX-barW
	bar2Y=0
}
function startBallPosition(){
	canvasAverage=(canvasX+canvasY)/2
	ballDiameter=canvasAverage*0.04
	ballRadius=ballDiameter/2
	ballX=canvasX/2
	ballY=canvasY/2
	ballDirectionX=-1
	if(Math.random()>0.5)ballDirectionX=1;
	ballDirectionY=-1
	if(Math.random()>0.5)ballDirectionY=1;
}

function draw() {
	if(!pause){
		iterate()
	}
}

function iterate(){
	background(0);
    fill(255);
	bar1();
	bar2();
	ball();
	drawScore();
	drawInstructions()
}

function drawInstructions(){
	fill(255);
	textSize(instructionsSize);
	textAlign(LEFT);
	text("W=UP \nS=DOWN", canvasX * .03 , canvasY*0.9);
	text("R=Reset Game", canvasX * .20 , canvasY*0.9);
	textAlign(RIGHT);
	text("↑=UP \n↓=DOWN", canvasX * .97 , canvasY*0.9);
	text("P=Pause/UnPause", canvasX * .80 , canvasY*0.9);

}

function drawScore(){
	var line = "\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|"
	fill(255);
	textSize(scoreSize);
	textAlign(CENTER, CENTER);
	text(bar1Score+"  "+bar2Score, canvasX * .5 , canvasY*0.1);
	text(line, canvasX * .5 , 0);

}
function bar1(){

 if (keyIsDown(87)) {
    bar1Y-=velocity;
  }

  if (keyIsDown(83)) {
    bar1Y+=velocity;
  }

	if(bar1Y<0) bar1Y=0;
	if(bar1Y>canvasY-barH) bar1Y=canvasY-barH;
	rect(bar1X,bar1Y,barW,barH);
}
function bar2(){
	if (keyIsDown(38)) {
  	 	bar2Y-=velocity;
 	}

  	if (keyIsDown(40)) {
    	bar2Y+=velocity;
  	}
	if(bar2Y<0) bar2Y=0;
	if(bar2Y>canvasY-barH) bar2Y=canvasY-barH;
	rect(bar2X,bar2Y,barW,barH);
}
function ball(){
	computeCollision()
	ballX+=ballDirectionX*velocity
	ballY+=ballDirectionY*velocity
	ellipse(ballX,ballY,ballDiameter,ballDiameter)

	if(ballX>(canvasX-ballRadius)){
		startBallPosition();
		bar1Score++
	}
	if(ballX<ballRadius){
		startBallPosition();
		bar2Score++
	}
	if(ballY>(canvasY-ballRadius) || ballY<ballRadius){
		ballDirectionY=ballDirectionY*-1;
	}		
}

function computeCollision(){
	if(((ballY>bar2Y)&&(ballY<bar2Y+barH))&&(ballX+ballRadius>bar2X))ballDirectionX=ballDirectionX*-1;
	if(((ballY>bar1Y)&&(ballY<bar1Y+barH))&&(ballX-ballRadius<barW))ballDirectionX=ballDirectionX*-1;
}

function keyPressed() {

	if (key == 1) {
	  velocity=1
	}

	if (key == 2) {
		velocity=2
	}

	if (key == 3) {
		velocity=3
	}

	if (key == 4) {
		velocity=4
	}
	if (key == 5) {
		velocity=5
	}
	if (key == 6) {
		velocity=6
	}

	if (key == 'r') {
		resetGame();
	}
	if (key == 'p') {
		changeGameStatus();
	}

  }

function resetGame(){
	//changeGameStatus();
	startBallPosition();
	startBarPosition();
	resetScore();
	iterate()
	pause=true
	//changeGameStatus();
}

function resetScore(){
	bar1Score=0
	bar2Score=0
}

function changeGameStatus(){
	if(pause){pause=false}else{pause=true}
}
