import java.util.Arrays;
import java.util.Scanner;
import java.util.Random;
public class Main {

    static class agent{
        double efficiency;
        double time;
    }

    public static void giveProperties(agent[] agents, int[] num){
        Random random = new Random();
        int j = 0;
        for(int i = 0; i < num[0]; i++, j++){
            agents[j].efficiency = 0.2 + (0.5 - 0.2) * random.nextDouble();
            agents[j].time = 6 + random.nextGaussian() * Math.sqrt(0.5);
        }
        for(int i = 0; i < num[1]; i++, j++){
            agents[j].efficiency = 0.1 + (0.3 - 0.1) * random.nextDouble();
            agents[j].time = 5 + random.nextGaussian() * Math.sqrt(0.5);
        }
        for(int i = 0; i < num[2]; i++, j++){
            agents[j].efficiency = 0.05 + (0.2 - 0.05) * random.nextDouble();
            agents[j].time = 4 + random.nextGaussian() * Math.sqrt(0.5);
        }
        for(int i = 0; i < num[3]; i++, j++){
            agents[j].efficiency = 0.01 + (0.02 - 0.01) * random.nextDouble();
            agents[j].time = Math.abs(2 + random.nextGaussian() * Math.sqrt(0.5));
        }
        for(int i = 0; i < num[4]; i++, j++){
            agents[j].efficiency = 0.3 + (0.75 - 0.3) * random.nextDouble();
            agents[j].time = Math.abs(1 + random.nextGaussian() * Math.sqrt(0.5));
        }
    }

    public static void enterPercents(int totalNumOfEmploys, int[] numOfEmploys){
        Scanner sc = new Scanner(System.in);
        double percent = 0;
        int sum = 0;
        for (int i = 0; i < 4; i++) {
            percent = sc.nextInt();
            numOfEmploys[i] = (int)Math.floor(totalNumOfEmploys * percent /100);
            sum += numOfEmploys[i];
        }
        numOfEmploys[4] = totalNumOfEmploys - sum;
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Введите кол-во сотрудников: ");
        int totalNumOfEmploys = sc.nextInt();
        agent[] agents = new agent[totalNumOfEmploys];
        for (int i = 0; i < totalNumOfEmploys; i++) {
            agents[i] = new agent();
        }
        System.out.println("Введите через пробел проценты кол-ва сотрудников в классах: ");
        int[] numOfEmploys = new int[5];

        enterPercents(totalNumOfEmploys, numOfEmploys);
        int totalDays = 0;
        double totalWork = 0;
        double minWork = 100;
        double maxWork = 0;
        int maxDays = 0;
        int minDays = 999;

        for (int i = 0; i < 100; i++) {
            double doneWork = 0;
            int days = 0;
            while (doneWork < 100) {
                giveProperties(agents, numOfEmploys);
                for (int j = 0; j < agents.length; j++) {
                    double work = agents[j].efficiency * agents[j].time;
                    if(work > maxWork)
                        maxWork = work;
                    else if (work < minWork)
                        minWork = work;
                    doneWork += work;
                }
                days++;
            }
            if(days > maxDays)
                maxDays = days;
            else if (days < minDays)
                minDays = days;

            totalDays += days;
            totalWork += doneWork;
        }
        System.out.println("Среднее кол-во дней выполнения работы: " + totalDays/100);
        System.out.println("Средний процент выполненой работы за день: " + totalWork/totalDays);
        System.out.println("Максимально работы за день: " + maxWork);
        System.out.println("Минимально работы за день: " + minWork);
        System.out.println("Максимальное кол-во дней: " + maxDays);
        System.out.println("Минимальное кол-во дней: " + minDays);
    }
}