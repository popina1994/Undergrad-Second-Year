package OO2K2.K2012.Vozovi;

/**
 * Created by popina on 1.5.15..
 */
public class Stanica implements  Cloneable {
    private static int idx;
    private int pIdx = idx++, putarina;
    private Cenovnik c;



    public Stanica(Cenovnik c) {
        this.c = c;
    }

    public Stanica clone() {
        try {
            Stanica s = (Stanica)(super.clone());
            s.putarina = 0;
            s.pIdx = idx++;
            return s;
        }
        catch (CloneNotSupportedException e) {
            return null;
        }
    }

    public void SetCenovnik(Cenovnik c) {
        this.c = c;
        putarina = 0;
    }

    public void NaplatiPutarinu(Vozilo v) throws ErrorNemaKategorija, ErrorNemaCenovnik {
        if (c == null)
            throw new ErrorNemaCenovnik();
        putarina += c.GetPutarina(v.Kategorija());
    }

    public int GetPutarina() {
        return putarina;
    }

    public String toString() {
        return pIdx + "(" + putarina + ")";
    }

}
