package entities;

import game.items.Item;
import org.newdawn.slick.Color;
import org.newdawn.slick.Graphics;

public class ItemEntity extends Entity {
	private Item item;

	public ItemEntity(){
		this.w = (float)(Math.random()*15) + 25;
		this.h = (float)(Math.random()*15) + 25;
		//this.item = new Item();
	}
	public ItemEntity(Item item){
		this.item = item;
		this.w = item.getWidth();
		this.h = item.getHeight();
	}

	public void draw(float sx, float sy, float z, Graphics g){
//		g.setColor(Color.red);
//		g.fillOval((x - sx) * z, (y - sy) * z, w * z, h * z);
		this.item.draw(sx, sy, z, g, x, y);
	}

	public void tick(){
		this.x += dx;
		//attempted wave motion to the items.
		//this.dy = (float)((Math.random()*2 - 1)*(Math.sin((double)System.nanoTime())));
		this.y += dy;
		tickDZ();

	}
	public Item getItem(){
		return item;
	}

}
