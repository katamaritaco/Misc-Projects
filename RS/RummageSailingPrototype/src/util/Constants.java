package util;

import entities.Player;
import game.RSP;
import org.newdawn.slick.Color;

public class Constants {
	public static final int TICKS_PER_SECOND = 60;


	public static final char[] acceptedCharacters = new char[] {
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
		'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
		'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
		'z', 'x', 'c', 'v', 'b', 'n', 'm',
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		'~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=',
		':', ';', '\'', '"', '<', '>', '?'
	};

	public static boolean isAcceptedCharacter(char c) {
		for (char chr : acceptedCharacters) {
			if (chr == c) return true;
		}
		return false;
	}
	public static final Color greenColor = new Color(0.0f,1.0f,0.0f,1.0f);
	public static final Color greedColor = new Color(1.0f,1.0f,0.0f,1.0f);
	public static final Color moneyColor = new Color(0.4f,1.0f,0.0f,1.0f);
	public static void drawScores(){
		Font.drawMonospacedFontString("Green: " + RSP.getPlayer().getGreen(),10,00,18,Constants.greenColor);
		Font.drawMonospacedFontString("Greed: " + RSP.getPlayer().getGreed(),10,18,18,Constants.greedColor);
		Font.drawMonospacedFontString("Money: " + RSP.getPlayer().getMoney(),10,36,18,Constants.moneyColor);

	}
}
