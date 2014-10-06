package zones;

import entities.ItemEntity;
import game.Cooldown;
import game.Engine;
import game.RSP;
import org.newdawn.slick.Graphics;
import util.Constants;
import util.Images;

/**
 * Created with IntelliJ IDEA.
 * User: zadjii
 * Date: 4/18/13
 * Time: 9:25 PM
 * To change this template use File | Settings | File Templates.
 */
public class EgyptZone extends Zone{
	public EgyptZone(){
		float duration = 40 + (int)(Math.random()*10);
		zoneTimer = new Cooldown(Constants.TICKS_PER_SECOND * (duration));
		zoneTimer.reset();
	}

	public void addItem(Engine engine){
		if(RSP.getRand().nextDouble() < 0.03){
			ItemEntity item = new ItemEntity(getRandomItem());
			item.setDXDYDZ((float)Math.random()*3.5f + 0.5f, 0, 0);
			item.setX(-10);
			item.setY((int)(Math.random() * engine.getSeaLevel()) + engine.getSeaHeight());
			items.add(item);
		}
	}
	public void drawBackground(float sx, float sy, float z, Graphics g){
		Images.egyptBG.draw(sx, sy, RSP.DEFAULT_SCREEN_WIDTH, RSP.DEFAULT_SCREEN_HEIGHT);
	}
}
