package OO2K1.K2010.Prevoz;

/**
 * Created by popina on 14.3.15..
 */
public class Kamion {
    private String registracije;
    Tovar [] x;
    private double nosivost, trenutno;

    public Kamion(String registracije, int brojTovara, double nosivost) {
        this.registracije = registracije;
        x = new Tovar [brojTovara];
        this.nosivost = nosivost;
    }

    public boolean Stavi(Tovar t, int idx) {
        if ( (idx < 0) || (idx >= x.length) ||
                ((x[idx] != null) &&  (t.GetTezina() + trenutno - x[idx].GetTezina() ) > nosivost ) )
            return false;
        x[idx] = t;
        trenutno = trenutno -x[idx].GetTezina() + t.GetTezina();
        return true;
    }

    public Tovar Uzmi(int idx) {
        if ( (idx < 0) && (idx >= x.length) || (x[idx] == null))
            return null;
        trenutno -= x[idx].GetTezina();
        Tovar tmp = x[idx];
        x[idx] = null;
        return tmp;
    }

    public String toString() {
        StringBuilder s = new StringBuilder("");
        s.append(registracije);
        s.append("(");
        s.append(trenutno);
        s.append("/");
        s.append(nosivost);
        s.append(")\n");
        for (Tovar t : x) {
            if (t != null)
                s.append(t);
            else
                s.append("NULL");
            s.append("\n");
        }
        return s.toString();
    }



}
