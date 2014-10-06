package game.items;

import org.newdawn.slick.Color;
import org.newdawn.slick.Graphics;

/**
 * An actual Item. The item is either in your inventory, or "in" an ItemEntity,
 * where an ItemEntity is the actual item in the ocean.
 */
public abstract class Item {

	protected float mass;
	protected int greedScore;
	protected int greenScore;

	protected int money = 0;

	protected float width;
	protected float height;

	public Item(){
		this.greenScore = (int)(Math.random() * 10);
		this.greedScore = (int)(Math.random() * 10);
		this.money = (int)(Math.random() * 10) + 1;
		this.mass = (int)(Math.random() * 10) + 1;

		this.width = (float)(Math.random()*15) + 25;
		this.height = (float)(Math.random()*15) + 25;
	}

	public int getGreen() {return greenScore;}
	public void setGreen(int green) {this.greenScore = green;}
	public int getGreed() {return greedScore;}
	public void setGreed(int greed) {this.greedScore = greed;}
	public int getMoney() {return money;}
	public void setMoney(int money) {this.money = money;}
	public float getMass() {return mass;}
	public void setMass(int mass) {this.mass = mass;}
	public abstract void draw(float sx, float sy, float z, Graphics g, float x, float y);
	public float getWidth() {return width;}
	public float getHeight() {return height;}
}
