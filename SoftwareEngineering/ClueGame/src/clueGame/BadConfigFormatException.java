/* 
 * BadConfigFormatException is a custom exception for when the provided config files do not fit the necessary format
 * for the game to load properly.
 * 
 * Author: Ty Gazaway
 * Date: 10/11/2024
 * 
 * */
package clueGame;

@SuppressWarnings("serial")
public class BadConfigFormatException extends RuntimeException{
	private String message;
	
	public BadConfigFormatException() {
		super();
		message = "Improperly formatted config file";
	}
	
	public BadConfigFormatException(String message) {
		super();
		this.message = message;
	}
	
	@Override
	public String toString() {
		return message;
	}
}
