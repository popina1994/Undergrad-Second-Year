package OO2K1.K2007;

/**
 * Created by popina on 10.3.15..
 */
public class Uredjaj extends Potrosac {
    private double snaga;
    private String vrsta;

    public Uredjaj(String vrsta, double snaga) {
        this.snaga = snaga;
        this.vrsta = vrsta;
    }

    public double Snaga() {
        return snaga;
    }

    public String toString() {
        return vrsta + "(" + snaga + ")";
    }
}
