import java.io.*;
import java.util.*;


public class Training {

	//due to last minute changes, this is quite spaghetti...
	public static ArrayList<Integer> maleIndices = new ArrayList<Integer>();
	public static ArrayList<Integer> femaleIndices = new ArrayList<Integer>();
	public static HashMap<String, String[]> masterMap = new HashMap<String, String[]>();

	public static HashMap<String, String[]> buildSet(List<String> maleSelections, List<String> femaleSelections) {
		System.out.println("Start Building Set...");

		selectSetIndices(maleSelections.size(), femaleSelections.size());


		parseFiles(maleSelections, femaleSelections);


//		for (Map.Entry<String, String[]> entry : masterMap.entrySet()) {
//			String key = entry.getKey();
//			String[] values = entry.getValue();
//			System.out.println("Master Key: " + key + "; Master Value Male: " + 
//					values[0] + " " + values[1] + " Master Value Female:" + values[2] + " " + values[3]);
//		}

		System.out.println("Finished Building Set");
		System.out.println("================================================================================");
		return masterMap;
	}

	private static boolean parseFiles(List<String> maleSelections, List<String> femaleSelections){
		System.out.println("Start male files...");
		for(int i = 0; i < maleIndices.size(); i++){
			String fileName = "books\\Male\\" + maleSelections.get(maleIndices.get(i)) + ".txt";
			parseFile(fileName);
		}
		System.out.println("Start female files...");
		for(int i = 0; i < femaleIndices.size(); i++){
			String fileName = "books\\Female\\" + femaleSelections.get(femaleIndices.get(i)) + ".txt";
			parseFile(fileName);
		}

		return false;
	}

	private static boolean parseFile(String fileName){
		HashMap<String, String[]> localMap = new HashMap<String, String[]>();
		boolean isMale = false;

		if(fileName.contains("M")){
			isMale = true;
		}

		try {
			Scanner in = new Scanner(new File (fileName));

			while(in.hasNext()){				
				String currentToken = in.next();
				//Not the best way, doesn't handle splits yet
				currentToken = currentToken.toLowerCase().replaceAll("[^a-zA-Z ]", " ");

				String[] values = new String[4];

				if(isMale){
					values[0] = "1";//totalCount
					if(localMap.containsKey(currentToken)){
						values[0] = String.valueOf(Integer.parseInt(localMap.get(currentToken)[0].toString()) + 1);
					}

					values[1] = "1"; //numberOfVolumes

					values[2] = "0";
					values[3] = "0";

					//System.out.println(currentToken + " " + values[0] + " " + values[1] + " " + values[2]);
				}
				else{
					values[2] = "1";//totalCount
					if(localMap.containsKey(currentToken)){
						values[2] = String.valueOf(Integer.parseInt(localMap.get(currentToken)[2].toString()) + 1);
					}

					values[3] = "1"; //numberOfVolumes

					values[0] = "0";
					values[1] = "0";

					//System.out.println(currentToken + " " + values[0] + " " + values[1] + " " + values[2]);
				}

				localMap.put(currentToken, values);


			}

		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		}

		exportToFile(fileName, localMap);

		return true;
	}

	private static boolean exportToFile(String fileName, HashMap<String, String[]> localMap){

		//iterate through the localMap
		for (Map.Entry<String, String[]> entry : localMap.entrySet()) {
			String key = entry.getKey();
			String[] values = entry.getValue();

			// values[1] = String.valueOf(Integer.parseInt(localMap.get(currentToken)[1].toString()) + 1);

			String[] masterValues = new String[4];
			if(!masterMap.containsKey(key)){
				masterValues[0] = String.valueOf(Integer.parseInt(values[0].toString()));
				masterValues[1] = String.valueOf(Integer.parseInt(values[1].toString()));
				masterValues[2] = String.valueOf(Integer.parseInt(values[2].toString()));
				masterValues[3] = String.valueOf(Integer.parseInt(values[3].toString()));
			}
			else{
				//totalCount Male && totalVolume Male
				masterValues[0] = String.valueOf(Integer.parseInt(values[0].toString())  
						+ Integer.parseInt(masterMap.get(key)[0].toString()));
				masterValues[1] = String.valueOf(Integer.parseInt(values[1].toString()) 
						+ Integer.parseInt(masterMap.get(key)[1].toString()));
				//totalCount Female && totalVolume Female
				masterValues[2] = String.valueOf(Integer.parseInt(values[2].toString())  
						+ Integer.parseInt(masterMap.get(key)[2].toString()));
				masterValues[3] = String.valueOf(Integer.parseInt(values[3].toString()) 
						+ Integer.parseInt(masterMap.get(key)[3].toString()));
			}

			masterMap.put(key, masterValues);

		}

		return false;
	}

	private static void selectSetIndices(int maleSelectionsSize, int femaleSelectionsSize){

		Random rand = new Random();
		int r = 0;

		//male selections
		while(true){

			r = rand.nextInt(maleSelectionsSize);
			if(!maleIndices.contains(r)){
				maleIndices.add(r);
			}

			if(maleIndices.size() == 8){
				break;
			}

		}

		//female selections
		while(true){

			r = rand.nextInt(femaleSelectionsSize);
			if(!femaleIndices.contains(r)){
				femaleIndices.add(r);
			}

			if(femaleIndices.size() == 8){
				break;
			}

		}

		Test.selectSetIndices(maleIndices, femaleIndices, 
				GenderDetector.maleSelections, GenderDetector.femaleSelections);

	}

}
