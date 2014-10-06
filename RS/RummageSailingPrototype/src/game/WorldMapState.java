package game;

import util.Constants;
import util.Font;
import org.lwjgl.util.Point;
import org.lwjgl.util.Rectangle;
import org.newdawn.slick.*;
import org.newdawn.slick.state.BasicGameState;
import org.newdawn.slick.state.StateBasedGame;
import util.Images;
import util.Maths;
import zones.*;

import java.util.ArrayList;

/**
 * Created with IntelliJ IDEA.
 * User: zadjii
 * Date: 3/8/13
 * Time: 8:40 PM
 * To change this template use File | Settings | File Templates.
 */
public class WorldMapState extends BasicGameState {
	@Override
	public int getID() {
		return RSP.WORLD_MAP_SCREEN;  //To change body of implemented methods use File | Settings | File Templates.
	}


	private static float W_RATIO = ((float)(RSP.DEFAULT_SCREEN_WIDTH))/600.0f;
	private static float H_RATIO = ((float)(RSP.DEFAULT_SCREEN_HEIGHT))/322.0f;
	private static Point[] areas = new Point[]{
		new Point(150,155),//Florida
		new Point(155,130),//DC
		new Point(275,100),//London
		new Point(320,130),//Mediterranean
		new Point(350,165),//Red Sea
		new Point(410,210),//Indian Ocean
		new Point(350,240),//Madagasgar
		new Point(530,280),//Sydney
		new Point(480,155),//Bejing
		new Point(510,130),//Tokyo
		new Point( 75,115),//Seattle
		new Point( 80,130),//LA
		new Point(150,185),//Panama
		new Point(190,150),//Bermuda
		new Point(135,112),//Mendota
		new Point(330,150),//Nile
		new Point(185,215),//Florida
	};
	private static Zone[] zones = new Zone[]{
			new RedZone(),          //Florida
			new YellowZone(),       //DC
			new GreenZone(),        //London
			new Zone(),             //Mediterranean
			new RedZone(),          //Red Sea
			new YellowZone(),       //Indian Ocean
			new GreenZone(),        //Madagasgar
			new Zone(),             //Sydney
			new RedZone(),          //Bejing
			new YellowZone(),       //Tokyo
			new GreenZone(),        //Seattle
			new Zone(),             //LA
			new RedZone(),          //Panama
			new YellowZone(),       //Bermuda
			new MendotaZone(),        //Mendota
			new EgyptZone(),             //Nile
			new RedZone(),          //Florida
			new YellowZone(),
			new GreenZone(),
			new Zone(),
	};

	private Point mouse = new Point(-1, -1);

	private Input input;

	protected boolean lmbPressed = false;
	protected boolean rmbPressed = false;
	public boolean haveToRelease = false;
	private ArrayList<Particle> particles = new ArrayList<Particle>();
	private static final Color transparentBlack = new Color(0, 0, 0, .5f);
	private double startOfTick = 0;
	protected static boolean drawDebug = false;
	protected static boolean drawTiming = false;
	protected static boolean drawPaths = false;
	private boolean areaClearedNotification = false;

	public Point getMouse() {
		return mouse;
	}

	public boolean drawingPaths(){return drawPaths;}

	public void mouseDragged(int oldx, int oldy, int newx, int newy) {
		mouse.setLocation(newx, newy);
	}

	public void mouseMoved(int oldx, int oldy, int newx, int newy) {
		mouse.setLocation(newx,newy);
	}

	public void mousePressed(int button, int x, int y) {
		if (button == 0) {
			lmbPressed = true;
		}
		if (button == 1) {
			rmbPressed = true;
		}
		mouse.setLocation(x,y);
	}

	public void mouseReleased(int button, int x, int y) {
		if (button == 0) {
			lmbPressed = false;
			//mouseRectangle.setSize(-1, -1);
			//mouseRectangle.setLocation(-1, -1);

			/*
			* If the player releases the mouse over a location, then the
			 * game will try and load up the zone corresponding to that
			 * dot.
			* */

			Point descaledMouse = convertToUnscaled(mouse);

			for (int i = 0; i < RSP.rsp.getLevel()&& i<areas.length; i++) {

				if(Maths.dist(descaledMouse, areas[i]) < 10){
					Zone zone = zones[i];
					Engine e = new Engine(zone);
					RSP.setEngine(e);
					RSP.enterMenuState(RSP.GAME_SCREEN);
				}
			}

		}
		if (button == 1) {
			rmbPressed = false;
			//mouseRectangle.setSize(-1, -1);
			//mouseRectangle.setLocation(-1, -1);
		}
		haveToRelease = false;
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
	/**
	 * Takes a point (generally the mouse) of the screen, and converts it to the
	 * image coordinates. so if the point is on top of london in the window, then
	 * it will de-scale to the proper point on the original image of the earth.
	 *
	 * */
	private Point convertToUnscaled(Point point){
		float newX = ((float)(point.getX()))/((float)(W_RATIO));
		float newY = ((float)(point.getY()))/((float)(H_RATIO));
		return new Point((int)newX, (int)newY);
	}

	public void render(GameContainer gc, StateBasedGame sbg, Graphics g) throws SlickException {

		Images.earthMap.draw(0,0, RSP.DEFAULT_SCREEN_WIDTH, RSP.DEFAULT_SCREEN_HEIGHT);


		g.setColor(Color.orange);
		Point descaledMouse = convertToUnscaled(mouse);
		for (int i = 0; i < RSP.rsp.getLevel() && i<areas.length; i++) {
			if(Maths.dist(descaledMouse, areas[i]) < 10){
				g.setColor(Color.red);
			}
			else{
				g.setColor(Color.orange);

			}
			g.fillOval(
					(areas[i].getX()*W_RATIO) - 10,
					(areas[i].getY()*H_RATIO) - 10,
					20,
					20);
		}
		Constants.drawScores();
	}

	@Override
	public void update(GameContainer gameContainer, StateBasedGame stateBasedGame, int i) throws SlickException {



	}

}
