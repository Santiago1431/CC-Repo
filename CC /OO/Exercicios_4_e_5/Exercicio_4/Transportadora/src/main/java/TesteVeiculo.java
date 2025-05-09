import encapsulamento.versao3.Veiculo;

import java.util.Scanner;

public class TesteVeiculo {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Forneça a carga máxima suportada pelo veículo:");
        double cargaMaxima = scanner.nextDouble();
        Veiculo veiculo = new Veiculo(cargaMaxima);

        int boxCounter = 1;
        double boxWeight = 0.0;
        boolean result = true;

        while (result) {
            System.out.println("Forneça o peso da caixa número " + boxCounter);
            boxWeight = scanner.nextDouble();
            result = veiculo.adicionarCaixa(boxWeight);
            if (result)
                boxCounter++;
            else
                System.out.println("Não foi possível adicionar a caixa número " + boxCounter + " : carga máxima atingida");
        }
        System.out.println("A carga do veiculo é: " + veiculo.getCarga() + " kg");
    }
}

