package OO2K2.K2010.Kretnja;

/**
 * Created by popina on 3.5.15..
 */
public class Automobil extends Thread implements Pokretan  {
    private static int idx;
    private int pIdx = idx++;
    private Aerodrom a;
    private double x, y, dx, dy, r;
    private long t;
    private boolean work;

    public Automobil(Aerodrom a, double x, double y, double dx, double dy, double r, long t) {
        this.a = a;
        this.x = x;
        this.y = y;
        this.dx = dx;
        this.dy = dy;
        this.r = r;
        this.t = t;
    }

    public synchronized  void Start() {
        start();
    }
    public void Stop() {
        interrupt();
    }

    public synchronized  void Pomeri() {
        x += dx;
        y += dy;
    }

    public void run() {
        try {
            while (!interrupted()) {
                sleep(t);
                Pomeri();
                switch (a.IsCrashed(this)) {
                    case Aerodrom.AUTO :
                        dx = 0; dy = 0; break;
                    case Aerodrom.SUDAR_SA_DUZINOM:
                        dy = -dy; break;
                    case Aerodrom.SUDAR_SA_SIRINOM:
                        dx = -dx;break;
                }
            }
        }
        catch (InterruptedException e) {

        }
    }

    public double GetX() {
        return x;
    }

    public double GetY() {
        return y;
    }

    public double GetDx() {
        return dx;
    }

    public double GetDy() {
        return dy;
    }

    public double GetR() {
        return r;
    }

    public long GetT() {
        return t;
    }

    public double Distance(Automobil a) {
        synchronized (this) {
            synchronized (a) { // mrzi me
                x++;
            }
        }
        return 1;
    }

    public String toString() {
        return pIdx + "(" + x + ", " + y +")";
    }

}
