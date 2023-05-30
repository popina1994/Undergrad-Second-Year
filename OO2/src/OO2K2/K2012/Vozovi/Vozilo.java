package OO2K2.K2012.Vozovi;

/**
 * Created by popina on 1.5.15..
 */
public class Vozilo implements  Kategorizovano {
    private int kat;

    public Vozilo(int kat) {
        this.kat = kat;
    }

    public int Kategorija() {
        return kat;
    }
}