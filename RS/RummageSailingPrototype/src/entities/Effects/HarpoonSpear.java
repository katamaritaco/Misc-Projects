package entities.Effects;

import entities.Entity;
import entities.Player;
import entities.ItemEntity;
import game.Engine;
import game.RSP;
import org.lwjgl.util.Point;
import org.lwjgl.util.Rectangle;
import org.newdawn.slick.Color;
import org.newdawn.slick.Graphics;
import util.Maths;

import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: zadjii
 * Date: 2/2/13
 * Time: 4:26 AM
 * To change this template use File | Settings | File Templates.
 */
public class HarpoonSpear extends GetterEffect {
	private ItemEntity attachedItem = null;
	private static final Color lineColor = new Color(.6f,.8f,1.0f,.25f);
	private boolean hasReversed = false;
	private float distanceTraveled = 0.0f;

	//These next two variables are debug-only, and should be removed for the release:
	//Point src;
	//Point tgt;

	public HarpoonSpear(Point src, Point tgt){

		this.w = 10;
		this.h = 10;
		this.x = src.getX();
		this.y = src.getY();
		this.speed = 6.0f;
		double distX = tgt.getX() - x;
		double distY = tgt.getY() - y;
//		double distX = thisX - targetX;
//		double distY = thisY - targetY;
		this.angle = (float)(Math.toDegrees(Math.atan2(distY, distX)));
		//dx = ((float)((distX / Maths.dist(src, tgt))) * speed);
		//dy = ((float)((distY / Maths.dist(src, tgt))) * speed);

		Player player = RSP.getPlayer();
		//dx = (float)(-((player.getX()-tgt.getX()) / Maths.dist(tgt, player.getLoc())) * (speed/2.0f));
		//dy = (float)(-((player.getY()-tgt.getY()) / Maths.dist(tgt, player.getLoc())) * (speed/2.0f));
		dx = (float)(speed * Math.cos(Math.toRadians(angle)));
		dy = (float)(speed * Math.sin(Math.toRadians(angle)));
		//System.out.println(dx+","+dy);
		//System.out.println(angle);
		//this.src = new Point(src);
		//this.tgt = new Point(tgt);
	}

	public void draw(float sx, float sy, float z, Graphics g){
		g.setColor(Color.gray);
		g.fillRect((x - sx -(w)) * z, (y - sy -(h)) * z, w * z, h * z);
		g.setColor(lineColor);
		g.setLineWidth(3.0f);
		Player player = RSP.getPlayer();
		g.drawLine((x - sx -(w/2)) * z, (y - sy -(h/2)) * z, (player.getX() - sx)*z, (player.getY()-sy)*z);
		g.setLineWidth(1.0f);

		if(attachedItem!= null){
			attachedItem.draw(sx, sy, z, g);
		}

		//old code for drawing a RotatedProjectileEffect:
		//g.rotate((getAbsX() - sx)*zoom, (getAbsY() - sy)*zoom, (float)angle);
		//image.draw((getAbsX() - sx - (getWidth()/2))*zoom, (getAbsY() - sy - (getHeight()/2))*zoom, (getWidth())*zoom, (getHeight())*zoom);
		//g.rotate((getAbsX() - sx)*zoom, (getAbsY() - sy)*zoom, (float)-angle);
	}


	public void tick(Engine engine){

		Point initial = this.getLoc();
		x += dx;
		y += dy;
		distanceTraveled += Maths.dist(initial, this.getLoc());

		//System.out.println(distanceTraveled);

		if(attachedItem == null){
			Rectangle bounds = new Rectangle((int)(this.x-12), (int)(this.y-12), 24, 24);
			bounds = this.getBounds();
//			List list = engine.getZone().getItems(bounds);
//			System.out.println(list.size());
			for(Entity entity : engine.getZone().getItems(bounds)){
				if(!this.getBounds().intersects(entity.getBounds()))continue;
				ItemEntity itemEntity = (ItemEntity)entity;
				attachedItem = itemEntity;
				this.speed/=(attachedItem.getItem().getMass()/2);
				reverseDirection();

				attachedItem.setDX(dx);
				attachedItem.setDY(dy);

				//System.out.println("Caught Item!");
				engine.addToBeRemoved(attachedItem);
				return;
			}
			if(!hasReversed && distanceTraveled > 450.0f){
				reverseDirection();
			}
		}else{
			//attachedItem.setLoc(this.getLoc());

			attachedItem.setDX(dx);
			attachedItem.setDY(dy);

			attachedItem.tick();
		}

	}

	@Override
	public boolean shouldBeRemoved() {
		if(Maths.dist(this, RSP.getPlayer()) < 24.0f && hasReversed){
			//add items to players inventory, and then return true.
			if(attachedItem!=null)RSP.getPlayer().addItem(attachedItem.getItem());
			return true;
		}
		return false;  //To change body of implemented methods use File | Settings | File Templates.
	}

	private void reverseDirection(){
		if(hasReversed)return;
		float oldDX = dx;
		float oldDY = dy;
		Player player = RSP.getPlayer();
		dx = (float)(-((this.getX()-player.getX()) / Maths.dist(this, player)) * (speed/4.0f));
		dy = (float)(-((this.getY()-player.getY()) / Maths.dist(this, player)) * (speed/4.0f));

		//this.dx = -dx;
		//this.dy = -dy;
		//System.out.println(dx+","+dy+"\t"+oldDX+","+oldDY);
		hasReversed = true;
		//System.out.println("REVERSED DIRECTION");
	}
}
