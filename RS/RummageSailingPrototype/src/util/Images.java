package util;

import org.newdawn.slick.*;
import org.newdawn.slick.font.effects.ColorEffect;

import java.awt.Font;
import java.util.HashMap;

public class Images {


	public static Image companyLogo;
	public static Image menuScreen;
	public static Image earthMap;

	public static Image ahab000;

	public static Image raft;
	public static Image sailboat;

	public static Image shadow;
	public static Image selectedArrow;
	public static Image cursor;
	public static Image panelBG;

	public static Image blueBG;
	public static Image greenBG;
	public static Image redBG;
	public static Image yellowBG;
	public static Image mendotaBG;
	public static Image egyptBG;

	public static Image toiletSeat;
	public static Image bottle;
	public static Image coral;
	public static Image lawyerLamp;
	public static Image tv;

	public static Image notification;
	public static Image notification02;

    @SuppressWarnings("unchecked")
    public static void init() throws SlickException {

		companyLogo = new Image("img/mainMenu/BGDLogoPrototype.png");
		//menuScreen = new Image("img/mainMenu/menuScreen.png");
		menuScreen = new Image("img/mainMenu/RummageSailingLogoBig.jpg");
		earthMap = new Image("img/mainMenu/earth001.png");

	    panelBG = new Image("img/panels/panelBG.png");
	    panelBG.setFilter(Image.FILTER_NEAREST);


	    ahab000 = new Image("img/other/bgdAhabFinalFromPS.png");
	    ahab000.setFilter(Image.FILTER_NEAREST);


	    raft = new Image("img/boats/bgdBeginnerBoat.png");
	    raft.setFilter(Image.FILTER_NEAREST);

	    sailboat = new Image("img/boats/bgdSailboat.png");
	    sailboat.setFilter(Image.FILTER_NEAREST);

	    blueBG = new Image("img/zones/blueBG.png");
	    blueBG.setFilter(Image.FILTER_NEAREST);
	    redBG = new Image("img/zones/redBG.png");
	    redBG.setFilter(Image.FILTER_NEAREST);
	    greenBG = new Image("img/zones/greenBG.png");
	    greenBG.setFilter(Image.FILTER_NEAREST);
	    yellowBG = new Image("img/zones/yellowBG.png");
	    yellowBG.setFilter(Image.FILTER_NEAREST);
	    mendotaBG = new Image("img/zones/mendota_BG.png");
	    mendotaBG.setFilter(Image.FILTER_NEAREST);
	    egyptBG = new Image("img/zones/egypt_BG.png");
	    egyptBG.setFilter(Image.FILTER_NEAREST);

	    toiletSeat = new Image("img/items/bgdToiletSeat.png");
	    toiletSeat.setFilter(Image.FILTER_NEAREST);

	    bottle = new Image("img/items/bgdBottle.png");
	    bottle.setFilter(Image.FILTER_NEAREST);

	    coral = new Image("img/items/bgdCoral.png");
	    coral.setFilter(Image.FILTER_NEAREST);

	    lawyerLamp = new Image("img/items/bgdLawyerLamp.png");
	    lawyerLamp.setFilter(Image.FILTER_NEAREST);

	    tv = new Image("img/items/bgdTV.png");
	    tv.setFilter(Image.FILTER_NEAREST);


	    notification = new Image("img/panels/notification.png");
	    notification.setFilter(Image.FILTER_NEAREST);
	    notification02 = new Image("img/panels/notification002.png");
	    notification02.setFilter(Image.FILTER_NEAREST);

    }
}
