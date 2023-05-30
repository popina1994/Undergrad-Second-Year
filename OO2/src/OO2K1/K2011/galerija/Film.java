package OO2K1.K2011.galerija;

/**
 * Created by popina on 20.3.15..
 */
public class Film extends Sadrzaj {
    private Slika[] x;
    private int last;

    public Film(String naziv, int n) {
        super(naziv);
        x = new Slika[n];
    }

    public boolean Dodaj(Slika s) {
        if (x.length == last)
            return false;
        if ( (last != 0) && ( (x[last - 1].GetS() != s.GetS()) || (x[last -1].GetV() != s.GetV())))
            return false;
        x[last++] = s;
        return true;
    }

    public int Velicina() {
        int sum = 0;
        for (int idx = 0; idx < last; idx ++)
            sum += x[idx].Velicina();
        return sum + super.Velicina() + 1024;
    }

    public char GetOznaka() {
        return 'F';
    }

    public String toString() {
        String s = super.toString() + "[";
        for (int idx = 0; idx < last; idx++) {
            s += x[idx].toString();
            if (idx != (last - 1))
                s += ", ";
        }
        return s + "]";
    }

}
