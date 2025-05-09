package banco;

import java.util.Scanner;

public class TesteBancoTeclado {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Conta conta;
        int option = 0;
        double saldoInicial = 0.0;
        double valorDeposito = 0.0;
        double valorSaque = 0.0;

        System.out.println("Forneça o saldo inicial para criação de uma conta (R$)");
        saldoInicial = scanner.nextDouble();
        System.out.println("Criando uma conta com saldo de R$ " + saldoInicial);
        conta = new Conta(saldoInicial);

        do {
            System.out.println("Selecione uma opção ");
            System.out.println("1 - Depositar");
            System.out.println("2 - Sacar");
            System.out.println("3 - Consultar saldo");
            System.out.println("4 - Sair");
            option = scanner.nextInt();

            switch (option){
                case 1: {
                    System.out.println("Informe o valor a ser depositado R$");
                    valorDeposito = scanner.nextDouble();
                    conta.depositar(valorDeposito);
                    break;
                }
                case 2: {
                    System.out.println("Informe o valor a ser sacado R$");
                    valorSaque = scanner.nextDouble();
                    conta.sacar(valorSaque);
                    break;
                }
                case 3: {
                    System.out.println("O saldo da conta é R$ " + conta.getSaldo()+"\n");
                    break;
                }
                case 4: {
                    break;
                }
            }
        } while (option != 4);
    }
}
