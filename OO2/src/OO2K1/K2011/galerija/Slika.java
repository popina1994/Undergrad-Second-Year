package OO2K1.K2011.galerija;

/**
 * Created by popina on 20.3.15..
 */
public class Slika extends Sadrzaj {
    private int s, v;

    public Slika(String naziv, int s, int v) {
        super(naziv);
        this.s = s;
        this.v = v;
    }

    public int GetS() {
        return s;
    }

    public int GetV() {
        return v;
    }

    public int Velicina() {
        return super.Velicina() + 4 * s * v + 32;
    }

    public char GetOznaka() {
        return 's';
    }

}
