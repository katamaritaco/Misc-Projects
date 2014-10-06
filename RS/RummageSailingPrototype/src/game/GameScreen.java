package game;


import entities.Effects.Effect;
import entities.Entity;
import entities.ItemEntity;
import org.lwjgl.util.Point;
import org.lwjgl.util.Rectangle;
import org.newdawn.slick.*;
import org.newdawn.slick.geom.Circle;
import org.newdawn.slick.state.BasicGameState;
import org.newdawn.slick.state.StateBasedGame;
import util.Constants;

import java.util.ArrayList;
import static game.RSP.*;


public class GameScreen extends BasicGameState {

	private Engine engine;

	private Point mouse = new Point(-1, -1);

	private Input input;
	private ArrayList<Particle> particles = new ArrayList<Particle>();
	private static final Color transparentBlack = new Color(0, 0, 0, .5f);
	private double startOfTick = 0;
	protected static boolean drawDebug = false;
	protected static boolean drawTiming = false;
	protected static boolean drawPaths = false;
	//private Image lighting;
	//private Graphics overlay;

	private Rectangle notificationZone = new Rectangle(800, 10, 32, 32);

	private byte tenCountTicker = 0;
	private byte sixtyCountTicker = 0;
	private boolean areaClearedNotification = false;

	private ArrayList<Circle> waterCircles = new ArrayList<Circle>();

	public Point getMouse() {
		return mouse;
	}

	public void setEngine(Engine e) {
		engine = e;
	}
	public boolean drawingPaths(){return drawPaths;}

	public void mouseDragged(int oldx, int oldy, int newx, int newy) {
		mouse.setLocation((int) (newx / RSP.getZoom()) + engine.getScreen().getX(), (int) (newy / RSP.getZoom()) + engine.getScreen().getY());

	}

	public void mouseMoved(int oldx, int oldy, int newx, int newy) {

		mouse.setLocation((int) (newx / RSP.getZoom()) + engine.getScreen().getX(), (int) (newy / RSP.getZoom()) + engine.getScreen().getY());

	}

	public void mousePressed(int button, int x, int y) {
		if (button == 0) {
			engine.lmbPressed = true;
		}
		if (button == 1) {
			engine.rmbPressed = true;
		}
		mouse.setLocation(
				(int) (x / RSP.getZoom()) + engine.getScreen().getX(),
				(int) (y / RSP.getZoom()) + engine.getScreen().getY()
		);

	}

	public void mouseReleased(int button, int x, int y) {
		if (button == 0) {
			engine.lmbPressed = false;
			//mouseRectangle.setSize(-1, -1);
			//mouseRectangle.setLocation(-1, -1);
		}
		if (button == 1) {
			engine.rmbPressed = false;
			//mouseRectangle.setSize(-1, -1);
			//mouseRectangle.setLocation(-1, -1);
		}
		engine.needToRelease = false;
	}

	public void mouseWheelMoved(int change) {

	}

	public void keyPressed(int key, char c) {
		KeyHandler.keyPressed(key, c);
	}

	public void keyReleased(int key, char c) {
		KeyHandler.keyReleased(key, c);
	}

	public void init(GameContainer gc, StateBasedGame game) throws SlickException {

		input = new Input(600);
		input.addListener(this);
		//Crafting.init(RSP.getPlayerInventory(), engine.getActiveArea());
	}

	// TODO Shortcut to render()
	public void render(GameContainer gc, StateBasedGame game, Graphics g) throws SlickException {


//		g.setColor(Color.cyan);
//		g.fillRect(0,0, RSP.DEFAULT_SCREEN_WIDTH, RSP.DEFAULT_SCREEN_HEIGHT);
//		g.setColor(Color.blue);
//		g.fillRect(0,RSP.DEFAULT_SCREEN_HEIGHT, RSP.DEFAULT_SCREEN_WIDTH, -engine.getSeaLevel());


		engine.getZone().drawBackground(0,0,1,g);

		for(Entity entity : engine.getZone().getItems()){
			ItemEntity item = (ItemEntity)entity;
			item.draw(0,0,engine.getZoom(), g);
		}
		for(Effect effect:engine.getZone().getEffects()){
			effect.draw(0,0,1.0f,g);
		}
		engine.getPlayer().draw(0,0,1,g);

		drawZoneTimeRemaining(engine, g);

		Constants.drawScores();
		// FPS
		util.Font.drawTriniganFgString(Integer.toString(gc.getFPS()), 1000, 570, 16, Color.white);




	}






	public void update(GameContainer gc, StateBasedGame game, int delta) throws SlickException {
		startOfTick = System.nanoTime();
		engine.update();

		startOfTick = System.nanoTime() - startOfTick;
		startOfTick = startOfTick/1000000000;
		if(startOfTick < 0.016){
		}
		if(tenCountTicker < 10)tenCountTicker++;
		else tenCountTicker = 0;

		if(sixtyCountTicker < 60)sixtyCountTicker++;
		else sixtyCountTicker = 0;
		//System.out.println(startOfTick);

	}

	public int getID() {
		return RSP.GAME_SCREEN;
	}

	public ArrayList<Particle> getParticles() {
		return particles;
	}
	private void drawZoneTimeRemaining(Engine engine, Graphics g){

		float width = 100 * (engine.getZoneTimer().getRemaining()/engine.getZoneTimer().getDuration());

		if(width>50)g.setColor(Color.green);
		else if(width>15)g.setColor(Color.yellow);
		else g.setColor(Color.red);

		g.fillRect(DEFAULT_SCREEN_WIDTH - 116, 16, width, 16);


		g.setLineWidth(3);
		g.setColor(Color.black);
		g.drawRect(DEFAULT_SCREEN_WIDTH - 116, 16, 100, 16);




		g.setLineWidth(1);
	}
}