package game;

import org.lwjgl.util.Point;
import org.lwjgl.util.Rectangle;
import org.newdawn.slick.*;
import org.newdawn.slick.state.*;
import util.*;
import util.Font;

import javax.swing.*;
import java.awt.event.*;

//The new TitleScreen, with the moving terrain image in the background and generally fancier (and actually working)
public class TitleScreen extends BasicGameState {

	public static class LogoScreen extends BasicGameState {
		private int counter;

		public void init(GameContainer arg0, StateBasedGame arg1) throws SlickException {
			Images.init();
			//Audio.init();
		}

		public void render(GameContainer arg0, StateBasedGame arg1, Graphics arg2) throws SlickException {
			Images.companyLogo.draw(0f, 0, RSP.DEFAULT_SCREEN_WIDTH, RSP.DEFAULT_SCREEN_HEIGHT);
		}

		public void update(GameContainer arg0, StateBasedGame arg1, int arg2) throws SlickException {
			++counter;
			if (counter >= 75) RSP.enterMenuState(RSP.TITLE_SCREEN);
		}

		public int getID() {
			return RSP.LOGO_SCREEN;
		}
	}

	private Input input;
	private boolean[] hovering;
	private int backgroundX, backgroundY;
	private static final int PLAY = 0, SETTINGS = 1, QUIT = 2;
	private int growthLevel = 0;

	public TitleScreen() {
		resetSelectionBooleans();
	}

	private void resetSelectionBooleans() {
		hovering = new boolean[3];
	}

	public void keyPressed(int key, char c) {


	}
	private static final Rectangle playButtonBounds = new Rectangle(300, 260, 265, 128);


	public void mousePressed(int button, int x, int y) {
		if (button == 0) {

//			try{
			if(playButtonBounds.contains(new Point(x, y))){
				RSP.enterMenuState(RSP.WORLD_MAP_SCREEN);
			}
//				if (x > 455 && x < 600 && y > 260 && y < 300) {
////					RSP.loadGame();
//					RSP.enterMenuState(RSP.WORLD_MAP_SCREEN);
//				}
//				else if (x > 380 && x < 675 && y > 320 && y < 360) return; //No Settings menu yet
				//else if (x > 455 && x < 600 && y > 380 && y < 420) System.exit(0);
//			}catch(SlickException e){}

			}
	}


	public void init(GameContainer gc, StateBasedGame game) throws SlickException {
		input = new Input(600);
		input.addListener(this);
	}

	public void render(GameContainer arg0, StateBasedGame arg1, Graphics g) throws SlickException {
//		Images.terrain.draw(backgroundX, backgroundY);

		Images.menuScreen.draw(0f, 0, RSP.DEFAULT_SCREEN_WIDTH, RSP.DEFAULT_SCREEN_HEIGHT);

		//Font.drawDkNorthumbriaString("Rummage Sailing", 200, 75, 50, null, Font.FontType.RENDERED);
		//g.setColor(Color.green);
		//g.fillRect(playButtonBounds.getX(), playButtonBounds.getY(), playButtonBounds.getWidth(), playButtonBounds.getHeight());
		//g.fillRect(455,260,145,40);
//		Font.drawMonospacedFontString("PLAY", 455, 250, 60, hovering[0] ? Color.white : Color.black);
//		Font.drawMonospacedFontString("SETTINGS", 380, 310, 60, hovering[1] ? Color.white : Color.black);
//		Font.drawMonospacedFontString("QUIT", 455, 370, 60, hovering[2] ? Color.white : Color.black);
	}

	public void update(GameContainer gc, StateBasedGame game, int delta) throws SlickException {

	}

	public int getID() {
		return RSP.TITLE_SCREEN;
	}
}
