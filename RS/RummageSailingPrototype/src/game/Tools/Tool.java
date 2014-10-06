package game.Tools;

import game.Engine;
import org.newdawn.slick.Graphics;

public abstract class Tool {
	protected float weight = 0.0f;
	public abstract void tick(Engine engine);
	public abstract void draw(float sx, float sy, float z, Graphics g);
	public float getWeight(){
		return weight;
	}

	/**
	 * Returns the following fraction, [0.0, 1.0]
	 * Time until off cooldown / total cooldown length
	 * @return
	 */
	public abstract float getCooldownRemaining();
}
