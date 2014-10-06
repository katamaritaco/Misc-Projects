import java.io.*;
import java.util.*;

public class GenderDetector {
	
	static List<String> maleSelections = new ArrayList<String>();
	static List<String> femaleSelections = new ArrayList<String>();
	
	static double totalMaleTests = 0;
	static double totalFemaleTests = 0;
	static double correctFemalePredictions = 0;
	static double correctMalePredictions = 0;
	public static double unknownWords = 0;
	public static double totalWords = 0;

	private static HashMap<String, String[]> trainingMap = new HashMap<String, String[]>();


	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		for(int i = 0; i < 100; i++){
			run();

		}
	}
	
	//not generalized all too well, but whatever
	public static void parse(){				
		
		try {
			Scanner fileIn = new Scanner(new File("books\\Male\\master.txt"));
			while(fileIn.hasNextLine()){
				String s = fileIn.nextLine().replaceAll("\t", "");
				maleSelections.add(s);
			}
			
			fileIn = new Scanner(new File("books\\Female\\master.txt"));
			while(fileIn.hasNextLine()){
				String s = fileIn.nextLine().replaceAll("\t", "");
				femaleSelections.add(s);
			}

			fileIn.close();

		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}		

				
	}

	public static void run(){
		parse();

		trainingMap = Training.buildSet(maleSelections, femaleSelections);
		
		Test.analyze(trainingMap);

		printInfo();
		
		reset();
	}
	
	public static void printInfo(){
		System.out.println("Unknown words in test: " + (int)Test.unknownWords + 
				"\tTotal words in test: " + (int)Test.totalWords + 
				"\tWord Errors: " + (Test.unknownWords/Test.totalWords)*100);
		
		System.out.println("Unknown words Total: " + (int)unknownWords + 
				"\tTotal words Total: " + (int)totalWords + 
				"\tWord Errors Total: " + (unknownWords/totalWords)*100);

		System.out.println("Correct Male Predictions:\t" + (int)correctMalePredictions + " Total Male Tests:\t" 
				+ (int)totalMaleTests + " Male Accuracy:\t" + (correctMalePredictions/totalMaleTests)*100);
		System.out.println("Correct Female Predictions:\t" + (int)correctFemalePredictions+ " Total Female Tests:\t" 
				+ (int)totalFemaleTests + " Female Accuracy:\t" + (correctFemalePredictions/totalFemaleTests)*100);
		System.out.println("Correct Predictions:\t\t" + (int)(correctMalePredictions+correctFemalePredictions)
				+ " Total Tests:\t\t" + (int)(totalMaleTests+totalFemaleTests) + " Total Accuracy:\t" + 
				(correctMalePredictions+correctFemalePredictions)/(totalMaleTests+totalFemaleTests)*100);
	}
	
	public static void reset(){
		maleSelections.removeAll(maleSelections);// = new ArrayList<String>();
		femaleSelections.removeAll(femaleSelections);// = new ArrayList<String>();
		
		Training.maleIndices.removeAll(Training.maleIndices);// = new ArrayList<Integer>();
		Training.femaleIndices.removeAll(Training.femaleIndices);// = new ArrayList<Integer>();
		Training.masterMap.clear();// = new HashMap<String, String[]>();


		Test.maleTestSelections.removeAll(Test.maleTestSelections);// = new ArrayList<String>();
		Test.femaleTestSelections.removeAll(Test.femaleTestSelections);// = new ArrayList<String>();

		Test.maleIndices.removeAll(Test.maleIndices);// = new ArrayList<Integer>();
		Test.femaleIndices.removeAll(Test.femaleIndices);// = new ArrayList<Integer>();

		Test.unknownWords = 0;
		Test.totalWords = 0;

	}
	
}
