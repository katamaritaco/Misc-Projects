//package twitterStuff;
//
//import com.twilio.sdk.TwilioRestClient;
//import com.twilio.sdk.TwilioRestException;
//import com.twilio.sdk.resource.factory.SmsFactory;
//import com.twilio.sdk.resource.instance.Sms;
//import com.twilio.sdk.resource.list.SmsList;
//import java.util.HashMap;
//import java.util.Map;
//
//public class TextMessaging {
//	
//	public static final String ACCOUNT_SID = "AC27f27f08614271df598a54b4e8ab793f";
//	public static final String AUTH_TOKEN = "5ef7f7879801bc2d42f0f7c6a53bbc4e";
//	  
//	public static void main(String[] args) throws TwilioRestException{
//		  
//		    TwilioRestClient client = new TwilioRestClient(ACCOUNT_SID, AUTH_TOKEN);
//		 
//		    // Build a filter for the SmsList
//		    Map<String, String> params = new HashMap<String, String>();
//		    params.put("Body", "Test text from Java!");
//		    params.put("To", "+19205741375");
//		    params.put("From", "+19203514761");
//		 
//		    SmsFactory messageFactory = client.getAccount().getSmsFactory();
//		    Sms message = messageFactory.create(params);
//		    System.out.println(message.getSid());
//	}
//}
