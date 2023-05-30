package OO2K1.K2011.galerija;

/**
 * Created by popina on 20.3.15..
 */
public abstract class Sadrzaj {
    protected static int idx;
    private int personalIdx = idx++;
    private String naziv;

    Sadrzaj(String naziv) {
        this.naziv = naziv;
    }

    public int GetPersonalIdx() {
        return personalIdx;
    }

    public abstract char GetOznaka();

    public int Velicina() {
        return naziv.length() + 8;
    }

    public String toString() {
        return naziv + "(" + GetOznaka() + "/" + GetPersonalIdx() + "/" + Velicina() + ")";
    }


}
