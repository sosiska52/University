import java.util.Random;
import java.util.Scanner;

public class Task3 {
    public void task() {
        Random random = new Random();
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter N: ");
        int N = scanner.nextInt();
        String letters = "BCDFGHJKLMNPQRSTVWXYZ";
        StringBuilder sequence = new StringBuilder();

        for (int i = 0; i < N; i++) {
            int index = random.nextInt(letters.length());
            sequence.append(letters.charAt(index));
        }

        System.out.println("Sequence: " + sequence.toString());
    }
}