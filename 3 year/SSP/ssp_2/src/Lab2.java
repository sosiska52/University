import java.io.*;
import java.util.*;

public class Lab2 {
    public void generateRandomFile(String fileName, int size){
        try (BufferedWriter file = new BufferedWriter(new FileWriter(fileName))) {
            Random random = new Random();
            file.write(String.valueOf(size));
            file.newLine();

            for(int i = 0; i < size; i++){
                int num = random.nextInt(1001);
                file.write(String.valueOf(num));
                file.newLine();
            }
        }catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sortFile(String fileName, boolean mode){
        try(BufferedReader file = new BufferedReader(new FileReader(fileName))){
            String size = file.readLine();
            Integer[] arr = new Integer[Integer.parseInt(size)];

            for(int i = 0; i < arr.length; i++)
                arr[i] = Integer.parseInt(file.readLine());

            if(mode)
                Arrays.sort(arr);
            else
                Arrays.sort(arr, Collections.reverseOrder());

            BufferedWriter sortedFile = new BufferedWriter(new FileWriter("sorted_" + fileName));
            sortedFile.write(size);
            sortedFile.newLine();
            for(int i = 0; i < arr.length; i++){
                sortedFile.write(Integer.toString(arr[i]));
                sortedFile.newLine();
            }
            sortedFile.close();

        }catch (IOException e){
            e.printStackTrace();
        }
    }

    public boolean sortCheck(String fileName){
        try(BufferedReader file = new BufferedReader(new FileReader(fileName))){
            int size = Integer.parseInt(file.readLine());
            if (size <= 0) {
                return true;
            }

            boolean f = true, b = true;
            int first = Integer.parseInt(file.readLine());
            for(int i = 0 ; i < size - 1; i++){
                int second = Integer.parseInt(file.readLine());

                if (first < second)
                    b = false;
                if (first > second)
                    f = false;
                if(!f & !b)
                    return false;
                first = second;
            }
        }catch (IOException e){
            e.printStackTrace();
        }
        return true;
    }
}