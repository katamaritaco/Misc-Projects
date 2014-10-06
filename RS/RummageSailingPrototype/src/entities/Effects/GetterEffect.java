package entities.Effects;

import entities.Entity;

/**
 * Created with IntelliJ IDEA.
 * User: zadjii
 * Date: 4/8/13
 * Time: 4:12 PM
 * To change this template use File | Settings | File Templates.
 */
public abstract class GetterEffect extends Effect {

	protected float angle;

	public float getAngle() {
		return angle;
	}
	public void setAngle(float angle) {
		this.angle = angle;
	}

}
