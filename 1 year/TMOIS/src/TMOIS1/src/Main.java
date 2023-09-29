public class Main {
    public int[] fillWith0(int[]a, int size)
    {
        int[] filled = new int[size];
        for(int i = 0; i < a.length; i++)
            filled[i] = a[i];
        for(int i = a.length; i < size; i++)
            filled[i] = 0;
        return filled;
    }
    public static void bool(int [] array)
    {
        int p = (int)Math.pow(2,array.length);
        System.out.print("Boolean of a set of numbers:{\n{ }\n ");
        for (int i = 1; i < p; i++)
        {
            System.out.print("{");
            for (int j = 0; j < array.length; j++)
            {
                int z = i & (1 << j);
                if (z != 0)
                    System.out.print(array[j]+" ");
            }
            System.out.println("}");
        }
        System.out.print("}");
    }
    public void copy(int[] result, int currentResultIndex, int[] source, int currentSourceIndex) {
        while (source.length > currentSourceIndex) {
            result[currentResultIndex] = source[currentSourceIndex];
            currentResultIndex ++;
            currentSourceIndex ++;
        }
    }
    public int[] merging(int[] aArray, int[] bArray) {
        if (aArray.length == 0) {
            return bArray;
        }
        if (bArray.length == 0) {
            return aArray;
        }
        int currentAIndex = 0;
        int currentBIndex = 0;
        int[] resultArray = new int[aArray.length + bArray.length];
        int currentResultIndex = 0;
        while (true) {
            if (aArray[currentAIndex] < bArray[currentBIndex]) {
                resultArray[currentResultIndex] = aArray[currentAIndex];
                currentAIndex++;
                currentResultIndex++;
                if (aArray.length <= currentAIndex) {
                    copy(resultArray, currentResultIndex, bArray, currentBIndex);
                    return resultArray;
                }
            } else {
                resultArray[currentResultIndex] = bArray[currentBIndex];
                currentBIndex++;
                currentResultIndex++;
                if (bArray.length <= currentBIndex) {
                    copy(resultArray, currentResultIndex, aArray, currentAIndex);
                    return resultArray;
                }
            }
        }
    }
    public int[] combination(int[] a, int[] b, int[] u)
    {
        boolean[] masc = new boolean[u.length];
        int check = 0;
        int count0 = 0;
        if(a.length > b.length)
            b = fillWith0(b, a.length);
        else if(a.length < b.length)
            a = fillWith0(a, b.length);
        for (int i = 0; i < u.length; i++)
        {
            for (int j = 0; j < a.length; j++)
                if (u[i] == a[j] || u[i] == b[j])
                    check++;
            if (check != 0)
            {
                masc[i] = true;
            }
            else
            {
                masc[i] = false;
                count0++;
            }
            check = 0;
        }
        int[] comb = new int[masc.length - count0];
        for (int i = 0; i < u.length ; i++)
        {
            if (masc[i])
            {
                comb[check] = u[i];
                check++;
            }
        }
        return comb;
    }
    public int[] intersection(int[] a, int[] b, int[] u)
    {
        boolean[] masc = new boolean[u.length];
        int count0 = 0;
        boolean checkA = false;
        boolean checkB = false;
        if(a.length > b.length)
            b = fillWith0(b, a.length);
        else if(a.length < b.length)
            a = fillWith0(a, b.length);
        for(int i = 0; i < u.length; i++)
        {
            for(int j = 0; j < a.length; j++)
            {
                if(u[i] == a[j])
                    checkA = true;
                if(u[i] == b[j])
                    checkB = true;
            }
            if(checkA && checkB)
                masc[i] = true;
            else {
                masc[i] = false;
                count0++;
            }
            checkA = false;
            checkB = false;
        }
        int[] inter = new int[masc.length - count0];
        int check = 0;
        for (int i = 0; i < u.length ; i++)
        {
            if (masc[i])
            {
                inter[check] = u[i];
                check++;
            }
        }
        return inter;
    }
    public int[] difference(int[] a, int[] b, int[] u)
    {
        boolean[] masc = new boolean[u.length];
        int count0 = 0;
        boolean checkA = false;
        boolean checkB = false;
        if(a.length > b.length)
            b = fillWith0(b, a.length);
        else if(a.length < b.length)
            a = fillWith0(a, b.length);
        for(int  i = 0; i < u.length; i++)
        {
            for(int j = 0; j < a.length; j++)
            {
                if(u[i] == a[j])
                    checkA = true;
                if(u[i] == b[j])
                    checkB = true;
            }
            if(checkA && !checkB)
                masc[i] = true;
            else
            {
                masc[i] = false;
                count0++;
            }
            checkA = false;
            checkB = false;
        }
        int[] diff = new int[masc.length - count0];
        int check = 0;
        for (int i = 0; i < u.length ; i++)
        {
            if (masc[i])
            {
                diff[check] = u[i];
                check++;
            }
        }
        return diff;
    }
    public int[] symdifference(int[] a, int[] b, int[] u)
    {
        boolean[] masc = new boolean[u.length];
        int count0 = 0;
        boolean checkA = false;
        boolean checkB = false;
        if(a.length > b.length)
            b = fillWith0(b, a.length);
        else if(a.length < b.length)
            a = fillWith0(a, b.length);
        for(int  i = 0; i < u.length; i++)
        {
            for(int j = 0; j < a.length; j++)
            {
                if(u[i] == a[j])
                    checkA = true;
                if(u[i] == b[j])
                    checkB = true;
            }
            if((checkA && !checkB) || (!checkA && checkB))
                masc[i] = true;
            else
            {
                masc[i] = false;
                count0++;
            }
            checkA = false;
            checkB = false;
        }
        int[] sdiff = new int[masc.length - count0];
        int check = 0;
        for (int i = 0; i < u.length ; i++)
        {
            if (masc[i])
            {
                sdiff[check] = u[i];
                check++;
            }
        }
        return sdiff;
    }
    public int[] addition(int[] a, int[] u)
    {
        boolean[] masc = new boolean[u.length];
        int count0 = 0;
        boolean checkA = false;
        for(int  i = 0; i < u.length; i++)
        {
            for(int j = 0; j < a.length; j++)
            {
                if(u[i] == a[j])
                    checkA = true;
            }
            if(!checkA)
                masc[i] = true;
            else
            {
                masc[i] = false;
                count0++;
            }
            checkA = false;
        }
        int[] add = new int[masc.length - count0];
        int check = 0;
        for (int i = 0; i < u.length ; i++)
        {
            if (masc[i])
            {
                add[check] = u[i];
                check++;
            }
        }
        return add;
    }
    public static void output(int []arr){
        for(int i = 0; i<arr.length;i++)
            System.out.print(arr[i] + " ");
    }

    public static int getGrayCode(int i) {
        return  i ^ (i >> 1);
    }

    public static void main(String[] args) {
        int []U = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11};
        int []a = { 2,3,4,5 };
        int []b = { 3,4,6,7 };
        int []c = { 4,8,9 };

        bool(a);

        System.out.println();
        int[] merge = new Main().merging(a,b);
        System.out.print("Result of merging: ");
        output(merge);

        System.out.println();
        int[] comb = new Main().combination(a,b,U);
        System.out.print("Result of combination: ");
        output(comb);

        System.out.println();
        int[] inter = new Main().intersection(a,b,U);
        System.out.print("Result of intersection: ");
        output(inter);

        System.out.println();
        int[] diff = new Main().difference(a,b,U);
        System.out.print("Result of difference: ");
        output(diff);

        System.out.println();
        int[] symdiff = new Main().symdifference(a,b,U);
        System.out.print("Result of symdifference: ");
        output(symdiff);

        System.out.println();
        int[] add = new Main().addition(a,U);
        System.out.print("Result of addition: ");
        output(add);

        System.out.println();
        int[] exp1 = new Main().symdifference(b,a,U);
        int[] exp2 = new Main().difference(exp1, c, U);
        System.out.print("Result of expression: ");
        output(exp2);

        System.out.println();
        int num = 2;
        num = getGrayCode(num);
        System.out.println("Код Грея номера варианта: " + Integer.toBinaryString(num));
    }
}