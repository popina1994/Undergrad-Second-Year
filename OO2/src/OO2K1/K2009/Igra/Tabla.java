package OO2K1.K2009.Igra;

/**
 * Created by popina on 13.3.15..
 */
public class Tabla extends Skup{
    public boolean Dodaj(Domina d) {
        if (first == null) {
            Dodaj(d);
            return true;
        }
        boolean addBegin = false;
        if (first.info.GetFirst() == d.GetFirst())
            addBegin = true;
        else if (first.info.GetFirst() == d.GetSecond()) {
            d.Reverse();
            addBegin = true;
        }

        if (addBegin) {
            Elem tmpFirst = first;
            first = new Elem(d);
            first.next = tmpFirst;
            return true;
        }

        boolean addLast = false;
        if (last.info.GetSecond() == d.GetFirst())
            addLast = true;
        else if (last.info.GetSecond() == d.GetSecond()) {
            d.Reverse();
            addLast = true;
        }

        if (addLast) {
            Elem tmpLast = last;
            last = new Elem(d);
            tmpLast.next = last;
            return true;
        }
        return false;
    }
}
