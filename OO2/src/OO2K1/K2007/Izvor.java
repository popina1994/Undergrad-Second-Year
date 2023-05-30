package OO2K1.K2007;

/**
 * Created by popina on 10.3.15..
 */
public class Izvor {
    private double snaga, opter;
    private Potrosac x[];

    public Izvor(double snaga, int brojPrikljucnih) {
        this.snaga = snaga;
        x = new Potrosac[brojPrikljucnih];
    }

    public double GetSnaga() {
        return snaga;
    }

    public double GetOpterecenje() {
        return opter;
    }

    public int BrojPrikljucenih() {
        return x.length;
    }

    public boolean Prikljuci(Potrosac p, int idx) {
        if ( (idx >= x.length) || (idx < 0) )
            return false;
        if (p == null) {
            if (x[idx] == null)
                opter -= x[idx].Snaga();
            x[idx] = null;
            return true;
        }
        if (x[idx] == null) {
            if  ((opter + p.Snaga()) <= snaga) {
                opter += p.Snaga();
                x[idx] = p;
                return true;
            }
            else return false;
        }
        else {
            if ( (opter + p.Snaga() - x[idx].Snaga()) <= snaga) {
                opter += p.Snaga() - x[idx].Snaga();
                x[idx] = p;
                return true;
            }
            else return false;

        }
    }

    public String toString() {
        String s = "" + snaga;
        s +=  " " + opter;

        for (Potrosac p : x) {
            if (p != null)
                s += p.toString();
            s += "\n";
        }
        return s;
    }
}
