package OO2K1.K2010.Prevoz;

/**
 * Created by popina on 14.3.15..
 */

class Elem {
    Tovar info;
    Elem next;
    Elem(Tovar info) {
        this.info = info;
    }
}

public class Paket extends Tovar{
    private Elem begin;

    public Paket() {
        super("paket");
    }

    public void DodajTovar(Tovar t) {
        Elem e = new Elem(t);
        e.next = begin;
        begin = e;
    }

    public double GetTezina() {
        double tezina = 0;
        for (Elem it = begin; it != null; it = it.next)
            tezina += it.info.GetTezina();
        return tezina;
    }

    public String GetVrsta() {
        return vrsta;
    }
}
