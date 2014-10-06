import java.io.*;
import java.util.*;


public class Test {

	static List<String> maleTestSelections = new ArrayList<String>();
	static List<String> femaleTestSelections = new ArrayList<String>();

	static ArrayList<Integer> maleIndices = new ArrayList<Integer>();
	static ArrayList<Integer> femaleIndices = new ArrayList<Integer>();

	static double unknownWords = 0;
	static double totalWords = 0;


	public static void selectSetIndices(ArrayList<Integer> maleIndicesTrain,
			ArrayList<Integer> femaleIndicesTrain, List<String> maleSelections, List<String> femaleSelections) {

		maleTestSelections = maleSelections;
		femaleTestSelections = femaleSelections;

		boolean isSupposedToBeInTest;
		//find male indices
		for(int i = 0; i < maleSelections.size(); i++){
			isSupposedToBeInTest = true;
			for(int j = 0; j < maleIndicesTrain.size(); j++){
				if(maleIndicesTrain.contains(i)){
					isSupposedToBeInTest = false;
					break;
				}
			}
			if(isSupposedToBeInTest){
				maleIndices.add(i);
			}
		}

		//find female indices
		for(int i = 0; i < femaleSelections.size(); i++){
			isSupposedToBeInTest = true;
			for(int j = 0; j < femaleIndicesTrain.size(); j++){
				if(femaleIndicesTrain.contains(i)){
					isSupposedToBeInTest = false;
					break;
				}
			}
			if(isSupposedToBeInTest){
				femaleIndices.add(i);
			}
		}

		System.out.println("Male train selections: \t\t" + maleIndicesTrain.toString());
		System.out.println("Male test selections: \t\t" + maleIndices.toString());
		System.out.println("Female train selections: \t" + femaleIndicesTrain.toString());
		System.out.println("Female test selections: \t" + femaleIndices.toString());

	}

	public static void analyze(HashMap<String, String[]> trainingMap) {
		// TODO Auto-generated method stub

		//		maleTestSelections

		for(int i = 0; i < maleIndices.size(); i++){
			System.out.println("Male Test #" + (i+1) + ": " + maleTestSelections.get(maleIndices.get(i)));
			String prediction = findProb(parseFile("books\\Male\\" + 
					maleTestSelections.get(maleIndices.get(i)) + ".txt"), trainingMap);
			System.out.println("Prediction: " + prediction + '\n');
			if(prediction.equals("Male")){
				GenderDetector.correctMalePredictions++;
			}
		}
		for(int i = 0; i < femaleIndices.size(); i++){
			System.out.println("Female Test #" + (i+1) + ": " + femaleTestSelections.get(femaleIndices.get(i)));
			String prediction = findProb(parseFile("books\\Female\\" + 
					femaleTestSelections.get(femaleIndices.get(i)) + ".txt"), trainingMap);
			System.out.println("Prediction: " + prediction + '\n');
			if(prediction.equals("Female")){
				GenderDetector.correctFemalePredictions++;
			}
		}

		GenderDetector.totalWords += totalWords;
		GenderDetector.unknownWords += unknownWords;

	}

	private static String findProb(HashMap<String, String[]> testMap, HashMap<String, String[]> trainingMap) {
		// TODO Auto-generated method stub

		double maleProbability = 0, femaleProbability = 0;

		for (Map.Entry<String, String[]> entry : testMap.entrySet()) {
			String key = entry.getKey();
			String[] values = entry.getValue();
			totalWords++;
			if(!trainingMap.containsKey(key)){
				unknownWords++;
			}
			else{

				maleProbability += Math.log((double)(Double.parseDouble(values[0]) + .0000001) / 
						((double)Double.parseDouble(trainingMap.get(key)[0]) + .0000001));

				femaleProbability += Math.log(((double)Double.parseDouble(values[2]) + .0000001) / 
						((double)Double.parseDouble(trainingMap.get(key)[2]) + .0000001));

			}
		}
		System.out.println("Male Probability: " + maleProbability + "\tFemale Probability: " + femaleProbability);

		if(maleProbability > femaleProbability){
			GenderDetector.totalMaleTests++;
			return "Male";
		}
		else if(maleProbability <= femaleProbability){
			GenderDetector.totalFemaleTests++;
			return "Female";
		}
		else{
			return "Error?";
		}

	}

	//shameless stolen from Training Class
	private static HashMap<String, String[]> parseFile(String fileName){
		HashMap<String, String[]> localMap = new HashMap<String, String[]>();
		boolean isMale = false;

		if(fileName.contains("M")){
			isMale = true;
		}

		try {
			Scanner in = new Scanner(new File (fileName));

			while(in.hasNext()){				
				String currentToken = in.next();
				currentToken = currentToken.toLowerCase().replaceAll("[^a-zA-Z ]", "");

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
		}


		return localMap;
	}


}
