package OO2K1.K2011.galerija;

/**
 * Created by popina on 20.3.15..
 */
public class Galerija {
    private Sadrzaj [] x;

    public Galerija(int kap) {
        x = new Sadrzaj[kap];
    }

    public boolean Dodaj(int idx, Sadrzaj s) {
        if ( (idx >= x.length) || (idx < 0) || (x[idx] != null))
            return false;
        x[idx] = s;
        return true;
    }

    public Sadrzaj Uzmi(int idx) {
        if ( (idx >= x.length) || (idx < 0) || (x[idx] != null))
            return null;
        return x[idx];
    }

    public int Velicina() {
        int vel = 0;
        for (Sadrzaj it : x)
            if (it != null)
                vel += it.Velicina();
        return vel;
    }

    public String toString() {
        String s = "";
        for (Sadrzaj it : x)
            if (it != null)
                s += it + "\n";
        return s;
    }
}
