package game;

import org.newdawn.slick.Input;


public class KeyHandler {

    public static boolean shiftKeyPressed = false;

    public static void keyPressed(int key, char c) {
	    Engine engine = RSP.getEngine();
		if (key == Input.KEY_ESCAPE) {


		}
		if (key == Input.KEY_LSHIFT || key == Input.KEY_RSHIFT) {
//			CraftingMenu.setShiftKeyPressed(true);
            shiftKeyPressed = true;
		}
		if (key == Input.KEY_LCONTROL) {
		}
		if (key == Input.KEY_SPACE) {
		}
		if (c == 'x'||c == 'X') {
		}
		if (c == 'a' || c == 'A') {
			engine.setAPressed(true);
		}
		if (c == 'd' || c == 'D') {
			engine.setDPressed(true);
		}
		if (c == 'w' || c == 'W') {
			engine.setWPressed(true);
		}
		if (c == 's' || c == 'S') {
			engine.setSPressed(true);
		}
		if (c == 'e' || c == 'E') {

		}
		if (c == 'r' || c == 'R') {
		}
	    if (c == 'l' || c == 'L') {
	    }
	    if (c == '!') {
		}
		if (c == '@') {
		}
		if (c == '#') {
		}
		if (c == '$') {
		}
		if (c == '%') {
		}
	    if (c == '|') {
	    }
	    if (c == '}') {
	    }
	    if (c == '{') {
	    }
	    if (c == '1') {
		    RSP.getPlayer().setActiveTool(0);
	    }
	    if (c == '2') {
		    RSP.getPlayer().setActiveTool(1);
	    }
	    if (c == '3') {
		    RSP.getPlayer().setActiveTool(2);
	    }
	    if (c == '4') {
		    RSP.getPlayer().setActiveTool(3);
	    }
	    if (c == '5') {
		    RSP.getPlayer().setActiveTool(4);
	    }
	    if (c == ',') {
		    if (engine.getZoom() > 0.25)
			    engine.setZoom(engine.getZoom() - 0.1f);
		    if (engine.getZoom() < 0.25)
			    engine.setZoom(0.25f);
	    }
	    if (c == '.') {
		    if (engine.getZoom() < 4.0)
			    engine.setZoom(engine.getZoom() + 0.1f);
		    if (engine.getZoom() > 4.0)
			    engine.setZoom(4.0f);
	    }
    }
    public static void keyReleased(int key, char c) {
	    Engine engine = RSP.getEngine();
		if (key == Input.KEY_LSHIFT || key == Input.KEY_RSHIFT) {
//			CraftingMenu.setShiftKeyPressed(false);
            shiftKeyPressed = false;
		}
		if (c == 'a' || c == 'A') {
			engine.setAPressed(false);
		}
		if (c == 'd' || c == 'D') {
			engine.setDPressed(false);

		}
		if (c == 'w' || c == 'W') {
			engine.setWPressed(false);

		}
		if (c == 's' || c == 'S') {
			engine.setSPressed(false);

		}
    }
}
