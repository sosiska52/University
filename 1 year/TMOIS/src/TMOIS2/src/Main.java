import java.util.Scanner;
public class Main {

    public static int interpolSearch(int[] arr, int x) {
        int low = 0, mid, high = arr.length - 1, i = 0;
        while (arr[low] < x && arr[high] > x) {
            i++;
            mid = low + ((x - arr[low]) * (high - low)) / (arr[high] - arr[low]);
            if (arr[mid] < x)
                low = mid + 1;
            else if (arr[mid] > x)
                high = mid - 1;
            else {
                System.out.println("Кол-во итераций: " + i);
                return mid;
            }
        }
        if (arr[low] == x) {
            System.out.println("Кол-во итераций: " + i);
            return low;
        } else if (arr[high] == x) {
            System.out.println("Кол-во итераций: " + i);
            return high;
        } else {
            System.out.println("Кол-во итераций: " + i);
            return -1;
        }
    }

    public static int binarySearch(int[] arr, int x) {
        int low = 0, high = arr.length - 1, i = 0;
        while (arr[low] < x && arr[high] > x) {
            i++;
            if (arr[(low + high) / 2] > x)
                high = (low + high) / 2;
            else if (arr[(low + high) / 2] < x)
                low = (low + high) / 2;
            else {
                System.out.println("Кол-во итераций: " + i);
                return (low + high) / 2;
            }
        }
        if (arr[low] == x) {
            System.out.println("Кол-во итераций: " + i);
            return low;
        } else if (arr[high] == x) {
            System.out.println("Кол-во итераций: " + i);
            return high;
        } else {
            System.out.println("Кол-во итераций: " + i);
            return -1;
        }
    }

    public static void showMatrix(int[][] matrix){
        System.out.println("----------------------------------------------");
        for(int i = 0; i < matrix.length; i++) {
            System.out.println();
            for (int j = 0; j < matrix[i].length; j++)
                System.out.print(matrix[i][j] + " ");
        }
        System.out.println("\n----------------------------------------------");
    }

    public static int[] mergeSort(int[] x) {
        int[][] matrix = new int[x.length][1];
        for (int i = 0; i < x.length; i++)
            matrix[i][0] = x[i];
        for(int size = 1;size < x.length;size *= 2) {
            for (int i = 0, n = 0; i < x.length - size; i += 2 * size, n++) {
                if(size == 1 && x.length % 2 == 1 && n == (x.length)/(2*size))
                    continue;
                matrix[i] = merge(matrix[i], matrix[i + size]);
            }
        }
        return matrix[0];
    }

    public static int[] merge(int[] l, int[] r) {
        int ir, il;
        ir = il = 0;
        int[] res = new int[l.length + r.length];
        for (int i = 0; i < l.length + r.length; i++) {
            if (il < l.length && (ir >= r.length || l[il] < r[ir])) {
                res[i] = l[il];
                il++;
            } else {
                res[i] = r[ir];
                ir++;
            }
        }
        return res;
    }

    public static String makeMax(int[] x){
        int[] arr = x;
        boolean check = true;
        String temp, dig1, dig2;
        String [] sarr = new String[arr.length];
        for(int i = 0; i < arr.length; i++)
            sarr[i] ="" + arr[i];
        while(check){
            check = false;
            for(int i = 0; i < arr.length - 1; i++){
                dig1 = sarr[i] + sarr[i+1];
                dig2 = sarr[i+1] + sarr[i];
                if(dig1.compareTo(dig2) < 0){
                    temp = sarr[i];
                    sarr[i] = sarr[i+1];
                    sarr[i+1] = temp;
                    check = true;
                }
            }
        }
        String res = "";
        for(int i = 0; i < sarr.length; i++){
            if((sarr[i] == sarr[i+1]) && (sarr[i] == "0")){
                res += sarr[i];
                i++;
            } else {
                res += sarr[i];
            }
        }
        return res;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[] s = {1, 2, 5, 8, 11, 14, 17, 20, 23, 25, 29};
        int[] test1 = {4, 6, 13, 12, 1, 8, 14, 3, 10, 9, 5, 7, 2, 11,15};
        int[] test2 = {999999998,999999997,999999999};
        int[] test3 = {1,11,5,8,7,3,10,12,4,2,6,9,13};
//        System.out.println("Введите ключ, номер которого хотите найти: ");
//        int x = sc.nextInt();
//
//        int res = interpolSearch(s,x);
//        System.out.println("Номер искомого ключа по интерполярному поиску: " + res);
//
//        res = binarySearch(s, x);
//        System.out.println("Номер искомого ключа по бинарному поиску: " + res);

//        System.out.println("Сортировка слиянием: ");
//        test1 = mergeSort(test3);
//        for(int i = 0; i < test1.length; i++)
//            System.out.print(test1[i] + " ");

        System.out.println("\nМаксимальное число сделанное из массива: ");
        String str = makeMax(test2);
        System.out.println(str);
    }
}