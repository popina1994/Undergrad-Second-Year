package OO2K1.K2012.Muzika;

/**
 * Created by popina on 21.3.15..
 */
public abstract class Stavka {
    private static int idx;
    private int pIdx = idx++;
    private String naslov, izdavac;

    public Stavka(String naslov, String izdavac) {
        this.naslov = naslov;
        this.izdavac = izdavac;
    }

    public String GetNaslov() {
        return naslov;
    }

    public String GetIzdavac() {
        return izdavac;
    }

    public abstract char GetVrsta();

    public String toString() {
        return "" + GetVrsta() + "." + pIdx + "/" + naslov + "/" + izdavac;
    }
}
