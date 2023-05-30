package OO2K2.K2011.Fizika;

/**
 * Created by popina on 1.5.15..
 */
public abstract class Promenljiva extends Thread implements  Velicina {
    private long tMin, tMax;
    private double val, delta,  minVal, maxVal;

    public Promenljiva(long tMin, long tMax, double beginVal, double delta, double minVal, double maxVal) {
        this.tMin = tMin;
        this.tMax = tMax;
        this.val = beginVal;
        this.delta = delta;
        this.minVal = minVal;
        this.maxVal = maxVal;
        start();
    }

    public synchronized double Vrednost() {
        return val;
    }

    public void run() {
        try {
            while (!interrupted()) {
                sleep((int)(Math.random() * (tMax-tMin) + tMin));
                synchronized (this) {
                    val += Math.random() * 2 * delta - delta;
                    if (val < minVal)
                        val = minVal;
                    if (val > maxVal)
                        val = maxVal;
                }
            }
        }
        catch (InterruptedException e) {
        }
    }

    public synchronized  void Stop() {
        interrupt();
    }
}
