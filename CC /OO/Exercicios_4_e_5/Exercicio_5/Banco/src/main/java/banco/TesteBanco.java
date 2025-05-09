package banco;

import banco.*;
public class TesteBanco {
    public static void main(String[] args) {
        Conta conta;
        Cliente cliente;

        cliente = new Cliente("Bruno", "Henrique");
        System.out.println("Criando o cliente ." + cliente.getNome());



        System.out.println("Criando uma conta com saldo de R$ 50.000,00 para o ." + cliente.getNome());
        conta = new Conta(50000.00);
        cliente.setConta(conta);

        System.out.println("Sacando R$ 1.200,00");
        conta.sacar(1200.00);


        System.out.println("Depositando R$ 8.525,00");
        conta.depositar(8525.00);

        System.out.println("Sacando R$ 12000");
        conta.sacar(12800.00);
        System.out.println("Sacando R$ 50.000,00");
        conta.sacar(50000.00);

        System.out.println("O saldo da conta é R$ " + cliente.getConta().getSaldo());

    }
}
