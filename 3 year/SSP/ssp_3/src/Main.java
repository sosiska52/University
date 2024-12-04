import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        while(true){
            System.out.println("Choose program(1, 2, 3)");
            System.out.println("4) Exit");
            Scanner sc = new Scanner(System.in);
            int choise = sc.nextInt();
            switch (choise){
                case 1:
                    new WinApp1();
                    break;
                case 2:
                    new WinApp2();
                    break;
                case 3:
                    new WinApp3();
                    break;
                case 4:
                    return;
                default:
                    System.out.println("Wrong option");
                    break;
            }
        }
    }
}