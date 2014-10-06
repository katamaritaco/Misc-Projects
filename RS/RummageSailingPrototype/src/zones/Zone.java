package zones;

import entities.Effects.Effect;
import entities.Entity;
import entities.ItemEntity;
import game.Cooldown;
import game.Engine;
import game.RSP;
import game.items.*;
import org.lwjgl.util.Rectangle;
import org.newdawn.slick.Graphics;
import util.Constants;
import util.EntityMap;
import util.Images;

import java.util.ArrayList;

/**
 * Created with IntelliJ IDEA.
 * User: zadjii
 * Date: 1/7/13
 * Time: 1:32 PM
 * To change this template use File | Settings | File Templates.
 */
public class Zone {


	protected EntityMap items = new EntityMap();
	protected ArrayList<Effect> effects = new ArrayList<Effect>();
	protected ArrayList<ItemEntity> toBeRemovedItems = new ArrayList<ItemEntity>();
	//The amount of time remaining in the level.
	protected Cooldown zoneTimer;
	public Zone(){
		float duration = 20 + (int)(Math.random()*15);
		zoneTimer = new Cooldown(Constants.TICKS_PER_SECOND * (duration));
		zoneTimer.reset();
	}


	public ArrayList<Entity> getItems() {
		return items.getEntities();
	}
	public ArrayList<Entity> getItems(Rectangle rect) {
		return items.get(rect);
	}
	public ArrayList<Effect> getEffects() {
		return effects;
	}
	public void tick(Engine engine){
		zoneTimer.tick();
		for (Entity i : toBeRemovedItems) {
			items.getEntities().remove(i);
		}
		toBeRemovedItems.clear();

		items.reseed();
		ArrayList<Entity> temp = new ArrayList<Entity>();
		for(Entity item:items.getEntities()){
			item.tick();
			if(item.getY() > 1500)temp.add(item);
		}
		for (Entity i : temp) {
			items.getEntities().remove(i);
		}
		temp.clear();
		for(Effect effect:effects){
			effect.tick(engine);
			if(effect.shouldBeRemoved()){
				temp.add(effect);
			}

		}
		for(Entity e : temp){
			effects.remove(e);
		}
	}

	public void addItem(Engine engine){
		if(RSP.getRand().nextDouble() < 0.01){
			ItemEntity item = new ItemEntity(getRandomItem());
			item.setDXDYDZ((float)Math.random()*1.5f + 0.5f, 0, 0);
			item.setX(-10);
			item.setY((int)(Math.random() * engine.getSeaLevel()) + engine.getSeaHeight());
			items.add(item);
		}
	}
	public void drawBackground(float sx, float sy, float z, Graphics g){
		Images.blueBG.draw(sx, sy, RSP.DEFAULT_SCREEN_WIDTH, RSP.DEFAULT_SCREEN_HEIGHT);
	}
	public Cooldown getZoneTimer(){return zoneTimer;}

	/**
	 * Resets anything that might need to be reset upon the exit from a stage.
	 */
	public void reset(){
		this.zoneTimer.reset();
		this.items.clear();
		this.effects.clear();
	}
	public void addToBeRemoved(ItemEntity item){
		toBeRemovedItems.add(item);
	}
	public static Item getRandomItem(){
		switch ((int)(Math.random() * 5)){
			case 0:return new ToiletSeat();
			case 1:return new Bottle();
			case 2:return new TV();
			case 3:return new LawyerLamp();
			case 4:return new Coral();
		}
		throw new RuntimeException("Zone.getRandomItem(): You shouldn't have gotten here.");
		//return null;
	}
}
