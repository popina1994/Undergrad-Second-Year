package OO2K2.K2014.Saobracaj;

/**
 * Created by popina on 28.4.15..
 */
public class Ulica extends  Saobracajnica {

    public Ulica(int brTraka, long tMin, long tMax) throws ErrorBr {
        super(brTraka, tMin, tMax);
        start();
    }

    public void Do() {
        t[(int)(Math.random() * t.length)].PushBack(new Vozilo());
    }

    public String Snimak() {
        int idx = (int)(Math.random() * t.length);
        t[idx].PopFront();
        return t[idx].GetLastShoot();
    }
}
