package zones;

import entities.ItemEntity;
import game.Cooldown;
import game.Engine;
import game.RSP;
import org.newdawn.slick.Graphics;
import util.Constants;
import util.Images;

public class MendotaZone extends Zone {
	public MendotaZone(){
		float duration = 40 + (int)(Math.random()*10);
		zoneTimer = new Cooldown(Constants.TICKS_PER_SECOND * (duration));
		zoneTimer.reset();
	}

	public void addItem(Engine engine){
		if(RSP.getRand().nextDouble() < 0.0051){
			ItemEntity item = new ItemEntity(getRandomItem());
			item.setDXDYDZ((float)Math.random()*1.0f + 0.5f, 0, 0);
			item.setX(-10);
			item.setY((int)(Math.random() * engine.getSeaLevel()) + engine.getSeaHeight() + 50);
			items.add(item);
		}
	}
	public void drawBackground(float sx, float sy, float z, Graphics g){
		Images.mendotaBG.draw(sx, sy, RSP.DEFAULT_SCREEN_WIDTH, RSP.DEFAULT_SCREEN_HEIGHT);
	}
}
