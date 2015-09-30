float g = 5/2; // gravity
float fact = 3; // xgravity
float x, y; // positions
int screenwid = 525; 
int buffer = 25;

void setup() {
// only happens when program first runs
// initialization, etc
  size(screenwid,screenwid);
  background(255); // note that 1 number = default to grayscale, 3 = rgb
  y=height/2;
  x=width/2;
}

void draw () {
// constantly running over and over again
  noStroke(); // kind of like "hold"
  fill(random(255),(x-buffer)/2,(y-buffer)/2);
  
  y=y+g;
  x=x+fact;
  for (int i=0; i<20; i++) {
    ellipse(x+random(24),y+random(24),5,5); 
  }
  if (y>(screenwid-buffer) || y<buffer) {
    g*=-1;
    g=g+random(-.1,.1);
  } 
  if (x<buffer || x>(screenwid-buffer)) {
    fact*=-1+random(-.1,.1);
    //fact=fact*random(1);
  }
  
}


