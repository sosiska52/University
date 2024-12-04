import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Lab2 object = new Lab2();
        int choice;
        String fileName;
        while(true){
//            clearConsole();
            System.out.println("1. Make new random file");
            System.out.println("2. Sort file");
            System.out.println("3. Check sorted file");
            System.out.println("4. Exit");

            choice = sc.nextInt();
            sc.nextLine();
            switch (choice){
                case 1:
//                    clearConsole();
                    System.out.print("Enter file name: ");
                    fileName = sc.nextLine();
                    System.out.print("Enter file size: ");
                    int size = sc.nextInt();
                    object.generateRandomFile(fileName, size);
                    break;
                case 2:
                    System.out.print("Enter file name: ");
                    fileName = sc.nextLine();
                    System.out.print("Enter mode(true - forward; false - backward): ");
                    boolean mode = sc.nextBoolean();
                    object.sortFile(fileName, mode);
                    break;
                case 3:
                    System.out.print("Enter file name: ");
                    fileName = sc.nextLine();
                    if(object.sortCheck(fileName))
                        System.out.println("File is sorted");
                    else System.out.println("File is not sorted");
                    break;
                case 4:
                    sc.close();
                    return;
                default:
//                    clearConsole();
                    System.out.println("Wrong option");
//                    try {
//                        System.in.read();
//                    } catch (IOException e) {
//                        e.printStackTrace();
//                    }
                    break;
            }
        }
    }

    private static void clearConsole() {
        for (int i = 0; i < 50; i++) {
            System.out.println();
        }
    }
}