package OO2K2.K2014.Saobracaj;

/**
 * Created by popina on 28.4.15..
 */
public abstract class Saobracajnica extends  Thread {
    protected Traka [] t;
    private long tMin, tMax;
    private boolean work = false;

    public Saobracajnica(int brTraka, long tMin, long tMax) throws ErrorBr {
        if (brTraka < 0)
            throw new ErrorBr();
        t = new Traka[brTraka];
        this.tMin = tMin;
        this.tMax = tMax;
        for (int idx = 0; idx < t.length; idx ++)
            t[idx] = new Traka();
    }

    public abstract void Do();

    public void run() {
        try {
            while (!interrupted()) {
                synchronized (this) {
                    if (!work) { // moze i ovako, jer samo komuniciraju medjusobno, dakle opet samo za potrebe zadatka
                        wait();
                    }
                }
                sleep((long) (Math.random() * (tMax - tMin) + tMin));
                if (work) Do(); // ide
            }
        }
        catch (InterruptedException e) {

        }
    }

    public synchronized  void Start() {
        work = true; notifyAll();
    }

    public synchronized void Pause() {
        work = false;
    }

    public synchronized  void Stop() {
        interrupt();
    }
}
