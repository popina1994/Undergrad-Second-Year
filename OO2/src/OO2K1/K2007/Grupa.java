package OO2K1.K2007;

/**
 * Created by popina on 10.3.15..
 */

class Elem {
    Potrosac info; // ne moze private nivo, jer Grupa nece moci da pristupa, najbolje resenje ugnjezdena klasa,
                    // ali nije radjeno
    Elem next;

    Elem(Potrosac info) {
        this.info = info;
    }
}

public class Grupa extends Potrosac {
    private Elem begin, end;

    public void PushBack(Potrosac p) {
        Elem e = new Elem(p);
        if (begin != null)
            end.next = e;
        else
            begin = e;
        end = e;
    }

    public double Snaga() {
        double snaga = 0;
        for (Elem it = begin; it != null; it = it.next)
            snaga += it.info.Snaga();

        return snaga;
    }

    public String toString() {
        String s= "[";
        for (Elem it = begin; it != null; it = it.next) {
            s += it.info.toString();
            if (it.next != null) {
                s += ", ";
            }
            else
                s += "]";
        }
        return s;
    }
}
