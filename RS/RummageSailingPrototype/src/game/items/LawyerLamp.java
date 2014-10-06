package game.items;

import org.newdawn.slick.Graphics;
import util.Images;

public class LawyerLamp extends Item {
	public LawyerLamp(){
		this.greenScore = (int)(Math.random() * 10);
		this.greedScore = (int)(Math.random() * 10);
		this.money = (int)(Math.random() * 10) + 1;
		this.mass = (int)(Math.random() * 10) + 1;

		this.width = 36;
		this.height = 36;
	}
	public void draw(float sx, float sy, float z, Graphics g, float x, float y) {
		Images.lawyerLamp.draw((x-sx)*z, (y-sy)*z, width, height);
	}
}
