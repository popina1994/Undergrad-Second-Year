package OO2K1.K2008.Prodaja;

/**
 * Created by popina on 11.3.15..
 */
public abstract class Radnik {
    private String ime;
    private double procenat;

    public Radnik(String ime, double procenat) {
        this.ime = ime;
        this.procenat = procenat;
    }

    public abstract double Prihod();
    public double Plata() {
        return Prihod() * procenat / 100;
    }

    public String toString() {
        String s = ime + "/" + Plata();
        return s;
    }
}
