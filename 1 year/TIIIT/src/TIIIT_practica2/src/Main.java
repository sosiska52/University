import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String txt = sc.nextLine();
        char Sletter = 'а';
        char Bletter = 'А';
        double counter = 0;
        double Pi = 0;
        double Hi = 0;
        double sum = 0;
        for(int i = 0; i<33; i++, Sletter++, Bletter++)
        {
            for(int j = 0; j < txt.length(); j++)
                if(txt.charAt(j) == Sletter || txt.charAt(j) == Bletter)
                    counter++;
            if(counter != 0) {
                Pi = counter / txt.length();
                Hi = Pi * (Math.log(Pi) / Math.log(2));
                sum += Hi;
                Pi = 0;
                Hi = 0;
                counter = 0;
            }
        }
        System.out.println(-sum);
    }
}