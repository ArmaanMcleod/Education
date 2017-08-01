/* Libraries, just in case */
import java.util.Scanner;
import java.lang.Math;

/* pythagoras class */
public class MathTestTwo {
    /* main function */
    public static void main(String args[]) {
        double x, alpha, beta;
        final int hypo = 10;
        final double bottomSide = 7.2;
        final int oneEightyDegrees = 180, nintyDegrees = 90;
        
        /* side x */
        x = Math.sqrt((hypo * hypo) - (bottomSide * bottomSide));
        System.out.println(x);

        /* alpha */
        alpha = Math.toDegrees(Math.acos(bottomSide/hypo));
        System.out.println(alpha);
        
        /* beta */
        beta = oneEightyDegrees - nintyDegrees - alpha;
        System.out.println(beta);
    }
}