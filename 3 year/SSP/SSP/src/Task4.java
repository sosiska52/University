import java.util.Scanner;

public class Task4 {
    public void task() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter string:");
        String text = scanner.nextLine();

        int vowelCount = 0;
        int spaceCount = 0;
        int letterCount = 0;

        for(int i = 0; i < text.length();i++) {
            char ch = text.charAt(i);
            if (Character.isLetter(ch)) {
                letterCount++;
                if ("AEIOUYaeiouy".indexOf(ch) != -1) {
                    vowelCount++;
                }
            }
            if (Character.isWhitespace(ch)) {
                spaceCount++;
            }
        }

        System.out.println("Number of vowels: " + vowelCount);
        System.out.println("Number of spaces: " + spaceCount);
        System.out.println("Number of letters: " + letterCount);
    }
}
