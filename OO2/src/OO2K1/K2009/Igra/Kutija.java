package OO2K1.K2009.Igra;

/**
 * Created by popina on 12.3.15..
 */
public class Kutija extends  Skup{
    public boolean Dodaj(Domina d) {
        if (IsThere(d))
            return false;
        Elem e = new Elem(d);
        if (first == null)
            first = e;
        else
            last.next = e;
        last = e;
        return true;
    }

    public void RandomKutija(int n) {
        first = null;
        last = null;

        Domina[] d = new Domina[n * (n - 1) / 2];
        int cnt = 0;
        for (int i = 0; i < n - 1; i ++)
            for (int j = i + 1; j < n; j++)
                d[cnt++] = new Domina(i, j);

        for (int idx = d.length - 1; idx >= 0; idx --) {
            int high = idx, low = 0;
            int ranIdx = (int)(Math.random() * (high - low) + low);

            Domina tmp = d[idx];
            d[idx] = d[ranIdx];
            d[ranIdx] = tmp;
            Dodaj(d[idx]);
        }
    }

    public Domina TakeIt() {
        if (first == null)
            return null;

        Elem e = first;
        first = first.next;
        if (first == null)
            last = null;
        return e.info;
    }

}
