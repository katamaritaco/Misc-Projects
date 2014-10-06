package weatherAPIZ;

import java.net.*;
import java.io.*;

import org.apache.commons.*;

public class weather{

	public boolean isWeatherGood() throws MalformedURLException, IOException{
		InputStream response = new URL("http://api.wunderground.com/api/5cfaadd65f3a7e60/conditions/q/MA/Cambridge.json").openStream();

		String convertedJson = convertStreamToString(response);//mfw parsing llelelelel

		if (convertedJson.contains("\"pressure_in\":\"29.82\"") || convertedJson.contains("\"pressure_in\":\"29.81\"") ||
				convertedJson.contains("\"pressure_in\":\"29.80\"") || convertedJson.contains("\"pressure_in\":\"29.79\"") || 
				convertedJson.contains("\"pressure_in\":\"29.78\"") || convertedJson.contains("\"pressure_in\":\"29.77\"") || 
				convertedJson.contains("\"pressure_in\":\"29.76\"") || convertedJson.contains("\"pressure_in\":\"29.75\"") || 
				convertedJson.contains("\"pressure_in\":\"29.74\"") || convertedJson.contains("\"pressure_in\":\"29.73\"") || 
				convertedJson.contains("\"pressure_in\":\"29.72\"") || convertedJson.contains("\"pressure_in\":\"29.71\"") || 
				convertedJson.contains("\"pressure_in\":\"29.70\"") || convertedJson.contains("\"pressure_in\":\"29.69\"")){
			return false;
		}
		
		return true;
	}

	
	static String convertStreamToString(java.io.InputStream is) {
	    java.util.Scanner s = new java.util.Scanner(is).useDelimiter("\\A");
	    return s.hasNext() ? s.next() : "";
	}

}
