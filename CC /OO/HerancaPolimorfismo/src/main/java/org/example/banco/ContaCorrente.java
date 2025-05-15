package org.example.banco;

public class ContaCorrente extends Conta{
    protected double chequeEspecial;

    public ContaCorrente(double saldoinicial, double chequeEspecial){
        super(saldoinicial);
        this.chequeEspecial = chequeEspecial;
    }
    public ContaCorrente(double saldoinicial){
        super(saldoinicial);
    }
    public boolean sacar(double valor){
        if(valor > this.saldo + this.chequeEspecial)
            return false;
        if(valor <= this.saldo)
            this.saldo -= valor;
        return true;
    }
}
