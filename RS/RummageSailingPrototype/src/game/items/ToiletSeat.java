package game.items;

import org.newdawn.slick.Graphics;
import util.Images;

/**
 * Created with IntelliJ IDEA.
 * User: zadjii
 * Date: 4/18/13
 * Time: 9:41 PM
 * To change this template use File | Settings | File Templates.
 */
public class ToiletSeat extends Item{
	public ToiletSeat(){
		this.greenScore = (int)(Math.random() * 10);
		this.greedScore = (int)(Math.random() * 10);
		this.money = (int)(Math.random() * 10) + 1;
		this.mass = (int)(Math.random() * 10) + 1;

		this.width = 30;
		this.height = 20;
	}
	public void draw(float sx, float sy, float z, Graphics g, float x, float y) {
		Images.toiletSeat.draw((x-sx)*z, (y-sy)*z, width, height);
	}
}
