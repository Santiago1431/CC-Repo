package org.example.banco;

public class Conta {
    protected double saldo;

    public Conta(double saldoinicial) {
        this.saldo = saldoinicial;
    }
    public double getSaldo() {
        return saldo;
    }
    public boolean depositar(double valor) {
        this.saldo += valor;
        return true;
    }
    public boolean sacar(double valor) {
        if (this.saldo >= valor) {
            this.saldo -= valor;
            return true;
        }
        return false;
    }
}
