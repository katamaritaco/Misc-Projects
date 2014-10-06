package game.Tools;

import entities.Effects.Hook;
import entities.Player;
import game.Cooldown;
import game.Engine;
import game.RSP;
import org.lwjgl.util.Point;
import org.newdawn.slick.Color;
import org.newdawn.slick.Graphics;
import util.Constants;
import zones.Zone;

/**
 * Created with IntelliJ IDEA.
 * User: zadjii
 * Date: 4/9/13
 * Time: 6:49 PM
 * To change this template use File | Settings | File Templates.
 */
public class OldRod extends GetterTool{
	private Cooldown useCooldown;
	public OldRod(){
		this.useCooldown = new Cooldown(3.0f*Constants.TICKS_PER_SECOND);
		this.weight = 0;
		//useCooldown.reset();
	}
	public boolean use(Point p, Engine engine) {
		//System.out.println("use(): CD REMAINING = " + useCooldown.getRemaining());
		if(!useCooldown.offCooldown())return false;
		//System.out.println("\tuseCooldown.offCooldown(): " + useCooldown.offCooldown());
		Zone z = engine.getZone();
		Point src = RSP.getPlayer().getLoc();

		engine.add(new Hook(src, p));
		useCooldown.reset();
		return true;
	}

	public void tick(Engine engine) {
		//System.out.println("tick(): CD REMAINING = " + useCooldown.getRemaining());
		useCooldown.tick();
	}

	public void draw(float sx, float sy, float z, Graphics g) {
		g.setColor(Color.green);
		Player player = RSP.getPlayer();
		g.fillRect((player.getX() - sx)*z, (player.getY()-sy)*z, 15.0f * z, 15.0f * z);
		if(useCooldown.offCooldown()){
			g.setColor(Color.gray);
			g.fillRect((player.getX() - sx + 4)*z, (player.getY()-sy)*z, 8.0f * z, 8.0f * z);
		}
	}
	public float getCooldownRemaining(){
		return useCooldown.getRemaining()/(2.0f*Constants.TICKS_PER_SECOND);
	}
}
