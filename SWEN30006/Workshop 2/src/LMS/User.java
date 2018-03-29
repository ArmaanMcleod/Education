package LMS;

public class User {
	private String name;
	private String email;
	private String username;
	private String password;
	
	public User(String name, String email, String username) {
		this.name = name;
		this.email = email;
		this.username = username;
	}
	
	public boolean authenticate(String password) {
		return true;
	}
}