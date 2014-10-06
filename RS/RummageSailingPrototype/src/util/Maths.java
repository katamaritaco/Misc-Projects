package util;

import entities.Entity;
import org.lwjgl.util.Point;

public class Maths {
	public static double dist(Entity i, Entity j){
		return Maths.dist(i.getLoc(), j.getLoc());
	}
	public static double dist(Point i, Point j){
		return Math.sqrt(
			( Math.pow((i.getX() - j.getX()), 2) + Math.pow((i.getY() - j.getY()), 2) )
		);
	}
	public static int intDist(Point i, Point j){
		return (int)(Math.sqrt(
				( Math.pow((i.getX() - j.getX()), 2) + Math.pow((i.getY() - j.getY()), 2) )
		));
	}

	public static double dist(float f, float g, float h, float i) {
		if (f > g) {
			if (h > i) {
				return Math.sqrt(((Math.pow((f - g), 2)) + (Math.pow((h - i), 2))));
			} else {
				return Math.sqrt(((Math.pow((f - g), 2)) + (Math.pow((i - h), 2))));
			}
		} else {
			if (h > i) {
				return Math.sqrt(((Math.pow((g - f), 2)) + (Math.pow((h - i), 2))));
			} else {
				return Math.sqrt(((Math.pow((g - f), 2)) + (Math.pow((i - h), 2))));
			}
		}
	}
}
