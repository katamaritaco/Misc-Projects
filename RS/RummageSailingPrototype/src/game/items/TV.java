package game.items;

import org.newdawn.slick.Graphics;
import util.Images;

/**
 * Created with IntelliJ IDEA.
 * User: zadjii
 * Date: 4/18/13
 * Time: 9:45 PM
 * To change this template use File | Settings | File Templates.
 */
public class TV extends Item {
	public TV(){
		this.greenScore = (int)(Math.random() * 10);
		this.greedScore = (int)(Math.random() * 10);
		this.money = (int)(Math.random() * 10) + 1;
		this.mass = (int)(Math.random() * 10) + 1;

		this.width = 50;
		this.height = 50;
	}
	public void draw(float sx, float sy, float z, Graphics g, float x, float y) {
		Images.tv.draw((x-sx)*z, (y-sy-(height/4))*z, width, height);

	}
}
