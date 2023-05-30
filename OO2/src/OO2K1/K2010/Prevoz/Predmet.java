package OO2K1.K2010.Prevoz;

/**
 * Created by popina on 14.3.15..
 */
public class Predmet extends  Tovar{
    private double tezina;
    public Predmet(String vrsta, double tezina) {
        super(vrsta);
        this.tezina = tezina;
    }

    public String GetVrsta() {
        return vrsta;
    }

    public double GetTezina() {
        return tezina;
    }
    
}
