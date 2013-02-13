package document;

import java.lang.reflect.Field;

public class Parameters {
	public static int test_time = 0;
	public static boolean test_result = true;
	public static String path_to_plans = "./plans";
	public static String path_to_images = "./images";
	public static String executer_service = "/executer";
	public static String path_to_lookup = "./plans/lookup.xml";
	public static String path_to_undo = "./.undo";
	public static String path_to_address = "./plans/TaskList.xml";
	public static String path_to_description = "./plans/TaskDescriptions.xml";
	public static String path_to_plans_on_executer = "{LOCALPATH}";
	public static boolean enableLinkConnection = true;
	public static boolean enableTaskIdRegeneration = false;
	
	
	
	public static boolean set(String key, String value) {
		Class<Parameters> pclass = Parameters.class;
		//System.out.println("class name : "+pclass.getName());
		try{
			Field pfield = pclass.getField(key);
			//System.out.println("  field name : "+pfield.getName());
			//System.out.println("  field type : "+pfield.getType().getName());
			if(pfield.getType().getName().equals(String.class.getName())){
				pfield.set(null, new String(value));
			}else
			if(pfield.getType().getName().equals(int.class.getName())){
				pfield.set(null, Integer.parseInt(value));
			}else
			if(pfield.getType().getName().equals(float.class.getName())){
				pfield.set(null, Float.parseFloat(value));
			}else
			if(pfield.getType().getName().equals(double.class.getName())){
				pfield.set(null, Double.parseDouble(value));
			}else
			if(pfield.getType().getName().equals(boolean.class.getName())){
				pfield.set(null, Boolean.parseBoolean(value));
			}else{
				System.out.println("Parameters.set"+key+","+value+")  Unknown type of parameter : "+pfield.getType().getName());
				return false;
			}
			return true;
		}catch(NoSuchFieldException ex){
			System.out.println("Parameters.set"+key+","+value+")  NoSuchFieldException : "+ex.getMessage());
		} catch (IllegalArgumentException ex) {
			System.out.println("Parameters.set"+key+","+value+")  IllegalArgumentException : "+ex.getMessage());
		} catch (IllegalAccessException ex) {
			System.out.println("Parameters.set"+key+","+value+")  IllegalAccessException : "+ex.getMessage());
		}
		return false;
	}
}
