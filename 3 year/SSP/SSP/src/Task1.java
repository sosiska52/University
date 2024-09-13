import java.util.Random;

public class Task1 {
    public void task(){
        Random random = new Random();
        String[] months = {
                "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
                "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"
        };

        int[] rNums = new int[12];
        int sum = 0;
        for(int i = 0; i < rNums.length; i++){
            rNums[i] = random.nextInt(100);
            sum += rNums[i];
        }

        for(int i = 0; i < months.length; i++){
            System.out.println(months[rNums[i]%12] + " - " + rNums[i]);
        }
        System.out.println(sum / rNums.length);
    }
}
