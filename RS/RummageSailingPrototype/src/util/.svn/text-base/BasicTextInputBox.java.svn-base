package util;

import org.newdawn.slick.Color;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Input;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;


public class BasicTextInputBox {

	private static boolean cursorOn = false;
	private static ArrayList<Character> chars = new ArrayList<Character>();
	private static Timer cursorTick = new Timer(500, new ActionListener() {
		public void actionPerformed(ActionEvent e) {
			cursorOn = !cursorOn;
		}
	});

	public void keyPressed(int key, char c){
		if (key == Input.KEY_BACK) {
			if (chars.size() != 0) {
				chars.remove(chars.size()-1);
			}
		} else {
			if (Constants.isAcceptedCharacter(c)) {
				chars.add(c);
			}
		}
	}
	public void draw(int x, int y, int w, int h, Graphics g){
		g.setColor(Color.white);
		g.fillRect(x, y, w, h);
		g.setColor(Color.black);
		g.drawRect(x, y, w, h);
		if (cursorOn){
			g.setColor(Color.black);
			g.fillRect(x+5 + 22 * chars.size(), y+36, 25, 2);
		}
		for (int i = 0; i < chars.size(); ++i) {
			Font.drawNewGameInputFontString(Character.toString(chars.get(i)), x+5 + 22 * i, y+5);
		}
	}
	public String getString(){
		String returnString ="";
		for(Character character : chars){
			returnString+=character;
		}
		return returnString;
	}
	public void enable(){
		cursorOn = true;
		cursorTick.start();
	}
	public boolean enabled(){return cursorTick.isRunning();}
	public void disable(){
		cursorTick.stop();
		cursorOn = false;
	}
	public int size(){return chars.size();}
	public void clear(){chars.clear();}

}
