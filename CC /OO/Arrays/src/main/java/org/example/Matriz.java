package org.example;

public class Matriz {
    public static void exibirArray(int[] array) {
        System.out.print("<");
        for (int i = 0; i < array.length; i++) {
            // Imprime um elemento
            System.out.print(array[i]);
            // Imprime uma vírgula como delimitador se não for o
            // último elemento
            if ((i+1) < array.length) {
                System.out.print(",");
            }
        }
        System.out.print(">");
    }
    public static void inicializar(int[][] matriz) {
        for (int i = 0; i < matriz.length; i++) {
            matriz[i] = new int[i + 1];
            for (int j = 0; j < matriz[i].length; j++) {
                matriz[i][j] = i + j;
            }
        }
    }
    public static void imprimirMatriz(int[][] matriz) {
        for (int i = 0; i < matriz.length; i++) {
            exibirArray(matriz[i]);
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int[][] matriz = new int[5][];
        inicializar(matriz);
        imprimirMatriz(matriz);
    }
}
