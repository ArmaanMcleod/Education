public class Wrapper {
	public static void main(String[] args) {

		/* Character class constants */
		final char maximumChar = Character.MAX_VALUE;
		final char currencySymbol = Character.CURRENCY_SYMBOL;

		/* Integer class constants */
		final int minInteger = Integer.MIN_VALUE;
		final int numberToConvert = 2017;
		final int numberToRotate = -31;

		/* Integer conversions */
		int reverseInteger = Integer.reverse(numberToConvert);
		int rotateInteger = Integer.rotateRight(numberToRotate, 3);

		/* Double class constants */
		final double maximumDouble = Double.MAX_VALUE;
		final double negInfinity = Double.NEGATIVE_INFINITY;
		final int numbertoLongBits = 22;

		/* Double long bits conversion */
		long longBits = Double.doubleToLongBits((double)numbertoLongBits);

		/* Printing out character values */
		System.out.println(maximumChar);
		System.out.println((int)currencySymbol);

		/* Printing out integer values */
		System.out.println(minInteger);
		System.out.println(reverseInteger);
		System.out.println(rotateInteger);

		/* Printing out double values */
		System.out.println(maximumDouble);
		System.out.println(negInfinity);
		System.out.println(longBits);

	}
}