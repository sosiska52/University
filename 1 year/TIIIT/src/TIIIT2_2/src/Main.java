import java.util.Scanner;

    class vector {
    double x;
    double y;
    double z;
}
public class Main {
    public static double function(vector cord){
        return cord.x * cord.x - cord.z * cord.z * Math.sin(cord.x) + (cord.y + cord.z) * cord.y * cord.y;
    }

    public static vector grad (vector cord){
        vector gradient = new vector();
        gradient.x = 2 * cord.x - Math.pow(cord.z, 2) * Math.cos(cord.x);
        gradient.y = Math.pow(cord.z, 2);
        gradient.z = 2 * Math.sin(cord.x) * cord.z + 2 * cord.y * cord.z + 3 * Math.pow(cord.z, 2);
        return gradient;
    }

    public static vector newCord(vector cord, vector grad, double lamb){
        vector newCord = new vector();
        newCord.x = cord.x + lamb * grad.x;
        newCord.y = cord.y + lamb * grad.y;
        newCord.z = cord.z + lamb * grad.z;
        return newCord;
    }

    public static vector extreme(vector current, double eps, byte znak){
        vector last = new vector();
        double lamb = 0.001 * znak;
        do{
            last = current;
            vector gradient = grad(current);
            current = newCord(current, gradient, lamb);
        }
        while(Math.abs(function(current) - function(last)) > eps);
        return current;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        double eps = 0.0001;
        byte znak;
        System.out.println("найти максимум или минимум (min = -1, max = 1): ");
        znak = sc.nextByte();
        System.out.println("Введите начальные координаты: ");
        vector cord = new vector();
        cord.x = sc.nextDouble();
        cord.y = sc.nextDouble();
        cord.z = sc.nextDouble();
        vector res = extreme(cord, eps, znak);
        System.out.println("Результат: " + res.x + " " + res.y + " " + res.z);
        System.out.println("Результат функции: " + function(res));
    }
}