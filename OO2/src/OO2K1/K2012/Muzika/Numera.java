package OO2K1.K2012.Muzika;

/**
 * Created by popina on 21.3.15..
 */
public class Numera {
    private String naziv, izvodjac;
    private int trajanje;

    public Numera(String naziv, String izvodjac, int trajanje) {
        this.naziv = naziv;
        this.izvodjac = izvodjac;
        this.trajanje = trajanje;
    }

    public String GetNaziv() {
        return naziv;
    }

    public String GetIzvodjac() {
        return izvodjac;
    }

    public int GetTrajanje() {
        return trajanje;
    }

    public String toString() {
        return "" + naziv + "-" + izvodjac + ":" + trajanje;
    }
}
