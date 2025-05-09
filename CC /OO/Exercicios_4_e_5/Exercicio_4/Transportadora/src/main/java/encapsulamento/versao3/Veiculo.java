package encapsulamento.versao3;

public class Veiculo {
    private double carga;
    private double cargaMaxima;

    public Veiculo(double cargaMaxima) {
        this.cargaMaxima = quilosParaNewtons(cargaMaxima);
    }

    public double getCarga() {
        return newtonsParaQuilos(carga);
    }

    public void setCarga(double carga) {
        this.carga = quilosParaNewtons(carga);
    }

    public double getCargaMaxima() {
        return newtonsParaQuilos(cargaMaxima);
    }

    public void setCargaMaxima(double cargaMaxima) {
        this.cargaMaxima = quilosParaNewtons(cargaMaxima);
    }

    public boolean adicionarCaixa(double peso) {
        double pesoEmNewtons = quilosParaNewtons(peso);
        if (this.carga + pesoEmNewtons > this.cargaMaxima)
            return false;
        this.carga+= pesoEmNewtons;
        return true;
    }

    private double newtonsParaQuilos(double peso) {
        return peso / 9.8;
    }

    private double quilosParaNewtons(double peso) {
        return peso * 9.8;
    }
}
