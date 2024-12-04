public class Task2 {
    public void task() {
        // Массив строк с датами
        String[] dates = {
                "01/09/2022", "15/01/2023", "23/05/2021", "07/12/2020",
                "30/06/2022", "14/02/2023", "05/11/2022", "19/07/2021",
                "11/10/2022", "25/04/2023"
        };

        // Массив названий месяцев
        String[] months = {
                "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
                "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"
        };

        for (int i = 0; i < dates.length; i++) {
            String[] temp = dates[i].split("/");
            String day = temp[0];
            int monthIndex = Integer.parseInt(temp[1]) - 1;
            String year = temp[2];
            String formattedDate = day + " " + months[monthIndex] + " " + year;
            System.out.println(formattedDate);
        }
    }
}