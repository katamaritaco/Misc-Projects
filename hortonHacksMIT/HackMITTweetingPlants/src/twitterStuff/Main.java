package twitterStuff;

import java.io.*;
import java.net.*;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import gnu.io.CommPort;

import winterwell.jtwitter.OAuthSignpostClient;
import winterwell.jtwitter.*;

import tweetSelection.tweetSelect;

import java.util.*;
import java.io.*;

public class Main {

	
	static String consumerKey = "h2uWk7fgPgQ3MynvchEg";
	static String consumerSecret = "44GkMpRE2XcMsDPbla5GxVDGbCYmvNOqfedkwKHyc7w";
	static String accessToken = "1938581365-E263zeV3UhB8iCvDX8p5OveQsGgj0GlTPhuqUMf";
	static String accessTokenSecret = "7QAzC9JnVrhqB0v0ds7Oqa2d6fxsw8qxHyKSCD0U";
	
	static OAuthSignpostClient oauthClient = new OAuthSignpostClient(consumerKey, 
			consumerSecret, accessToken,
			accessTokenSecret);
	
	static Twitter twitter = new Twitter("my-name", oauthClient);
	
//	public static void main(String[] args){
//		
//		
//
//		String status = "Testing authorization from our program! -The Humans #HackMIT";
//		System.out.println(status); //print the status
//		twitter.setStatus(status); //set the status
//	}
	
	static ArrayList<String> usedList = new ArrayList<String>();
	static int tweetCount = 0;
	
static String end_result = new String();
	
    public Main()
    {
        super();
    }
    
    void connect ( String portName ) throws Exception
    {
        CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
        if ( portIdentifier.isCurrentlyOwned() )
        {
            System.out.println("Error: Port is currently in use");
        }
        else
        {
            CommPort commPort = portIdentifier.open(this.getClass().getName(),2000);
            
            if ( commPort instanceof SerialPort )
            {
                SerialPort serialPort = (SerialPort) commPort;
                serialPort.setSerialPortParams(57600,SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
                
                InputStream in = serialPort.getInputStream();
                OutputStream out = serialPort.getOutputStream();
                               
                (new Thread(new SerialWriter(out))).start();
                
                serialPort.addEventListener(new SerialReader(in));
                serialPort.notifyOnDataAvailable(true);

            }
            else
            {
                System.out.println("Error: Only serial ports are handled by this example.");
            }
        }     
    }
    
    public static void dataAction() throws IOException{
    	
    	oauthClient = new OAuthSignpostClient(consumerKey, 
    			consumerSecret, accessToken,
    			accessTokenSecret);
    	
    	twitter = new Twitter("my-name", oauthClient);
    	
    	//Have 10 tweets in the 'cooldown queue'
    	if (tweetCount > 10){
    		usedList.remove(0);
    	}
    	
    	System.out.println("end_result: " + end_result);

    	String debug = end_result.replace("\n", "").replace("\r", "");
    	


    	if(end_result.replace("\n", "").replace("\r", "").split(",").length >= 5){

    		
    		System.out.println("Passed");
    		
            String[] results = end_result.split(",");
            int lightAmount = Integer.parseInt(results[0]);
            int soundAmount = Integer.parseInt(results[1]);
            String direction = results[2];
            double humidity = Double.parseDouble(results[3]);
            double tempFahrenheit = Double.parseDouble(results[4]);
            int moisture = Integer.parseInt(results[5]);
            
        	tweetSelection.tweetSelect datSelection = new tweetSelection.tweetSelect();

        	String usedString = datSelection.selectATweet(usedList, lightAmount, soundAmount, direction, humidity, tempFahrenheit, moisture);
        	System.out.println("LightAmount: " + lightAmount);
        	end_result = "";
        	
        	
        	System.out.println(usedString);
        	
        	URL url = new URL(
        			"http://www.heymitch.com/hortontheplant/" + 
        			"?phrase=" + URLEncoder.encode(usedString, "UTF-8") +
        			"&temperature=" + URLEncoder.encode( Double.toString(tempFahrenheit), "UTF-8") + 
        			"&sound=" + URLEncoder.encode(Double.toString(soundAmount), "UTF-8") + 
        			"&direction=" + URLEncoder.encode(direction, "UTF-8") + 
        			"&humidity=" + URLEncoder.encode(Double.toString(humidity), "UTF-8") + 
        			"&light=" + URLEncoder.encode(Double.toString(lightAmount), "UTF-8") +
        			"&dirt=" + URLEncoder.encode(Integer.toString(moisture), "UTF-8")
        	 ); 
        	
        	URLConnection conn = url.openConnection();

    	    conn.getContent(); 
        	
        	usedList.add(usedString);
        	
        	
        	
        	twitter.setStatus(usedString);
        	tweetCount++;
        	System.out.println("Tweet Posted. Tweet Count: " + tweetCount);
        	
        	
        	
        	/*
        	 * Begin all of the Twitter actions (other than Setting Status which just happened
        	 * 1. Check if any new followers; if so, follow them too.
        	 * 2. Retweet any mentions 
        	 * 3. (Not started) Check mentions for positivity/negativity and deal with accordingl 
        	 */
        	
        	//Begin Twitter Step 1:
        	List<User> users = twitter.users().getFollowers();
        	for(User u: users){
        		if(!u.isFollowedByYou()){
        			//If they are following you but you are NOT following them...
        			twitter.users().follow(u); //follow them
        			//System.out.println(u.name);
        		}
        			
        	}
        	
        	List<Status> statuses = twitter.getMentions();
        	User temp;
        	
        	for(Status s: statuses){
        		temp = s.getUser(); 
        		twitter.setFavorite(s, true);
        		if(!temp.isFollowingYou())
        			twitter.users().follow(temp); //follow the user
        			
        	}
        	
        	
    		
    	} else{
    		System.out.println("Length: " + end_result.replace("\n", "").replace("\r", "").split(",").length);
    		System.out.println(Arrays.deepToString(end_result.replace("\n", "").replace("\r", "").split(",")));
    	}
    	
    	end_result = "";
    	
    	
    	
    }
    
    /**
     * Handles the input coming from the serial port. A new line character
     * is treated as the end of a block in this example. 
     */
    public static class SerialReader implements SerialPortEventListener 
    {
        private InputStream in;
        private byte[] buffer = new byte[1024];
        
        public SerialReader ( InputStream in )
        {
            this.in = in;
        }
        
        public void serialEvent(SerialPortEvent arg0) {
            int data;
          
            try
            {
                int len = 0;
                while ( ( data = in.read()) > -1 )
                {
                    if ( data == '\n' || data == '\r') {
                    	dataAction();
                        break;
                    }
                    buffer[len++] = (byte) data;
                }
                end_result += new String(buffer,0,len);
            }
            catch ( IOException e )
            {
                e.printStackTrace();
                System.exit(-1);
            }             
        }

    }

    /** */
    public static class SerialWriter implements Runnable 
    {
        OutputStream out;
        
        public SerialWriter ( OutputStream out )
        {
            this.out = out;
        }
        
        public void run ()
        {
            try
            {                
                int c = 0;
                while ( ( c = System.in.read()) > -1 )
                {
                    this.out.write(c);
                }                
            }
            catch ( IOException e )
            {
                e.printStackTrace();
                System.exit(-1);
            }            
        }
    }

    
    public static void main ( String[] args )
    {
        try
        {
            (new Main()).connect("COM3");  

        }
        catch ( Exception e )
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }



	
	
	
	

	
}
