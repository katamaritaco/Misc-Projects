package entities.Effects;

import entities.Entity;
import game.Engine;
import org.newdawn.slick.Graphics;

public abstract class Effect extends Entity {



		public abstract void draw(float sx, float sy, float zoom, Graphics g);
		public abstract void tick(Engine e);
		public void tick(){
			System.err.println("YOU SHOULD REALLY BE USING Effect.tick(Engine engine)," +
					"\n NOT tick()!!!! NOW I WILL CRASH MWAH HAHAHAHA");
			throw new RuntimeException();
		}
		public abstract boolean shouldBeRemoved();
}
