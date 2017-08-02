import java.lang.Math;

/* class for printing value of pie */
public class ConvertPie {
	public static void main(String args[]) {
		double pie = Math.PI;

		/* formatting and printing string */
		String str = String.format("%03d%.4f", 0, pie);
		String text = String.format("\"The value of \'pi\' to four places is %s\"", str);
		System.out.println(text);
	}
}