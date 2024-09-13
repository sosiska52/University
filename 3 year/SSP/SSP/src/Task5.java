import java.util.Scanner;

public class Task5 {
    public void task() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter string:");
        String text = scanner.nextLine();
        System.out.print("Enter splitter:");
        String splitter = scanner.nextLine();
        String[] strings = text.split(splitter);

        System.out.println("Result:");
        for (int i = 0; i < strings.length; i++) {
            System.out.println(strings[i]);
        }
    }
}
