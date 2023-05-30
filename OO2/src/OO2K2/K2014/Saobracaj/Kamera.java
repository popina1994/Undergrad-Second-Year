package OO2K2.K2014.Saobracaj;

/**
 * Created by popina on 25.4.15..
 */
public class Kamera {
    private static int idx;
    private int pIdx = idx++;
    private static long t0 = System.currentTimeMillis();
    private long t;
    private Vozilo v;

    public void Snimi(Vozilo v) {
        this.v = v;
        t = System.currentTimeMillis() - t0;
    }

    public String toString() {
        return "[" + pIdx + ":" + t + "]" + v.RegOznaka();
    }
}
