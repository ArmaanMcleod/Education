import java.lang.Math;

public class ConvertPie {
	public static void main(String args[]) {
		double pie = Math.PI;

		String str = String.format("%03d%.4f", 0, pie);
		String text = String.format("\"The value of \'pi\' to four places is %s\"", str);
		System.out.println(text);
	}
}