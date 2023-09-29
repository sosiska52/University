import java.util.Scanner;
public class Main {

    public static double func(double x, int a, double b) {
        return Math.cos(x) + 1 / b * Math.cos(a * x + 1) + 1 / Math.pow(b, 2) * Math.cos(Math.pow(a, 2) * x + 2) + 1 / Math.pow(b, 3) * Math.cos(Math.pow(a, 3) * x + 3) + 1 / Math.pow(b, 4) * Math.cos(Math.pow(a, 4) * x + 4);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Введите Х0 и параметр b(2,10): ");
        int a = 9; //Макаревич
        double x0 = sc.nextDouble();
        double b = sc.nextDouble();
        while (true) {
            if (b >= 2 && b <= 10)
                break;
            else {
                System.out.println("Параметр b выходит за рамки, введите заново.");
                b = sc.nextDouble();
            }
        }
        System.out.println("Введите шаг: ");
        double alf = sc.nextDouble();
        System.out.println("Введите максимальное кол-во иттераций: ");
        int Nmax = sc.nextInt();
        double y0 = func(x0, a, b);
        double y1, x1, Y = 0;
        boolean check = false;
        System.out.println("<#> \t<y>      \t<x>      \t<alf>\n -----------------------------------------------");
        for (int i = 0; alf > 0.0001 && i < Nmax; i++, alf *= 0.75) {
            x1 = x0 + alf * (Math.random() * 2 - 1);
            y1 = func(x1, a, b);
            System.out.printf("<%d>| \t<%f> \t<%f> \t<%f> \n", i, y1, x1, alf);
            if (y1 < y0) {
                x0 = x1;
                Y = y1;
                check = true;
            }
        }
        if (check)
            System.out.println("Минимум функции: " + Y);
        else
            System.out.println("Минимум функции: " + y0);
    }
}