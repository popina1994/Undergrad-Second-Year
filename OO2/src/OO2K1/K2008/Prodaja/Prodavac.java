package OO2K1.K2008.Prodaja;

/**
 * Created by popina on 11.3.15..
 */
public class Prodavac extends  Radnik {
    double prihod;

    public Prodavac(String ime, double procenat) {
        super(ime, procenat);
    }

    public void Prodaj(double value) {
        prihod += value;
    }

    public double Prihod() {
        return prihod;
    }
}
