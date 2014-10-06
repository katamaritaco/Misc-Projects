package zones;

import game.RSP;
import org.newdawn.slick.Graphics;
import util.Images;

/**
 * Created with IntelliJ IDEA.
 * User: zadjii
 * Date: 3/8/13
 * Time: 8:39 PM
 * To change this template use File | Settings | File Templates.
 */
public class GreenZone extends Zone {
	public void drawBackground(float sx, float sy, float z, Graphics g){
		Images.greenBG.draw(sx, sy, RSP.DEFAULT_SCREEN_WIDTH, RSP.DEFAULT_SCREEN_HEIGHT);


	}
}
