/* Libraries, just in case */
import java.util.Scanner;
import java.lang.Math;

/* pythagoras class */
public class MathTestTwo {
    /* main function */
    public static void main(String args[]) {
        double x, alpha, beta;
        final int hypo = 10;
        double bottomSide = 7.2;
        
        /* side x */
        x = Math.sqrt((hypo * hypo) - (bottomSide * bottomSide));
        System.out.println(x);

        /* alpha */
        alpha = Math.toDegrees(Math.acos(bottomSide/hypo));
        System.out.println(alpha);
        
        /* beta */
        beta = 180 - 90 - alpha;
        System.out.println(beta);
    }
}