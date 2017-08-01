/* Libraries, just in case */
import java.util.Scanner;
import java.lang.Math;

/* cyclinder maths class */
public class MathTestThree {
    public static void main(String args[]) {
        final int radius = 10, height = 15;
        final double pi = Math.PI;
        double area, volume;
        
        /* area */
        area = 2 * pi * (radius * radius) + 2 * pi * radius * height;
        System.out.println(area);
        
        /* volume */
        volume = pi * (radius * radius) * height;
        System.out.println(volume);
    }
}