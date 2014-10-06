package game;


import entities.Effects.Effect;
import entities.ItemEntity;
import entities.Player;
import org.lwjgl.util.Point;
import org.lwjgl.util.Rectangle;
import zones.*;

import java.util.Random;

public class Engine {

//	private NewGameArea area;
	private transient GameScreen gameScreen;


	private int seed = (int)(Math.random() * 1000000);
	public final Random rand = new Random(seed);

	/** The Player*/
	private Player player;
	private Zone zone;

	private boolean paused = false;
	protected boolean lmbPressed = false;
	protected boolean rmbPressed = false;
	protected boolean needToRelease = false;

	private int screenW = RSP.DEFAULT_SCREEN_WIDTH;
	private int screenH = RSP.DEFAULT_SCREEN_HEIGHT;

	private float seaHeight = 100;
	private float seaLevel = RSP.DEFAULT_SCREEN_HEIGHT - seaHeight;



	private Rectangle screen = new Rectangle(0,0,screenW,screenH);

	private float zoomFactor = 1.0f;
	public float getZoom(){return zoomFactor;}
	public void setZoom(float z) {
		zoomFactor = z;
		screen.setWidth((int)(screenW/zoomFactor));
		screen.setHeight((int)(screenH/zoomFactor));
	}
	private boolean wPressed = false;
	public void setWPressed(boolean pressed){this.wPressed = pressed;}
	private boolean aPressed = false;
	public void setAPressed(boolean pressed){this.aPressed = pressed;}
	private boolean sPressed = false;
	public void setSPressed(boolean pressed){this.sPressed = pressed;}
	private boolean dPressed = false;
	public void setDPressed(boolean pressed){this.dPressed = pressed;}
	public Rectangle getScreen(){
		return screen;
	}
	public Player getPlayer() {return this.player;}
	public GameScreen getGameScreen() {return gameScreen;}
	public void setGameScreen(GameScreen gs) {this.gameScreen = gs;}
	public boolean isPaused() {return paused;}
	public float getSeaLevel(){return seaLevel;}
	public float getSeaHeight(){return seaHeight;}
	public Zone getZone(){return zone;}



	//TODO: Constructor

	public Engine(){

		this.zone = new Zone();
		switch (rand.nextInt(4)){
			case 0:zone = new RedZone();break;
			case 1:zone = new GreenZone();break;
			case 2:zone = new YellowZone();break;
			case 3:zone = new Zone();break;
		}
		this.player = RSP.getPlayer();
	}
	public Engine(Zone zone){

		this.zone = zone;
		this.player = RSP.getPlayer();
	}

	//TODO: update()
	public void update(){
		if(paused)return;

//		Character playerCharacter = player.getCharacter();
		if(wPressed){
			player.setDY(-.5f);
		}
		if(sPressed){
			player.setDY(.5f);
		}
		if(aPressed){
			player.setDX(-.5f);
		}
		if(dPressed){
			player.setDX(.5f);
		}

		player.setY(this.seaHeight);
		Point mouse = gameScreen.getMouse();
		//System.out.println();
		//System.out.println("lmbPressed: " + lmbPressed);
		//System.out.println("needToRelease: " + needToRelease);
		player.tick(this);
		if(lmbPressed&&!needToRelease){
			needToRelease = player.useGetter(mouse, this);
		}
		zone.tick(this);

		if(zone.getZoneTimer().offCooldown()){
			//display the gameover screen.
			//if the player has clicked the return button, return to overworld
			//right now, we're just gonna auto return
			zone.reset();
			RSP.enterMenuState(RSP.WORLD_MAP_SCREEN);
			return;
		}

		zone.addItem(this);



	}



	public void add(Particle p) {
		gameScreen.getParticles().add(p);
	}
	public void add(Effect effect) {
		zone.getEffects().add(effect);
	}







	public void centerScreen(int x, int y){
		screen.setBounds(x-(screen.getWidth()/2), y-(screen.getHeight()/2), screen.getWidth(), screen.getHeight());
	}
	public void pause() {
		paused = true;
	}

	public void unpause() {
		paused = false;
	}


	public void togglePause(){
		this.paused = !this.paused;
	}
	public Cooldown getZoneTimer(){return zone.getZoneTimer();}
	public void addToBeRemoved(ItemEntity item){
		zone.addToBeRemoved(item);
	}
}
