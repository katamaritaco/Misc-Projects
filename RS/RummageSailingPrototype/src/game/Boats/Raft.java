package game.Boats;

import entities.Player;
import game.Engine;
import game.RSP;
import org.newdawn.slick.Color;
import org.newdawn.slick.Graphics;
import util.Images;


public class Raft extends Boat {

	public static final Color raftColor = new Color(0.6f, 0.5f, 0.2f);

	private static float w = 48.0f * 3;
	private static float h = 48.0f;

	public Raft(){
		this.capacity = 10;
	}

	public void tick(Engine engine) {
		this.tickTools(engine);
	}

	public void drawBack(float sx, float sy, float z, Graphics g) {
//		g.setColor(raftColor);
//		Player p = RSP.getPlayer();
//		g.fillRect((p.getX() - sx- w/2)*z, (p.getY()-sy - h/2)*z, w * z, h * z);

	}
	public void drawFront(float sx, float sy, float z, Graphics g) {
		Player p = RSP.getPlayer();
		Images.raft.draw((p.getX() - sx- w/2)*z, (p.getY()-sy - h/2)*z, w * z, h * z);
		drawTools(sx, sy, z, g);
	}
}
