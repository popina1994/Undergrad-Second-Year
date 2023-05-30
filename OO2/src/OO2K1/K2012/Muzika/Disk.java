package OO2K1.K2012.Muzika;

/**
 * Created by popina on 21.3.15..
 */
public class Disk extends Stavka {
    private Numera[] x;
    private int n;

    public Disk(String naslov, String izdavac, int kap) {
        super(naslov, izdavac);
        x = new Numera[kap];
    }

    public char GetVrsta() {
        return 'D';
    }

    public boolean Dodaj(Numera num) {
        if (n == x.length)
            return false;
        x[n++] = num;
        return true;
    }

    public String toString() {
        String s = super.toString() + "[";
        int traj = 0;
        for (int idx = 0; idx < n; idx ++) {
            if (idx != 0)
                s += "," + x[idx];
            else
                s += x[idx];
            traj += x[idx].GetTrajanje();
        }
        return s + "]:" + traj;
    }

}
