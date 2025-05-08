package org.example;

import lombok.Getter;
import lombok.Setter;



@Getter
public class TesteArrays {
    int[] array1 = {2, 3, 5, 7, 11, 13, 17, 19};
    int[] array2 = array1;

    public int[] modificaArray(int[] array) {
        for(int i = 0; i < array.length; i = i+2){
            array[i] = i;
        }
        return array;
    }

    public void setArray1(int[] array1) {
        this.array1 = array1;
    }

    public void setArray2(int[] array2) {
        this.array2 = array2;
    }
}
