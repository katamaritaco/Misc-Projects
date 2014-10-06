package entities;

import entities.Effects.Hook;
import game.Boats.Boat;
import game.Boats.Raft;
import game.Cooldown;
import game.Engine;
import game.RSP;
import game.Tools.GetterTool;
import game.Tools.Harpoon;
import game.Tools.OldRod;
import game.Tools.Tool;
import game.items.Item;
import org.lwjgl.util.Point;
import org.newdawn.slick.Color;
import org.newdawn.slick.Graphics;
import util.Images;

import java.util.ArrayList;

public class Player extends Entity{

	//GetterTool tool;

	private int green = 0;
	private int greed = 0;
	private int money = 0;
	private ArrayList<Tool> tools = new ArrayList<Tool>();

	private Boat boat;

	private int activeTool = 0;

	public Player(){
		this.x = RSP.DEFAULT_SCREEN_WIDTH/2;
//		this.y = RSP.getEngine().getSeaHeight();
		this.w = 48;
		this.h = 64;
		//tool = new OldRod();
		this.tools.add(new OldRod());
		this.tools.add(new Harpoon());
		this.boat = new Raft();
		this.boat.equipGetter((GetterTool)tools.get(0), 0);
		this.boat.equipGetter((GetterTool)tools.get(1), 1);
		greed = green = money = 0;
	}

	public void tick(Engine engine){
		super.tick();
		this.boat.tick(engine);
		//this.tool.tick(engine);
	}

	public void draw(float sx, float sy, float z, Graphics g){
		this.boat.drawBack(sx, sy, z, g);
		g.setColor(Color.magenta);
		Images.ahab000.draw((x - sx - w/2) * z, (y - (3*h)/4 - sy) * z, w * z, h * z);
		//g.fillOval((x - sx - w/2) * z, (y - (3*h)/4 - sy) * z, w * z, h * z);
		this.boat.drawFront(sx, sy, z, g);
		//this.hook.draw(sx,sy,z,g);
		//this.tool.draw(sx,sy,z,g);
	}
	public boolean useGetter(Point tgt, Engine engine){
		//return tool.use(tgt, engine);
		return boat.useGetter(activeTool, tgt, engine);
	}

	public int getGreen() {return green;}
	public void setGreen(int green) {this.green = green;}
	public int getGreed() {return greed;}
	public void setGreed(int greed) {this.greed = greed;}
	public int getMoney() {return money;}
	public void setMoney(int money) {this.money = money;}
	public void addGGM(int green, int greed, int money){
		this.green+=green;
		this.greed+=greed;
		this.money+=money;
	}
	public void addGG(int green, int greed){
		this.green+=green;
		this.greed+=greed;
	}
	public void addItem(Item item){
		this.green += item.getGreen();
		this.greed += item.getGreed();
		this.money += item.getMoney();
	}
	public ArrayList<Tool> getTools(){return this.tools;}
	public void setActiveTool(int index){this.activeTool = index;}

}
