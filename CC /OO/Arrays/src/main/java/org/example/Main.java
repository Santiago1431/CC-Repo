package org.example;

public class Main {
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


    public static void main(String[] args) {
        TesteArrays array1 = new TesteArrays();
        exibirArray(array1.getArray1());
        array1.setArray2(array1.modificaArray(array1.array2));
        System.out.println("\n");
        exibirArray(array1.getArray2());

    }
}