package OO2K2.K2011.Fizika;

/**
 * Created by popina on 1.5.15..
 */
public class Merac extends  Thread {
    private Velicina v;
    private double sum;
    private int cnt;
    private long time;
    private boolean work = false;

    public Merac(long time, Velicina v) {
        this.v = v;
        this.time = time;
        start();
    }

    public double GetVal() {
        return v.Vrednost(); // pitanje je da li mora synchronized
    }

    public synchronized  double GetSrVr() throws  ErrorNemaPodataka {
        if (cnt == 0)
            throw new ErrorNemaPodataka();
        return sum / cnt;
    }

    public synchronized void Start() {
        work = true; notify();
    }

    public synchronized  void Pause() {
        work = false; cnt = 0; sum = 0;
    }

    public synchronized void Stop() { // mora, sta ako se zaustavi, a
        interrupt();
        if (v instanceof  Promenljiva)
            ((Promenljiva) v).Stop();
    }

    public void run() {
        try {
            while (!interrupted()) {
                synchronized (this) {
                while (!work) wait(); }
                sleep(time);

                if (work) {
                    synchronized (this) {
                        sum += v.Vrednost();
                        cnt++;
                    }
                }
            }
        }
        catch (InterruptedException e) {

        }
    }


    public synchronized  String toString() {
        String s = "" + v.Vrednost() + " " + v.Jedinica();
        if (cnt > 0)
            s += cnt + " " + v.Jedinica();
        return s;
    }


}
