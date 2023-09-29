
import java.util.Scanner;

public class Main {

    public static void showMatrix(int[][] matrix){
        System.out.println("----------------------------------------------");
        for(int i = 0; i < matrix.length; i++) {
            System.out.println();
            for (int j = 0; j < matrix[i].length; j++)
                System.out.print(matrix[i][j] + " ");
        }
        System.out.println("\n----------------------------------------------");
    }

    public static void Dijkstra(int[][] matrix)
    {
        int[] dist = new int[matrix.length];
        Boolean[] shortestPath = new Boolean[matrix.length];
        int[] prev = new int[matrix.length];

        for (int i = 0; i < matrix.length; i++) {
            dist[i] = Integer.MAX_VALUE;
            shortestPath[i] = false;
        }

        dist[0] = 0;

        for (int count = 0; count < matrix.length - 1; count++) {
            int min = Integer.MAX_VALUE;
            int minInd = -1;

            for (int v = 0; v < matrix.length; v++)
                if (!shortestPath[v] && dist[v] <= min) {
                    min = dist[v];
                    minInd = v;
                }

            shortestPath[minInd] = true;

            for (int v = 0; v < matrix.length; v++)
                if (!shortestPath[v] && matrix[minInd][v] != 0
                        && dist[minInd] != Integer.MAX_VALUE
                        && dist[minInd] + matrix[minInd][v] < dist[v]){
                    dist[v] = dist[minInd] + matrix[minInd][v];
                    prev[v] = minInd;
                }
        }

        System.out.println("Вершина \t Дистанция \t ПредВерш" );
        for (int i = 0; i < dist.length; i++)
            System.out.println((i+1) + " \t\t\t " + dist[i] + " \t\t\t " + (prev[i] + 1));
    }

    public static void Floyd(int[][]x){
        int[][] dist;
        dist = x;
        int inf = 9999;
        for(int i = 0; i < dist.length; i++)
            for (int j = 0; j < dist[i].length; j++) {
                if(i != j && dist[i][j] == 0)
                    dist[i][j] = inf;
            }

        int[][] next = new int[x.length][x[0].length];

        for (int i = 0; i < x.length; i++)
            for (int j = 0; j < x.length; j++) {
                if (dist[i][j] != inf && i != j)
                    next[i][j] = j;
                else
                    next[i][j] = -1;
            }

        for (int k = 0; k < x.length; k++) {
            for (int i = 0; i < x.length; i++) {
                for (int j = 0; j < x.length; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }

        System.out.println("Матрица длинн");
        for (int i = 0; i < x.length; i++) {
            for (int j = 0; j < x.length; j++) {
                if (dist[i][j] == inf)
                    System.out.print("- ");
                else
                    System.out.print(dist[i][j] + " ");
            }
            System.out.println();
        }

        System.out.println("Матрица путей");
        for (int i = 0; i < x.length; i++) {
            for (int j = 0; j < x.length; j++) {
                if (next[i][j] == -1)
                    System.out.print("- ");
                else
                    System.out.print( next[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int [][] matrix = {
                {0, 5, 7, 4, 0, 0},
                {5, 0, 0, 3, 0, 2},
                {7, 0, 0, 5, 8, 0},
                {4, 3, 5, 0, 6, 4},
                {0, 0, 8, 6, 0, 0},
                {0, 2, 0, 4, 0 ,0}};
        Dijkstra(matrix);
        Floyd(matrix);
    }
}