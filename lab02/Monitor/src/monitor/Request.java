package monitor;

/*
 * Request class
 */
public class Request {
	int ID;
	int length;
	
	public Request(int ID) {
		this.ID = ID;
		length = length();
	}
	//random length from 1 to 6
	public int length(){
		return (int) (Math.random()*5+1);
	}
	
}
