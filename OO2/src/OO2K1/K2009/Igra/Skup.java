package OO2K1.K2009.Igra;

/**
 * Created by popina on 12.3.15..
 */

class Elem {
    Domina info;
    Elem next;

    Elem(Domina info) {
        this.info = info;
    }
}

public abstract  class Skup {
    protected Elem first, last;

    public boolean IsThere(Domina d) {
        for (Elem it = first; it != null; it = it.next)
            if (d.Equal(it.info))
                return true;
        return false;
    }

    public abstract  boolean Dodaj(Domina d);

    public String toString() {
        StringBuilder s = new StringBuilder("");

        for (Elem it = first; it != null; it = it.next)
            s.append(it.info + " ");
        return s.toString();
    }
}
