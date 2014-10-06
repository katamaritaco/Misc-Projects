package game;

import entities.Entity;
import org.lwjgl.util.Point;
import org.newdawn.slick.Color;
import org.newdawn.slick.Graphics;

import util.Font;



public class Particle extends Entity {

    public Particle(int x, int y, int dx, int dy,
                    int time, Color color, boolean isAString,
                    boolean isASquare, boolean isACircle, float size, String text) {
        this.color = color;
        duration = new Cooldown(time);
        duration.reset();
        this.isAString = isAString;
        this.isASquare = isASquare;
        this.isACircle = isACircle;
        this.size = size;
        this.text = text;
        this.setXY(x, y);
        this.setDX(dx);
        this.setDY(dy);
    }

    private static final long serialVersionUID = 1L;

    private Color color;
    private Cooldown duration;
    private boolean isAString;
    private boolean isASquare;
    private boolean isACircle;
    private float size;
    private String text;

    public void tick() {
        duration.tick();
        this.setXY(this.getX() + this.getDX(), this.getY() + this.getDY());
    }


    public boolean isOff() {
        return duration.offCooldown();
    }


    public void draw(float sx, float sy, Graphics g, float zoom) {
        if (isAString) {
            Font.drawParticleFontString(text, (getX() - sx) * zoom, (getY() - sy) * zoom, color);
        }
        if (isASquare) {
            g.setColor(color);
            g.fillRect((getX() - sx) * zoom, (getY() - sy) * zoom, size * zoom, size * zoom);
            return;
        }
        if (isACircle) {
            g.setColor(color);
            g.fillOval((getX() - sx) * zoom, (getY() - sy) * zoom, size * zoom, size * zoom);
            return;
        }
    }





    public static Particle newTreeParticle(Entity entity) {
        int x = (int)entity.getX();
        int y = (int)entity.getY();
        int dx = (int) ((Math.random() * 4) - 2);
        int dy = (int) ((Math.random() * 2) + 1);
        return new Particle(
                x + ((int) (Math.random() * 16)),
                y + ((int) (Math.random() * 16)),
                dx, dy,
                15,
                new Color(114, 76, 2),
                false, true, false,
                6.0f, ""
        );
    }

    private static final Color treeGreen = new Color(13, 140, 45);

    public static Particle newGreenTreeParticle(Entity entity) {
        int x = (int)entity.getX();
        int y = (int)entity.getY();
        int dx = (int) ((Math.random() * 4) - 2);
        int dy = (int) ((Math.random() * 2) + 1);
        return new Particle(
                x + ((int) (Math.random() * 16)),
                y + ((int) (Math.random() * 16)),
                dx, dy,
                15,
                treeGreen,
                false, true, false,
                6.0f, ""
        );
    }

    public static Particle newTreeParticle(int gx, int gy, int dx, int dy) {
        return new Particle(
                gx * 16 + ((int) (Math.random() * 16)),
                gy * 16 + ((int) (Math.random() * 16)),
                dx, dy,
                15,
                new Color(114, 76, 2),
                false, true, false,
                6.0f, ""
        );

    }


    public static Particle newAttack(Point point) {
        return new Particle(
                point.getX() * 16,
                point.getY() * 16,
                0,
                0,
                50,
                new Color(1.0f, 1.0f, 1.0f, 0.5f),
                false, true, false,
                16, "");
    }


}
