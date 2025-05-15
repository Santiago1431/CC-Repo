package org.example.banco;

public class TesteBanco {
    public static void main(String[] args) {
        Conta conta;
        Cliente brunoHenrique;

        System.out.println("_____ CRIAÇÃO DE CONTAS DE BANCO _____\n");

        //Bruno Henrique
        brunoHenrique = new Cliente("Bruno", "Henrique");
        System.out.println("Criando o cliente " + brunoHenrique.getNome());
        System.out.println("Criando poupança para o cliente" + brunoHenrique.getNome() + " de 50k + taxa de rendimento de 3%.");
        Conta contaBruno = new ContaPoupanca(50000, 0.03);
        brunoHenrique.setConta(contaBruno);

        //Everton ribeiro
        Cliente evertonRibeiro = new Cliente("Everton", "Ribeiro");
        System.out.println("Criando o cliente " + evertonRibeiro.getNome());
        System.out.println("Criando conta Corrente para o cliente " + evertonRibeiro.getNome() + " com saldo de R$ 45.000,00 e  Cheque especial de 30k");
        Conta contaEverton = new ContaCorrente(45000.00, 30000.00);
        evertonRibeiro.setConta(contaEverton);

        //Felipe Luiz
        Cliente felipeLuiz = new Cliente("Felipe", "Luiz");
        System.out.println("Criando o cliente " + felipeLuiz.getNome());
        System.out.println("Criando conta Corrente para o cliente " + felipeLuiz.getNome() + " com saldo de R$ 70.000,00 e  Csem heque especial.");
        Conta contaFelipe = new ContaCorrente(70000.00, 0.00);
        felipeLuiz.setConta(contaFelipe);


        System.out.println("______________Relatório de transações______\n");
        System.out.println("Recuperando cliente Bruno Henrique.");
        System.out.println("Sacando 1.200,00 " + brunoHenrique.getConta().sacar(1200.00));
        System.out.println("Depositando 8.525,00 " + brunoHenrique.getConta().depositar(8525.00));
        System.out.println("Sacando 12.800,00 " + brunoHenrique.getConta().sacar(12800.00));
        System.out.println("Sacando 50.000,00 " + brunoHenrique.getConta().sacar(50000.00));
        System.out.println("Saldo Final: " +brunoHenrique.getConta().getSaldo());




//        System.out.println("Criando uma conta com saldo de R$ 50.000,00 para o ." + cliente.getNome());
//        conta = new Conta(50000.00);
//        cliente.setConta(conta);
//
//        System.out.println("Sacando R$ 1.200,00");
//        conta.sacar(1200.00);
//
//
//        System.out.println("Depositando R$ 8.525,00");
//        conta.depositar(8525.00);
//
//        System.out.println("Sacando R$ 12000");
//        conta.sacar(12800.00);
//        System.out.println("Sacando R$ 50.000,00");
//        conta.sacar(50000.00);
//
//        System.out.println("O saldo da conta é R$ " + cliente.getConta().getSaldo());

    }
}
