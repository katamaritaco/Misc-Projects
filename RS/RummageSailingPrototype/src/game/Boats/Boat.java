package game.Boats;

import game.Engine;
import game.Tools.GetterTool;
import game.Tools.Tool;
import game.Tools.WeaponTool;
import org.lwjgl.util.Point;
import org.newdawn.slick.Graphics;

/**
 * A vessel by which Ahab travels the seas.
 *
 * Has a weight capacity that limits # of items.
 * Also has a max # of equippable getters & weapons.
 *
 * Max # of equippable tools is five getter&five weapons.
 * Pick wisely.
 *
 */
public abstract class Boat {

	protected float capacity;
	private float currentWeight = 0;
	protected int getterSlots = 1;
	protected int weaponSlots = 1;

	protected Tool[] getters = new Tool[5];
	protected Tool[] weapons = new Tool[5];

	public float getCurrentWeight(){return currentWeight;}
	public float getCapacity(){return capacity;}
	public int getGetterSlots(){return getterSlots;}
	public int getWeaponSlots(){return weaponSlots;}

	public abstract void tick(Engine engine);
	public abstract void drawBack(float sx, float sy, float z, Graphics g);
	public abstract void drawFront(float sx, float sy, float z, Graphics g);

	protected void tickTools(Engine engine){
		for(Tool t:getters)if(t!=null)t.tick(engine);
		for(Tool t:weapons)if(t!=null)t.tick(engine);
	}
	protected void drawTools(float sx, float sy, float z, Graphics g){
		for(Tool t:getters)if(t!=null)t.draw(sx, sy, z, g);
		for(Tool t:weapons)if(t!=null)t.draw(sx, sy, z, g);
	}
	public boolean useGetter(int index, Point tgt, Engine engine){
		if(this.getters[index]!=null){
			return ((GetterTool)(this.getters[index])).use(tgt, engine);
		}
		return false;
	}
	/*
	* We still need to be able to determine if the item they are equipping has
	* already been equipped (If so, de-equip and re-equip)
	*/
	public void equipGetter(GetterTool tool, int index){
		if(index>getterSlots){
			//play a sound indicating slot is unavailable.
			//return?
			return;
		}
		if(this.getters[index]==null){
			if(this.currentWeight + tool.getWeight() > capacity){
				//return here
				return;
			}
			else{
				this.getters[index] = tool;
				this.currentWeight += tool.getWeight();
			}
		}
		else{
			if(this.currentWeight + tool.getWeight() - getters[index].getWeight() > capacity){
				//return here
				return;
			}
			else{
				this.currentWeight -= getters[index].getWeight();
				this.getters[index] = tool;
				this.currentWeight += tool.getWeight();
			}
		}
	}
	public void equipWeapon(WeaponTool tool, int index){
		if(index>weaponSlots){
			//play a sound indicating slot is unavailable.
			//return?
			return;
		}
		if(this.weapons[index]==null){
			if(this.currentWeight + tool.getWeight() > capacity){
				//return here
				return;
			}
			else{
				this.weapons[index] = tool;
				this.currentWeight += tool.getWeight();
			}
		}
		else{
			if(this.currentWeight + tool.getWeight() - weapons[index].getWeight() > capacity){
				//return here
				return;
			}
			else{
				this.currentWeight -= weapons[index].getWeight();
				this.weapons[index] = tool;
				this.currentWeight += tool.getWeight();
			}
		}
	}
}
