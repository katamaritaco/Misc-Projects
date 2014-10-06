package game;

import entities.Player;
import org.lwjgl.util.Point;
import org.newdawn.slick.*;
import org.newdawn.slick.state.*;

import java.util.Random;

public class RSP extends StateBasedGame {

	public static RSP rsp;
	private static Engine engine;
	private static GameScreen gameScreen;
	private static Player player;
	//private static Thread loaderThread;
	private static String saveName;

	public static final String GAME_VERSION = "v0.2";
	public static final int LOGO_SCREEN = 0;
	public static final int TITLE_SCREEN = 1;
	public static final int WORLD_MAP_SCREEN = 2;
	public static final int GAME_SCREEN = 3;
	public static final int NEW_PLAYER_SCREEN = 3;
	public static final int WORLD_SELECT_SCREEN = 4;
	public static final int NEW_WORLD_SCREEN = 5;
	public static final int LOADING_SCREEN = 6;
	public static final int PLAYER_SELECT_SCREEN = 7;

	public static final int DEFAULT_SCREEN_HEIGHT = 480;//1152x768 is nice too //Yea but at this point changing the window size would involve a LOT of refactoring. We should save that for final release.
	public static final int	DEFAULT_SCREEN_WIDTH = 854;

	private static TitleScreen.LogoScreen logoScreen;
	private static TitleScreen titleScreen;

	private int currentLevel = 20;
	private static WorldMapState worldMapState;
	//Extra Example States
//	private static PlayerSelectScreen playerSelectScreen;
//	private static NewPlayerScreen newPlayerScreen;
//	private static WorldSelectScreen worldSelectScreen;
//	private static NewWorldScreen newWorldScreen;
//	private static LoadingScreen loadingScreen;

	public RSP() throws SlickException {
		super("Rummage Sailing " + GAME_VERSION);
		addState(titleScreen);
		addState(logoScreen);
		addState(worldMapState);
	}

	public static void main(String[] args) throws SlickException {

		/*Initialize all of the game states*/
		logoScreen = new TitleScreen.LogoScreen();
		titleScreen = new TitleScreen();
		gameScreen = new GameScreen();
		worldMapState = new WorldMapState();
//		playerSelectScreen = new PlayerSelectScreen();
//		newPlayerScreen = new NewPlayerScreen();
//		worldSelectScreen = new WorldSelectScreen();
//		newWorldScreen = new NewWorldScreen();
//		loadingScreen = new LoadingScreen();

		rsp = new RSP();
		player = new Player();
		AppGameContainer app = new AppGameContainer(rsp);
		rsp.initStatesList(app);
		app.setDisplayMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, false);

		//app.setVSync(true);//This here is keeping your fps down. it can be commented out for testing, but i think it needs to be on.
		app.setTargetFrameRate(60);
		app.setShowFPS(false);
		rsp.enterState(LOGO_SCREEN);
		app.start();
	}



	public static void loadGame() throws SlickException {

		engine = new Engine();

		gameScreen.setEngine(engine);
		engine.setGameScreen(gameScreen);

		gameScreen.init(rsp.getContainer(), rsp);
		rsp.enterState(GAME_SCREEN);

		//loaderThread = null;
	}

	public static void enterMenuState(int state) {
		rsp.enterState(state);
	}

	public void initStatesList(GameContainer gc) throws SlickException {
		addState(logoScreen);
		addState(titleScreen);
		addState(worldMapState);
		addState(gameScreen);
		/** Additional states example code*/
//		addState(playerSelectScreen);
//		addState(newPlayerScreen);
//		addState(worldSelectScreen);
//		addState(newWorldScreen);
//		addState(loadingScreen);
	}
	public int getLevel(){return currentLevel;}
	public static String getSaveName() {
		return saveName;
	}

	public static Engine getEngine() {
		return engine;
	}
	public static Player getPlayer(){
		return player;
	}
	public static float getZoom() {
		return engine.getZoom();
	}

	public static String getLoc(Point p) {
		return "(" + p.getX() + ", " + p.getY() + ")";
	}

	public static Random getRand() {
		return engine.rand;
	}
	public static void setEngine(Engine e){
		engine = e;
		gameScreen.setEngine(e);
		engine.setGameScreen(gameScreen);
	}
}