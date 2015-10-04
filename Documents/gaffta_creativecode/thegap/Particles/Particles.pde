// Particles, by Daniel Shiffman.

ParticleSystem ps, ps2, ps3, ps4, ps5, ps6, ps7;
PImage sprite;  

void setup() {
  background(#66FFFF);
  size(1024, 768, P2D);
  orientation(LANDSCAPE);
  sprite = loadImage("shape-01.png");
  ps = new ParticleSystem(100);
    sprite = loadImage("shape-02.png");
  ps2 = new ParticleSystem(100);
      sprite = loadImage("shape-03.png");
  ps3 = new ParticleSystem(100);
        sprite = loadImage("shape-04.png");
  ps4 = new ParticleSystem(100);
        sprite = loadImage("shape-05.png");
  ps5 = new ParticleSystem(100);
        sprite = loadImage("shape-06.png");
  ps6 = new ParticleSystem(100);
        sprite = loadImage("shape-07.png");
  ps7 = new ParticleSystem(100);

  // Writing to the depth buffer is disabled to avoid rendering
  // artifacts due to the fact that the particles are semi-transparent
  // but not z-sorted.
  hint(DISABLE_DEPTH_MASK);
} 

void draw () {
  background(#66FFFF);
  ps.update();
  ps.display();
  ps.setEmitter(mouseX,mouseY);
  
  ps2.update();
  ps2.display();
  ps2.setEmitter(mouseX,mouseY);
  
  ps3.update();
  ps3.display();
  ps3.setEmitter(mouseX,mouseY);
  
  ps4.update();
  ps4.display();
  ps4.setEmitter(mouseX,mouseY);
  
  ps5.update();
  ps5.display();
  ps5.setEmitter(mouseX,mouseY);
  
  ps6.update();
  ps6.display();
  ps6.setEmitter(mouseX,mouseY);
  
  ps7.update();
  ps7.display();
  ps7.setEmitter(mouseX,mouseY);
  
  fill(255);
  textSize(16);
  text("Frame rate: " + int(frameRate), 10, 20);
  
}
class Particle {

  PVector velocity;
  float lifespan = 255;
  
  PShape part;
  float partSize;
  
  PVector gravity = new PVector(0,0.1);


  Particle() {
    partSize = random(10,60);
    part = createShape();
    part.beginShape(QUAD);
    part.noStroke();
    part.texture(sprite);
    part.normal(0, 0, 1);
    part.vertex(-partSize/2, -partSize/2, 0, 0);
    part.vertex(+partSize/2, -partSize/2, sprite.width, 0);
    part.vertex(+partSize/2, +partSize/2, sprite.width, sprite.height);
    part.vertex(-partSize/2, +partSize/2, 0, sprite.height);
    part.endShape();
    
    rebirth(width/2,height/2);
    lifespan = random(255);
  }

  PShape getShape() {
    return part;
  }
  
  void rebirth(float x, float y) {
    float a = random(TWO_PI);
    float speed = random(0.5,4);
    velocity = new PVector(cos(a), sin(a));
    velocity.mult(speed);
    lifespan = 255;   
    part.resetMatrix();
    part.translate(x, y); 
  }
  
  boolean isDead() {
    if (lifespan < 0) {
     return true;
    } else {
     return false;
    } 
  }
  

  public void update() {
    lifespan = lifespan - 1;
    velocity.add(gravity);
    
    part.setTint(color(255,lifespan));
    part.translate(velocity.x, velocity.y);
  }
}
class ParticleSystem {
  ArrayList<Particle> particles;

  PShape particleShape;

  ParticleSystem(int n) {
    particles = new ArrayList<Particle>();
    particleShape = createShape(PShape.GROUP);

    for (int i = 0; i < n; i++) {
      Particle p = new Particle();
      particles.add(p);
      particleShape.addChild(p.getShape());
    }
  }

  void update() {
    for (Particle p : particles) {
      p.update();
    }
  }

  void setEmitter(float x, float y) {
    for (Particle p : particles) {
      if (p.isDead()) {
        p.rebirth(x, y);
      }
    }
  }

  void display() {

    shape(particleShape);
  }
}

