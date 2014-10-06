package game.Tools;

import game.Engine;
import org.lwjgl.util.Point;

/**
 * Created with IntelliJ IDEA.
 * User: zadjii
 * Date: 4/8/13
 * Time: 6:28 PM
 * To change this template use File | Settings | File Templates.
 */
public abstract class GetterTool extends Tool{
	/**
	 * Returns true if this is the last "use" of the tool before it goes on CD.
	 * For example, a hook can be used once, but a vacuum has a "heat" mechanic.
	 * @return
	 */
	public abstract boolean use(Point p, Engine engine);
}
