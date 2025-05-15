package org.example.banco;

public class ContaPoupanca extends Conta {
    protected double taxaRendimento;

    public ContaPoupanca(double saldoinicial, double rendimento){
        super(saldoinicial);
        this.taxaRendimento = rendimento;
    }
}
